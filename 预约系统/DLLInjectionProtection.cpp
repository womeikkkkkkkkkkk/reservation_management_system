#include "DLLInjectionProtection.h"
#include <windows.h>
#include <wintrust.h>
#include <string>
#include <psapi.h>
#include <softpub.h>

bool DLLInjectionProtection::isSuspiciousPath(const std::string& fliePath) {
    if (fliePath.find("") != std::string::npos) {
        return true;
    }
    if (fliePath.find("") != std::string::npos) {
        return true;
    }
    return false;
}

bool DLLInjectionProtection::isValidSignature(const std::string& filePath) {
    WINTRUST_FILE_INFO fileInfo = { 0 };
    fileInfo.cbStruct = sizeof(WINTRUST_FILE_INFO);
    fileInfo.pcwszFilePath = std::wstring(filePath.begin(), filePath.end()).c_str();

    WINTRUST_ACTDATA actData = { 0 };
    actData.cbStruct = sizeof(WINTRUST_ACTDATA);
    actData.dwUIChoice = WTD_UI_NONE;
    actData.fdwRevocationChecks = WTD_REVOKE_NONE;
    actData.dwUnionChoice = WTD_CHOICE_FILE;
    actData.pFile = &fileInfo;

    GUID policyGUID = WINTRUST_ACTION_GENERIC_VERIFY_V2;
    LONG result = WinVerifyTrust(NULL, &policyGUID, &actData);
    return (result == ERROR_SUCCESS);
}

HMODULE WINAPI DLLInjectionProtection::hookedLoadLiabraryA(LPCSTR lpLibFileName) {
    std::string libPath(lpLibFileName);

    if (isSuspiciousPath(libPath)) {
        ExceptionLog::GetInstance()->LogException("检测到可疑DLL注入");
        std::cerr << "检测到可疑DLL注入" << libPath << std::endl;
        return NULL;
    }
    if (!isValidSignature(libPath)) {
        ExceptionLog::GetInstance()->LogException("检测到无效签名DLL注入");
        std::cerr << "检测到无效签名DLL注入" << libPath << std::endl;
        return NULL;
    }
    //原始LoadLiabraryA
    return OriginalLoadLibraryA(lpLibFileName);
}

HANDLE WINAPI DLLInjectionProtection::hookedCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
    if (lpStartAddress == nullptr) {
        ExceptionLog::GetInstance()->LogException("检测到非法的远程线程调试");
        std::cerr << "检测到非法的远程线程调试" << std::endl;
        return NULL;
    }
    //原始CreateRemoteThread
    return OriginalCreateRemoteThread(hProcess, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

void DLLInjectionProtection::monitorInjectedDLLs(DWORD processId) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId);
    if (hProcess) {
        HMODULE hModules[1024];
        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, hModules, sizeof(hModules), &cbNeeded)) {
            for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
                char szModName[MAX_PATH];
                if (GetModuleFileNameExA(hProcess, hModules[i], szModName, sizeof(szModName) / sizeof(char))) {
                    std::cout << "已加载模块：" << szModName << std::endl;

                    if (isSuspiciousPath(szModName)) {
                        ExceptionLog::GetInstance()->LogException("检测到可疑DLL注入");
                        std::cerr << "检测到可疑DLL注入" << szModName << std::endl;
                    }
                }
            }
        }
        CloseHandle(hProcess);
    }
}

DLLInjectionProtection::DLLInjectionProtection() {
    OriginalLoadLibraryA = (LoadLibraryA_t)GetProcAddress(GetModuleHandleA(".dll"), "LoadLibraryA");
    OriginalCreateRemoteThread = (CreateRemoteThread_t)GetProcAddress(GetModuleHandleA("dll"), "CreateRemoteThread");
}

void DLLInjectionProtection::initiallizeHooks() {
    DWORD oldProtect;
    // 钩取LoadLibraryA
    VirtualProtect(OriginalLoadLibraryA, sizeof(HMODULE), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(reinterpret_cast<void**>(&OriginalLoadLibraryA)) = reinterpret_cast<void*>(hookedLoadLiabraryA);
    VirtualProtect(OriginalLoadLibraryA, sizeof(HMODULE), oldProtect, &oldProtect);

    // 钩取CreateRemoteThread
    VirtualProtect(OriginalCreateRemoteThread, sizeof(HANDLE), PAGE_EXECUTE_READWRITE, &oldProtect);
    *(reinterpret_cast<void**>(&OriginalCreateRemoteThread)) = reinterpret_cast<void*>(hookedCreateRemoteThread);
    VirtualProtect(OriginalCreateRemoteThread, sizeof(HANDLE), oldProtect, &oldProtect);
}

void DLLInjectionProtection::startMonitoring() {
    DWORD processId = GetCurrentProcessId();
    while (true) {
        monitorInjectedDLLs(processId);
        Sleep(5000);
    }
}

DLLInjectionProtection::~DLLInjectionProtection() {
}