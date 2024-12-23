#pragma once
#include "TimeUtils.h"
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>
#include <cstdio>
#include <filesystem> // 使用 C++17 的文件系统库
#include <sys/stat.h>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <algorithm>
namespace fs = std::filesystem;

class ExceptionLog
{
private:
    static ExceptionLog* instance; // 单例实例
    static std::mutex mutex;       // 互斥锁，确保线程安全
    std::ofstream LogFile;         // 日志文件流
    std::string logFilePath;       // 日志文件路径
    size_t maxLogFileSize;         // 最大日志文件大小 (字节)
    size_t maxBackupFiles;         // 最大备份文件数量
    bool isRollingOver;            // 标记日志是否已滚动

    // 私有化构造函数，防止外部实例化
    ExceptionLog(const std::string& LogFilePath, size_t maxLogFileSize = 10 * 1024 * 1024, size_t maxBackupFiles = 5);

    // 执行日志滚动
    void RollOverLogFile();

    // 删除最旧的备份文件
    void RemoveOldBackups() const;

    // 获取文件大小
    size_t GetFileSize(const std::string& filename);

public:
    // 获取单例实例
    static ExceptionLog* GetInstance(const std::string& LogFilePath = EXCEPTIONLOG,
        size_t maxLogFileSize = 10 * 1024 * 1024, // 默认 10MB
        size_t maxBackupFiles = 5);               // 默认最多保留 5 个备份文件

    // 日志记录
    void LogException(const std::string& ExceptionMessage);

    // 日志级别枚举
    enum LogLevel
    {
        INFO,
        WARN,
        ERROR_,
        DEBUG
    };

    // 设置日志级别
    static const std::string LogLevelToString(LogLevel level);

    // 日志格式化（带时间戳）
    std::string GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level);

    // 析构函数
    ~ExceptionLog();

    // 禁止复制构造函数和赋值操作符
    ExceptionLog(const ExceptionLog&) = delete;
    ExceptionLog& operator=(const ExceptionLog&) = delete;
};

/*
// 示例使用
int main()
{
    try
    {
        // 获取日志实例，设置最大文件大小为 5MB，最多保留 3 个备份文件
        ExceptionLog* logger = ExceptionLog::GetInstance("application.log", 5 * 1024 * 1024, 3);

        // 记录日志
        logger->LogException("Application started successfully");

        // 模拟日志文件增长
        for (int i = 0; i < 10000; ++i)
        {
            logger->LogException("This is a test log message #" + std::to_string(i));
        }
    }
    catch (const std::exception& ex)
    {
        // 捕获异常并记录日志
        ExceptionLog::GetInstance()->LogException(ex.what());
    }

    return 0;
}
*/