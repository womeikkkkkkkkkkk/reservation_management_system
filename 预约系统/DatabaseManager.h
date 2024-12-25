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
    SQLInjectionProtection sqlProtection;
public:
    DatabaseManager(MYSQL* connection) : conn(connection) {}
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