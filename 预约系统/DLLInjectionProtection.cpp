#include "DLLInjectionProtection.h"

std::string DLLInjectionProtection::expandEnvironmentVariables(const std::string& path) {
    char expandedPath[MAX_PATH];
    ExpandEnvironmentStringsA(path.c_str(), expandedPath, sizeof(expandedPath));
    return std::string(expandedPath);
}

bool DLLInjectionProtection::isSuspiciousPath(const std::string& filePath) {
    try {
        ///可疑路径
        static const std::vector<std::string> suspiciousPaths = {
                 WINDOWS_TMP,
                 WINDOWS_SYSTEM32,
                 WINDOWS_SYSWOW64,
                 TEMP,
                 APPDATA,
                 USERPROFILE,
                 PROGRAMDATA
        };
        std::string expandedPath = expandEnvironmentVariables(filePath);
        ///检查恶意目录
        for (const auto& suspiciousPath : suspiciousPaths) {
            if (expandedPath.find(suspiciousPath) != std::string::npos) {
                std::string s = SUSPICIOUS_DLL + expandedPath;
                std::cerr << s << expandedPath << std::endl;
                ExceptionLog::GetInstance()->LogException(s);
                return true;
            }
        }
        ///检查可疑路径模式
        std::regex suspiciousPattern(R"(.*\\[a-zA-Z0-9]{8,}\\.*\.dll$)");
        if (std::regex_match(expandedPath, suspiciousPattern)) {
            std::string s = SUSPICIOUS_DLL + expandedPath;
            std::cerr << s << expandedPath << std::endl;
            ExceptionLog::GetInstance()->LogException(s);
            return true;
        }
        ///检查可疑文件扩展名
        static const std::vector<std::string> suspiciousExtensions = { ".exe", ".dll", ".bat", ".cmd" };
        for (const auto& ext : suspiciousExtensions) {
            if (expandedPath.size() >= ext.size() &&
                expandedPath.compare(expandedPath.size() - ext.size(), ext.size(), ext) == 0) {
                std::string s = SUSPICIOUS_DLL + expandedPath;
                std::cerr << s << expandedPath << std::endl;
                ExceptionLog::GetInstance()->LogException(s);
                return true;
            }
        }
        return false;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        throw;
    }
}

bool DLLInjectionProtection::isValidSignature(const std::string& filePath)const {
    /// 使用 WinVerifyTrust 来验证文件签名
    WINTRUST_FILE_INFO fileInfo = { 0 };
    fileInfo.cbStruct = sizeof(WINTRUST_FILE_INFO);
    fileInfo.pcwszFilePath = std::wstring(filePath.begin(), filePath.end()).c_str();

    GUID actionGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    WINTRUST_DATA trustData = { 0 };
    trustData.cbStruct = sizeof(WINTRUST_DATA);
    trustData.pPolicyCallbackData = NULL;
    trustData.pSIPClientData = NULL;
    trustData.dwUIChoice = WTD_UI_NONE;
    trustData.fdwRevocationChecks = WTD_REVOKE_NONE;
    trustData.dwUnionChoice = WTD_CHOICE_FILE;
    trustData.pFile = &fileInfo;

    LONG status = WinVerifyTrust(NULL, &actionGUID, &trustData);

    return (status == ERROR_SUCCESS);
}

void DLLInjectionProtection::protectMemoryExecution(HANDLE hProcess, LPVOID pMemory, SIZE_T size) {
    /// 设置内存保护，防止恶意代码执行
    DWORD oldProtect;
    if (!VirtualProtectEx(hProcess, pMemory, size, PAGE_READONLY, &oldProtect)) {
        std::cerr << ILLEGAL_MEMORY << std::endl;
        ExceptionLog::GetInstance()->LogException(ILLEGAL_MEMORY);
    }
}

void DLLInjectionProtection::checkAPIIntegrity() {
    /// 检查是否有 API 劫持
      /// 检查 LoadLibraryA 是否被篡改
    if (OriginalLoadLibraryA != (LoadLibraryA_t)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA")) {
        std::cerr << API_LOADLIBRARYA_JACKING << std::endl;
        ExceptionLog::GetInstance()->LogException(API_LOADLIBRARYA_JACKING);
    }
    /// 检查 CreateRemoteThread 是否被篡改
    if (OriginalCreateRemoteThread != (CreateRemoteThread_t)GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateRemoteThread")) {
        std::cerr << API_CREATEREMOTETHREAD_JACKING << std::endl;
        ExceptionLog::GetInstance()->LogException(API_CREATEREMOTETHREAD_JACKING);
    }
    /// 检查 CreateProcessW 是否被篡改
    if (OriginalCreateProcessW != (CreateProcessW_t)GetProcAddress(GetModuleHandleA("kernel32.dll"), "CreateProcessW")) {
        std::cerr << API_CREATEPROCESS_JACKING << std::endl;
        ExceptionLog::GetInstance()->LogException(API_CREATEPROCESS_JACKING);
    }
}

///  钩取LoadLibraryA
HMODULE WINAPI DLLInjectionProtection::hookedLoadLibraryA(LPCSTR lpLibFileName) {
    if (isSuspiciousPath(lpLibFileName)) {
        std::cerr << ILLEGAL_DLL << lpLibFileName << std::endl;
        ExceptionLog::GetInstance()->LogException(ILLEGAL_DLL);
        return NULL;
    }
    return OriginalLoadLibraryA(lpLibFileName);
}

/// 钩取CreateRemoteThread
HANDLE WINAPI DLLInjectionProtection::hookedCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
    SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter,
    DWORD dwCreationFlags, LPDWORD lpThreadId) {
    std::cerr << ILLEGAL_THREAD << std::endl;
    ExceptionLog::GetInstance()->LogException(ILLEGAL_THREAD);
    return NULL;
}

