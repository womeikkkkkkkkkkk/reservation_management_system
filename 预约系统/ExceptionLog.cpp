#include "ExceptionLog.h"

// 初始化静态成员
ExceptionLog* ExceptionLog::instance = nullptr;
std::mutex ExceptionLog::mutex;

ExceptionLog::ExceptionLog(const std::string& logFilePath, size_t maxLogFileSize, size_t maxBackupFiles, bool logToConsole, bool appendTimestamp, bool appendLevel, bool appendThreadID)
    : logFilePath(logFilePath),
    maxLogFileSize(maxLogFileSize),
    maxBackupFiles(maxBackupFiles),
    logToConsole(logToConsole),
    appendTimestamp(appendTimestamp),
    appendLevel(appendLevel),
    appendThreadID(appendThreadID),
    isRollingOver(false) {
    logFile.open(logFilePath, std::ios::app);
    if (!logFile) {
        throw std::runtime_error(LOG_OPEN_FALIED + logFilePath);
    }
}

// 获取单例实例
ExceptionLog* ExceptionLog::GetInstance(const std::string& logFilePath, size_t maxLogFileSize, size_t maxBackupFiles, bool logToConsole, bool appendTimestamp, bool appendLevel, bool appendThreadID) {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(mutex); // 确保线程安全
        if (instance == nullptr) {
            instance = new ExceptionLog(logFilePath, maxLogFileSize, maxBackupFiles, logToConsole, appendTimestamp, appendLevel, appendThreadID);
        }
    }
    return instance;
}

// 获取文件大小
size_t ExceptionLog::GetFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    return file.tellg();
}

// 删除最旧的备份文件
void ExceptionLog::RemoveOldBackups() const {
    std::vector<std::string> backupFiles;

    for (const auto& entry : fs::directory_iterator(".")) {
        std::string filename = entry.path().filename().string();
        if (filename.find(EXCEPTIONLOG) != std::string::npos) {
            backupFiles.push_back(filename);
        }
    }

    // 排序文件列表，按照文件名进行排序
    std::sort(backupFiles.begin(), backupFiles.end());

    // 删除最旧的备份文件，确保备份文件数目不超过 maxBackupFiles
    while (backupFiles.size() > maxBackupFiles) {
        if (remove(backupFiles.front().c_str()) != 0) {
            std::cerr << LOG_DELETE_FALIED << backupFiles.front() << std::endl;
        }
        backupFiles.erase(backupFiles.begin());
    }
}

// 执行日志文件滚动
void ExceptionLog::RollOverLogFile() {
    if (isRollingOver)
        return;

    std::lock_guard<std::mutex> lock(mutex); // 确保线程安全

    size_t fileSize = GetFileSize(logFilePath); // 获取文件大小

    if (fileSize >= maxLogFileSize) {
        isRollingOver = true;

        // 备份当前日志文件
        std::string backupFile = logFilePath + "." + std::to_string(std::time(nullptr));
        if (rename(logFilePath.c_str(), backupFile.c_str()) != 0) {
            std::cerr << RENMA_LOG_FILE_FALIED << std::endl;
        }
        RemoveOldBackups(); // 删除旧的备份文件

        // 重新创建日志文件
        logFile.close();
        logFile.open(logFilePath, std::ios::app);

        isRollingOver = false;
    }
}

// 日志记录
void ExceptionLog::LogException(const std::string& ExceptionMessage, LogLevel level) {
    std::string formattedMessage = GetFormattedLogMessage(ExceptionMessage, level);

    if (logToConsole) {
        LogToConsole(formattedMessage);
    }

    if (logFile.is_open()) {
        LogToFile(formattedMessage);
    }

    if (isRollingOver) {
        RollOverLogFile();
    }
}

// 获取格式化后的日志消息
std::string ExceptionLog::GetFormattedLogMessage(const std::string& ExceptionMessage, LogLevel level) {
    std::stringstream ss;
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);

    if (appendTimestamp) {
        ss << "[" << timeBuffer << "] ";
    }

    if (appendLevel) {
        ss << "[" << LogLevelToString(level) << "] ";
    }

    if (appendThreadID) {
        ss << "[Thread " << std::this_thread::get_id() << "] ";
    }

    ss << ExceptionMessage;
    return ss.str();
}

// 日志级别转换为字符串
const std::string ExceptionLog::LogLevelToString(LogLevel level) {
    switch (level) {
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

// 输出到控制台
void ExceptionLog::LogToConsole(const std::string& message) {
    std::cout << message << std::endl;
}

// 输出到文件
void ExceptionLog::LogToFile(const std::string& message) {
    logFile << message << std::endl;
}

// 析构函数
ExceptionLog::~ExceptionLog() {
    if (logFile.is_open()) {
        logFile.close();
    }
}