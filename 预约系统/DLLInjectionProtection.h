#pragma once
#ifndef DLLINJECTIONPROTECTION_H
#define DLLINJECTIONPROTECTION_H
#include "ExceptionLog.h"
#include <windows.h>
#include <wintrust.h>
#include <string>
#include <psapi.h>
#include <softpub.h>
#include <memory>
#include <vector>
#include <iostream>

class DLLInjectionProtection {
private:
    //API函数指针类型
    typedef HMODULE(WINAPI* LoadLibraryA_t)(LPCSTR lpLibFileName);
    typedef HANDLE(WINAPI* CreateRemoteThread_t)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
        SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
    //API函数指针
    LoadLibraryA_t OriginalLoadLibraryA = nullptr;
    CreateRemoteThread_t OriginalCreateRemoteThread = nullptr;
    //检查路径
    bool isSuspiciousPath(const std::string& fliePath);
    //检查DLL签名
    bool isValidSignature(const std::string& filePath);
    //钩取LoadLibraryA
    HMODULE WINAPI hookedLoadLiabraryA(LPCSTR lpLibFileName);
    //钩取CreateRemoteThread
    HANDLE WINAPI hookedCreateRemoteThread(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes,
        SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress,
        LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
    //监控已加载的DLL
    void monitorInjectedDLLs(DWORD processId);
public:
    DLLInjectionProtection();
    //初始化钩子
    void initiallizeHooks();
    //启动监控
    void startMonitoring();

    ~DLLInjectionProtection();
};
#endif
