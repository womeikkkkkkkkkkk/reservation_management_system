#include "DatabaseManager.h"

void DatabaseManager::executeQuery(const std::string& query, const std::vector<MYSQL_BIND>& binds) {
    try {
        MYSQL_SLMT* stmt = mysql_stmt_init(conn);
        if (!stmt) {
            throw std::runtime_error(MYSQL_STMT_INIT_FALIED);
        }
        if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
            throw std::runtime_error(MYSQL_STMT_PREPARE_FALIED + std::string(mysql_error(conn)));
        }
        if (mysql_stmt_param(stmt, const_cast<MYSQL_BIND*>(binds.data()))) {
            throw std::runtime_error(MYSQL_STMT_PARAM_FALIED + std::string(mysql_error(stmt)));
        }
        if (mysql_stmt_execute(stmt)) {
            throw std::runtime_error(MYSQL_STMT_EXECUTE_FAILED + std::string(mysql_error(stmt)));
        }
        mysql_stmt_close(stmt);
    }
    catch (const std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw;
    }
}
void DatabaseManager::executeQueryWithResult(const std::string& query, const std::vector<MYSQL_BIND>& binds, MYSQL_RES*& result) {
    try {
        ///初始化查询
        MYSQL_STMT* stmt = mysql_stmt_init(conn);
        if (!stmt) {
            throw std::runtime_error(MYSQL_INIT_STATEMENT_FALIED);
        }
        ///准备查询
        if (mysql_stmt_prepare(stmt, query.c_str(), query.length())) {
            throw std::runtime_error(MYSQL_PREPARE_STATEMENT_FALIED + std::string(mysql_error(conn)));
        }
        ///绑定参数
        if (mysql_stmt_bind_param(stmt, const_cast<MYSQL_BIND*>(binds.data()))) {
            throw std::runtime_error(MYSQL_BIND_PAEAMETERS_BIND_FALIED + std::string(mysql_error(conn)));
        }
        ///执行查询
        if (mysql_stmt_execute(stmt)) {
            throw std::runtime_error(MYSQL_EXECUTE_STATEMENT_FALIED + std::string(mysql_error(conn)));
        }
        ///获取结果集
        result = mysql_stmt_result_metadata(stmt);
        if (!result) {
            throw std::runtime_error(MYSQ_GET_RESULT_METADATA_FALIED + std::string(mysql_error(conn)));
        }

        unsigned int numFields = mysql_num_fields(result);
        std::vector<MYSQL_BIND> resultBinds(numFields);
        std::vector<char*> resultBuffers(numFields);
        ///创建绑定
        for (unsigned int i = 0; i < numFields; i++) {
            resultBuffers[i] = new char[255];
            resultBinds[i].buffer_type = MYSQL_TYPE_STRING;
            resultBinds[i].buffer = resultBuffers[i];
            resultBinds[i].buffer_length = 255;
        }
        ///绑定查询结果
        if (mysql_stmt_bind_result(stmt, resultBinds.data())) {
            throw std::runtime_error(+std::string(mysql_error(conn));
        }
        ///获取结果
        while (mysql_stmt_fetch(stmt) == 0) {
            for (unsigned int i = 0; i < numFields; i++) {
                std::string fieldValue(resultBuffers[i]);
            }
        }
        mysql_stmt_close(stmt);
    }
    catch (const std::exception& e) {
        ExceptionLog::GetInstance()->LogException(e.what());
        throw;
    }
}

bool DatabaseManager::isValidInputs(const std::string& input) const {
    return sqlProtection.isValidInput(input);
}

std::string DatabaseManager::sanitizeInput(const std::string& input) const {
    return std::string(sqlProtection.sanitizeInput(input));
}