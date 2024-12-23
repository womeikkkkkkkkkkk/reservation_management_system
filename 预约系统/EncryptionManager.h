#pragma once
#include "EncryptionUtils.h"

class EncryptionManager
{
private:
    std::string key;
public:
    EncryptionManager(); // 构造函数
    ~EncryptionManager(); // 析构函数

    void SetKey(const std::string& key); // 设置密钥
    std::string GetKey() const; // 获取密钥
    std::string EncryptData(const std::string& data); // 加密数据
    std::string DecryptData(const std::string& encryptedData); // 解密数据
};