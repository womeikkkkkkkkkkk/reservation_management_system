#include "ExceptionLog.h"

// 初始化静态成员
ExceptionLog* ExceptionLog::instance = nullptr;
std::mutex ExceptionLog::mutex;

// 构造函数
ExceptionLog::ExceptionLog(const std::string& LogFilePath, size_t maxLogFileSize, size_t maxBackupFiles)
    : logFilePath(LogFilePath), maxLogFileSize(maxLogFileSize), maxBackupFiles(maxBackupFiles), isRollingOver(false)
{
    LogFile.open(logFilePath, std::ios::app);
    if (!LogFile)
    {
        throw std::runtime_error("Failed to open log file");
    }
}

// 获取单例实例
ExceptionLog* ExceptionLog::GetInstance(const std::string& LogFilePath, size_t maxLogFileSize, size_t maxBackupFiles)
{
    if (instance == nullptr)
    {
        std::lock_guard<std::mutex> lock(mutex); // 确保线程安全
        if (instance == nullptr)
        {
            instance = new ExceptionLog(LogFilePath, maxLogFileSize, maxBackupFiles);
        }
    }
    return instance;
}

// 获取文件大小
size_t ExceptionLog::GetFileSize(const std::string& filename)
{
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) != 0)
    {
        return 0; // 如果文件无法访问，返回0
    }
    return stat_buf.st_size;
}

// 删除最旧的备份文件
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

    // 排序文件列表，按照文件名进行排序
    std::sort(backupFiles.begin(), backupFiles.end());

    // 删除最旧的备份文件，确保备份文件数目不超过 maxBackupFiles
    while (backupFiles.size() > maxBackupFiles)
    {
        if (remove(backupFiles.front().c_str()) != 0)
        {
            std::cerr << "Error deleting file: " << backupFiles.front() << std::endl;
        }
        backupFiles.erase(backupFiles.begin());
    }
}

// 执行日志文件滚动
void ExceptionLog::RollOverLogFile()
{
    if (isRollingOver)
        return;

    std::lock_guard<std::mutex> lock(mutex); // 确保线程安全

    size_t fileSize = GetFileSize(logFilePath); // 获取文件大小

    if (fileSize >= maxLogFileSize)
    {
        isRollingOver = true;

        // 备份当前日志文件
        std::string backupFile = logFilePath + "." + std::to_string(std::time(nullptr));
        if (rename(logFilePath.c_str(), backupFile.c_str()) != 0)
        {
            std::cerr << "Failed to rename log file" << std::endl;
        }
        RemoveOldBackups(); // 删除旧的备份文件

        // 重新创建日志文件
        LogFile.close();
        LogFile.open(logFilePath, std::ios::app);

        isRollingOver = false;
    }
}

// 日志记录
void ExceptionLog::LogException(const std::string& ExceptionMessage)
{
    std::lock_guard<std::mutex> lock(mutex); // 确保线程安全

    RollOverLogFile(); // 在写日志前检查是否需要滚动日志

    // 获取当前日志级别
    LogFile << GetFormattedLogMessage(ExceptionMessage, INFO) << std::endl;
}

// 获取格式化后的日志消息
std::string ExceptionLog::GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level)
{
    std::stringstream ss;
    std::string currentTime = Utils::GetCurrentTimes("%Y-%m-%d %H:%M:%S");

    ss << currentTime << "[" << LogLevelToString(level) << "] " << ExceptionMessage;
    return ss.str();
}

// 日志级别转换为字符串
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

// 析构函数
ExceptionLog::~ExceptionLog()
{
    if (LogFile.is_open())
    {
        LogFile.close();
    }
}