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
#include <filesystem> // ʹ�� C++17 ���ļ�ϵͳ��
#include <sys/stat.h>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <algorithm>
namespace fs = std::filesystem;

class ExceptionLog
{
private:
    static ExceptionLog* instance; // ����ʵ��
    static std::mutex mutex;       // ��������ȷ���̰߳�ȫ
    std::ofstream LogFile;         // ��־�ļ���
    std::string logFilePath;       // ��־�ļ�·��
    size_t maxLogFileSize;         // �����־�ļ���С (�ֽ�)
    size_t maxBackupFiles;         // ��󱸷��ļ�����
    bool isRollingOver;            // �����־�Ƿ��ѹ���

    // ˽�л����캯������ֹ�ⲿʵ����
    ExceptionLog(const std::string& LogFilePath, size_t maxLogFileSize = 10 * 1024 * 1024, size_t maxBackupFiles = 5);

    // ִ����־����
    void RollOverLogFile();

    // ɾ����ɵı����ļ�
    void RemoveOldBackups() const;

    // ��ȡ�ļ���С
    size_t GetFileSize(const std::string& filename);

public:
    // ��ȡ����ʵ��
    static ExceptionLog* GetInstance(const std::string& LogFilePath = EXCEPTIONLOG,
        size_t maxLogFileSize = 10 * 1024 * 1024, // Ĭ�� 10MB
        size_t maxBackupFiles = 5);               // Ĭ����ౣ�� 5 �������ļ�

    // ��־��¼
    void LogException(const std::string& ExceptionMessage);

    // ��־����ö��
    enum LogLevel
    {
        INFO,
        WARN,
        ERROR_,
        DEBUG
    };

    // ������־����
    static const std::string LogLevelToString(LogLevel level);

    // ��־��ʽ������ʱ�����
    std::string GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level);

    // ��������
    ~ExceptionLog();

    // ��ֹ���ƹ��캯���͸�ֵ������
    ExceptionLog(const ExceptionLog&) = delete;
    ExceptionLog& operator=(const ExceptionLog&) = delete;
};

/*
// ʾ��ʹ��
int main()
{
    try
    {
        // ��ȡ��־ʵ������������ļ���СΪ 5MB����ౣ�� 3 �������ļ�
        ExceptionLog* logger = ExceptionLog::GetInstance("application.log", 5 * 1024 * 1024, 3);

        // ��¼��־
        logger->LogException("Application started successfully");

        // ģ����־�ļ�����
        for (int i = 0; i < 10000; ++i)
        {
            logger->LogException("This is a test log message #" + std::to_string(i));
        }
    }
    catch (const std::exception& ex)
    {
        // �����쳣����¼��־
        ExceptionLog::GetInstance()->LogException(ex.what());
    }

    return 0;
}
*/