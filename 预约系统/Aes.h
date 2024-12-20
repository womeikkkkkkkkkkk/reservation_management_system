#pragma once
#include "aes.h"
#include "filters.h"
#include "hex.h"
#include "string.h"
#include "cryptlib.h"
#include "osrng.h"
#include "modes.h"
#include <string>
#include <vector>
#include "ExceptionLog.h"
#include "GlobalFile.h"
#include "Utils.h"
#include "OutPutMessages.h"
#pragma comment( lib, "cryptlib.lib" )
using namespace CryptoPP;

class Aes {
private:
    static std::string PadData(const std::string& data, size_t blockSize); // PKCS7填充函数
    static std::string UnpadData(const std::string& paddedData, size_t blockSize);// 去除PKCS7填充
public:
    static std::string GenerateKey();// 生成AES加密密钥
    static std::string GetKey();//获取密钥
    static std::string Encrypt(const std::string& plaintext, const std::string& key);// AES加密
    static std::string Decrypt(const std::string& ciphertext, const std::string& key);// AES解密
};