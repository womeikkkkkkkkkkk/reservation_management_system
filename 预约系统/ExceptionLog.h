#pragma once
#ifndef EXCEPTIONLOG_H
#define EXCEPTIONLOG_H
#include "TimeUtils.h"
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <sstream>
#include <iostream>
#include <filesystem>  // C++17 文件系统库
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <thread>
#include <exception>
namespace fs = std::filesystem;

class ExceptionLog {
private:
    static ExceptionLog* instance; // 单例实例
    static std::mutex mutex;       // 互斥锁，确保线程安全
    std::ofstream logFile;         // 日志文件流
    std::string logFilePath;       // 日志文件路径
    size_t maxLogFileSize;         // 最大日志文件大小 (字节)
    size_t maxBackupFiles;         // 最大备份文件数量
    bool logToConsole;             // 是否输出到控制台
    bool isRollingOver;            // 是否进行日志滚动
    bool appendTimestamp;          // 是否在日志中添加时间戳
    bool appendLevel;              // 是否在日志中添加日志级别
    bool appendThreadID;           // 是否输出线程ID

    // 私有化构造函数，防止外部实例化
    ExceptionLog(const std::string& logFilePath, size_t maxLogFileSize = 10 * 1024 * 1024, size_t maxBackupFiles = 5, bool logToConsole = true, bool appendTimestamp = true, bool appendLevel = true, bool appendThreadID = false);

    // 执行日志滚动
    void RollOverLogFile();

    // 删除最旧的备份文件
    void RemoveOldBackups() const;

    // 获取文件大小
    size_t GetFileSize(const std::string& filename);

public:
    enum LogLevel {
        INFO,
        WARN,
        ERROR_,
        DEBUG
    };
    // 获取单例实例
    static ExceptionLog* GetInstance(const std::string& logFilePath = EXCEPTIONLOG,
        size_t maxLogFileSize = 10 * 1024 * 1024,
        size_t maxBackupFiles = 5,
        bool logToConsole = true,
        bool appendTimestamp = true,
        bool appendLevel = true,
        bool appendThreadID = false);

    // 日志记录
    void LogException(const std::string& message, LogLevel level = INFO);

    // 设置日志级别
    static const std::string LogLevelToString(LogLevel level);

    // 日志格式化（带时间戳）
    std::string GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level);

    void LogToConsole(const std::string& message);

    void LogToFile(const std::string& message);
    // 析构函数
    ~ExceptionLog();

    // 禁止复制构造函数和赋值操作符
    ExceptionLog(const ExceptionLog&) = delete;
    ExceptionLog& operator=(const ExceptionLog&) = delete;
};
#endif

/*
使用方法：
    ExceptionLog*logger = ExceptionLog::GetInsetance();

    logger->LogException(
    std::string messages,
    可选参数:ExceptionLog::INFO
            :ExceptionLOG::WARN
            :ExceptionLog::ERROR_
            :ExceptionLOG::DEBUG);

    std::thread t1[&logger] {
        logger->LogException(
        std::string messages,
        可选参数:ExceptionLOG::INFO
                :ExceptionLOG::WARN
                :ExceptionLOG::ERROR_
                :ExceptionLOG::DEBUG);}
    t1.join();

    */
