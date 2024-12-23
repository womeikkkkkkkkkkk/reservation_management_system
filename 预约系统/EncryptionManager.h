#pragma once
#include "EncryptionUtils.h"

class EncryptionManager
{
private:
    std::string key;
public:
    EncryptionManager(); // ���캯��
    ~EncryptionManager(); // ��������

    void SetKey(const std::string& key); // ������Կ
    std::string GetKey() const; // ��ȡ��Կ
    std::string EncryptData(const std::string& data); // ��������
    std::string DecryptData(const std::string& encryptedData); // ��������
};