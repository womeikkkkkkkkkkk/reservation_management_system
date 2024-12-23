#include "ExceptionLog.h"

// ��ʼ����̬��Ա
ExceptionLog* ExceptionLog::instance = nullptr;
std::mutex ExceptionLog::mutex;

// ���캯��
ExceptionLog::ExceptionLog(const std::string& LogFilePath, size_t maxLogFileSize, size_t maxBackupFiles)
    : logFilePath(LogFilePath), maxLogFileSize(maxLogFileSize), maxBackupFiles(maxBackupFiles), isRollingOver(false)
{
    LogFile.open(logFilePath, std::ios::app);
    if (!LogFile)
    {
        throw std::runtime_error("Failed to open log file");
    }
}

// ��ȡ����ʵ��
ExceptionLog* ExceptionLog::GetInstance(const std::string& LogFilePath, size_t maxLogFileSize, size_t maxBackupFiles)
{
    if (instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex); // ȷ���̰߳�ȫ
        if (instance == nullptr)
        {
            instance = new ExceptionLog(LogFilePath, maxLogFileSize, maxBackupFiles);
        }
    }
    return instance;
}

// ��ȡ�ļ���С
size_t ExceptionLog::GetFileSize(const std::string& filename)
{
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) != 0)
    {
        return 0; // ����ļ��޷����ʣ�����0
    }
    return stat_buf.st_size;
}

// ɾ����ɵı����ļ�
void ExceptionLog::RemoveOldBackups() const
{
    std::vector<std::string> backupFiles;

    for (const auto& entry : fs::directory_iterator("."))
    {
        std::string filename = entry.path().filename().string();
        if (filename.find("exception.log") != std::string::npos)
        {
            backupFiles.push_back(filename);
        }
    }

    // �����ļ��б������ļ�����������
    std::sort(backupFiles.begin(), backupFiles.end());

    // ɾ����ɵı����ļ���ȷ�������ļ���Ŀ������ maxBackupFiles
    while (backupFiles.size() > maxBackupFiles)
    {
        if (remove(backupFiles.front().c_str()) != 0)
        {
            std::cerr << "Error deleting file: " << backupFiles.front() << std::endl;
        }
        backupFiles.erase(backupFiles.begin());
    }
}

// ִ����־�ļ�����
void ExceptionLog::RollOverLogFile()
{
    if (isRollingOver)
        return;

    std::lock_guard<std::mutex> lock(mutex); // ȷ���̰߳�ȫ

    size_t fileSize = GetFileSize(logFilePath); // ��ȡ�ļ���С

    if (fileSize >= maxLogFileSize)
    {
        isRollingOver = true;

        // ���ݵ�ǰ��־�ļ�
        std::string backupFile = logFilePath + "." + std::to_string(std::time(nullptr));
        if (rename(logFilePath.c_str(), backupFile.c_str()) != 0)
        {
            std::cerr << "Failed to rename log file" << std::endl;
        }
        RemoveOldBackups(); // ɾ���ɵı����ļ�

        // ���´�����־�ļ�
        LogFile.close();
        LogFile.open(logFilePath, std::ios::app);

        isRollingOver = false;
    }
}

// ��־��¼
void ExceptionLog::LogException(const std::string& ExceptionMessage)
{
    std::lock_guard<std::mutex> lock(mutex); // ȷ���̰߳�ȫ

    RollOverLogFile(); // ��д��־ǰ����Ƿ���Ҫ������־

    // ��ȡ��ǰ��־����
    LogFile << GetFormattedLogMessage(ExceptionMessage, INFO) << std::endl;
}

// ��ȡ��ʽ�������־��Ϣ
std::string ExceptionLog::GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level)
{
    std::stringstream ss;
    std::string currentTime = Utils::GetCurrentTimes("%Y-%m-%d %H:%M:%S");

    ss << currentTime << "[" << LogLevelToString(level) << "] " << ExceptionMessage;
    return ss.str();
}

// ��־����ת��Ϊ�ַ���
const std::string ExceptionLog::LogLevelToString(LogLevel level)
{
    switch (level)
    {
    case INFO:
        return "INFO";
    case WARN:
        return "WARN";
    case ERROR_:
        return "ERROR";
    case DEBUG:
        return "DEBUG";
    default:
        return "UNKNOWN";
    }
}

// ��������
ExceptionLog::~ExceptionLog()
{
    if (LogFile.is_open())
    {
        LogFile.close();
    }
}