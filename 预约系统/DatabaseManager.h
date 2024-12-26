#pragma once
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include "SQLInjectionProtection.h"
#include "ExceptionLog.h"
#include <mysql.h>
#include <string>
#include <vector>
#include <memory>

class DatabaseManager {
private:
    MYSQL* conn;
    bool isConnected;///连接状态
    int reconnectAttempts;///重连次数
    int reconnectDelayMs;///重连间隔
    SQLInjectionProtection sqlProtection;///SQL防护

public:
    DatabaseManager(int maxReconnectAttempts = 3, int reconnectDelayMs = 2000) : conn(nullptr), isConnected(false), reconnectAttempts(maxReconnectAttempts), reconnectDelayMs(reconnectDelayMs) {}
    ///链接
    void connect(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname);
    ///退出
    void logout(const std::string& username, const std::string& password);
    ///查询，SQL绑定
    void executeQuery(const std::string& query, const std::vector<MYSQL_BIND>& binds);
    ///查询返回结果
    void executeQueryWithResult(const std::string& query, const std::vector<MYSQL_BIND>& binds, MYSQL_RES*& result);
    ///校验输入
    bool isValidInputs(const std::string& input)const;
    ///清洗输入
    std::string sanitizeInput(const std::string& input)const;
};
#endif