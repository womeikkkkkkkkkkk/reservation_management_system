#pragma once
#ifndef DLLINJECTIONPROTECTION_H
#define DLLINJECTIONPROTECTION_H
#include "ExceptionLog.h"
#include "GlobalFile.h"
#include <windows.h>
#include <wintrust.h>
#include <string>
#include <psapi.h>
#include <softpub.h>
#include <detours.h>
#include <memory>
#include <vector>
#include <iostream>
#include <regex>

class DLLInjectionProtection {
private:
    ///API函数指针类型
    typedef HMODULE(WINAPI* LoadLibraryA_t)(LPCSTR lpLibFileName);
    typedef HANDLE(WINAPI* CreateRemoteThread_t)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
        SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
    typedef BOOL(WINAPI* CreateProcessW_t)(
        LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
        LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

    ///API函数指针
    static LoadLibraryA_t OriginalLoadLibraryA;
    static CreateRemoteThread_t OriginalCreateRemoteThread;
    static CreateProcessW_t OriginalCreateProcessW;

    ///拓展环境变量(用于检查路径)
    static std::string expandEnvironmentVariables(const std::string& path);
    ///检查路径
    static bool isSuspiciousPath(const std::string& filePath);
    ///检查DLL签名
    bool isValidSignature(const std::string& filePath) const;
    /// 内存保护
    void protectMemoryExecution(HANDLE hProcess, LPVOID pMemory, SIZE_T size);
    /// 检查 API 劫持
    void checkAPIIntegrity();

    ///钩取LoadLibraryA
    static HMODULE WINAPI hookedLoadLibraryA(LPCSTR lpLibFileName);
    ///钩取CreateRemoteThread
    static HANDLE WINAPI hookedCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
        SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
    ///钩取CreateProcessW
    static BOOL WINAPI hookedCreateProcessW(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment,
        LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);

public:
    std::mutex mtx; // 用于线程同步
    DLLInjectionProtection() { initializeHooks(); }
    /// 初始化钩子
    void initializeHooks();
    /// 启动监控
    void startMonitoring();
    /// 监控进程内存完整性
    void monitorMemoryIntegrity(DWORD processId);
    /// 监控 DLL 注入
    void monitorInjectedDLLs(DWORD processId);
    ///卸载钩子
    void removeHooks();

    ~DLLInjectionProtection();
};
#endif