/// 钩取CreateProcessW
BOOL WINAPI DLLInjectionProtection::hookedCreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles,
    DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation) {
    std::cerr << ILLEGAL_PROCESS << std::endl;
    ExceptionLog::GetInstance()->LogException(ILLEGAL_PROCESS);
    return FALSE;
}

void DLLInjectionProtection::initializeHooks() {
    /// 开始 Detours 事务
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    HMODULE hKernel32 = GetModuleHandleA(KERNE132_DLL);
    if (!hKernel32) {
        std::cerr << KERNE_132_DLL_NONE << std::endl;
        ExceptionLog::GetInstance()->LogException(KERNE_132_DLL_NONE);
        return;
    }

    ///原始地址
    OriginalLoadLibraryA = (LoadLibraryA_t)GetProcAddress(hKernel32, "LoadLibraryA");
    if (!OriginalLoadLibraryA) {
        std::cerr << LOADLIBRARYA_ADDRESS_ERROR << std::endl;
        ExceptionLog::GetInstance()->LogException(LOADLIBRARYA_ADDRESS_ERROR);
        return;
    }
    else {
        ///安装钩子
        DetourAttach(&(PVOID&)OriginalLoadLibraryA, hookedLoadLibraryA);
    }
    ///原始地址
    OriginalCreateRemoteThread = (CreateRemoteThread_t)GetProcAddress(hKernel32, "CreateRemoteThread");
    if (!OriginalCreateRemoteThread) {
        std::cerr << CREATEREMOTETHREAD_ADDRESS_ERROR << std::endl;
        ExceptionLog::GetInstance()->LogException(CREATEREMOTETHREAD_ADDRESS_ERROR);
        return;
    }
    else {
        ///安装钩子
        DetourAttach(&(PVOID&)OriginalCreateRemoteThread, hookedCreateRemoteThread);
    }
    ///原始地址
    OriginalCreateProcessW = (CreateProcessW_t)GetProcAddress(hKernel32, "CreateProcessW");
    if (!OriginalCreateProcessW) {
        std::cerr << CREATEPROCESSW_ADDRESS_ERROR << std::endl;
        ExceptionLog::GetInstance()->LogException(CREATEPROCESSW_ADDRESS_ERROR);
        return;
    }
    else {
        ///安装钩子
        DetourAttach(&(PVOID&)OriginalCreateProcessW, hookedCreateProcessW);
    }
    /// 提交 Detours 事务
    DetourTransactionCommit();
}

void DLLInjectionProtection::startMonitoring() {
    std::cout << DLL_PROTECTION_EXECUTION << std::endl;
    ExceptionLog::GetInstance()->LogException(DLL_PROTECTION_EXECUTION);
    while (true) {
        ///启动监控任务
        std::thread memoryThread(&DLLInjectionProtection::monitorMemoryIntegrity, this, GetCurrentProcessId());
        std::thread dllThread(&DLLInjectionProtection::monitorInjectedDLLs, this, GetCurrentProcessId());
        std::thread apiIntegrityThread(&DLLInjectionProtection::checkAPIIntegrity, this);

        memoryThread.join();
        dllThread.join();
        apiIntegrityThread.join();

        std::this_thread::sleep_for(std::chrono::seconds(60));  /// 每 60 秒轮询一次
    }
}

void DLLInjectionProtection::monitorMemoryIntegrity(DWORD processId) {
    /// 打开进程句柄，查询内存信息
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess) {
        MEMORY_BASIC_INFORMATION mbi;
        BYTE* pMem = nullptr;
        while (VirtualQueryEx(hProcess, pMem, &mbi, sizeof(mbi))) {
            // 检查是否是可执行且可写的内存区域
            if (mbi.State == MEM_COMMIT && (mbi.Protect == PAGE_EXECUTE_READWRITE || mbi.Protect == PAGE_READWRITE)) {
                std::cerr << MEMORY_ERROR << std::endl;
                ExceptionLog::GetInstance()->LogException(MEMORY_ERROR);
            }
            pMem += mbi.RegionSize;
        }
        CloseHandle(hProcess);
    }
}

void DLLInjectionProtection::monitorInjectedDLLs(DWORD processId) {
    // 在此监控进程加载的 DLL
     // 打开进程句柄
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess) {
        HMODULE hMods[1024];
        DWORD cbNeeded;
        // 枚举进程加载的所有模块
        if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
            for (unsigned int i = 0; i < cbNeeded / sizeof(HMODULE); i++) {
                TCHAR szModName[MAX_PATH];
                if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                    std::wstring wModName = szModName;
                    std::string modName(wModName.begin(), wModName.end());
                    if (isSuspiciousPath(modName) || !isValidSignature(modName)) {
                        std::cerr << SUSPICIOUS_DLL << modName << std::endl;
                        std::string s = SUSPICIOUS_DLL + modName;
                        ExceptionLog::GetInstance()->LogException(s);
                        exit(EXIT_FAILURE);///结束主进程
                    }
                }
            }
        }
        CloseHandle(hProcess);
    }
}

void DLLInjectionProtection::removeHooks() {
    /// 开始 Detours 事务
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    /// 卸载钩子
    DetourDetach(&(PVOID&)OriginalLoadLibraryA, hookedLoadLibraryA);
    DetourDetach(&(PVOID&)OriginalCreateRemoteThread, hookedCreateRemoteThread);
    DetourDetach(&(PVOID&)OriginalCreateProcessW, hookedCreateProcessW);
    /// 提交 Detours 事务
    DetourTransactionCommit();
}

DLLInjectionProtection::~DLLInjectionProtection() {
    removeHooks();
}