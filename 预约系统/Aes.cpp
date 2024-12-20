#pragma once
#include "Aes.h"

std::string Aes::GenerateKey() {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        rng.GenerateBlock(key, key.size());
        std::string sKey;
        CryptoPP::ArraySource(key, key.size(), true, new CryptoPP::StringSink(sKey));
        return sKey;
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
}

std::string Aes::GetKey() {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    std::ifstream ifs;
    std::string key;
    try {
        ifs.open(KEY, std::ios::in);
        if (!ifs.is_open()) {
            ifs.close();
            logMsg = Utils::GetCurrentTime(LOAD_FILE_ERROR);
            exceptionLog.LogException(logMsg);
            return "";
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
    try {
        key = "";
        ifs >> key;
        if (key == "") {
            logMsg = Utils::GetCurrentTime(KEY_NO_EXIST);
            exceptionLog.LogException(logMsg);
        }
        else {
            return key;
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
    return key;
}

std::string Aes::Encrypt(const std::string& plaintext, const std::string& key) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        std::string paddedPlaintext = PadData(plaintext, CryptoPP::AES::BLOCKSIZE);
        //填充
        CryptoPP::SecByteBlock aesKey((const CryptoPP::byte*)key.c_str(), key.size());
        CryptoPP::AES::Encryption aesEncryption(aesKey, aesKey.size());
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, aesKey);

        std::string encryptedText;
        CryptoPP::StreamTransformationFilter stfEncrypt(cbcEncryption, new CryptoPP::StringSink(encryptedText));
        stfEncrypt.Put((const CryptoPP::byte*)paddedPlaintext.c_str(), paddedPlaintext.length());
        stfEncrypt.MessageEnd();
        //转为十六进制存储
        CryptoPP::HexEncoder encoder;
        std::string encodeEncryptedText;
        encoder.Attach(new CryptoPP::StringSink(encodeEncryptedText));
        encoder.Put((const CryptoPP::byte*)encryptedText.c_str(), encryptedText.length());
        encoder.MessageEnd();
        return encodeEncryptedText;
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
}

std::string Aes::Decrypt(const std::string& ciphertext, const std::string& key) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        CryptoPP::SecByteBlock aesKey((const CryptoPP::byte*)key.c_str(), key.size());
        CryptoPP::AES::Decryption aesDecryption(aesKey, aesKey.size());
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, aesKey);

        //转为数组
        std::string decodedCiphertext;
        CryptoPP::HexDecoder decoder;
        decoder.Attach(new CryptoPP::StringSink(decodedCiphertext));
        decoder.Put((const CryptoPP::byte*)ciphertext.c_str(), ciphertext.length());
        decoder.MessageEnd();

        std::string decryptedText;
        CryptoPP::StreamTransformationFilter stfDecrypt(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        stfDecrypt.Put((const CryptoPP::byte*)decodedCiphertext.c_str(), decodedCiphertext.length());
        stfDecrypt.MessageEnd();

        // 去除填充的数据
        return UnpadData(decryptedText, CryptoPP::AES::BLOCKSIZE);
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
}

std::string Aes::PadData(const std::string& data, size_t blockSize) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        size_t paddingSize = blockSize - (data.size() % blockSize);
        return data + std::string(paddingSize, (char)paddingSize);
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
}

std::string Aes::UnpadData(const std::string& paddedData, size_t blockSize) {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        if (paddedData.size() % blockSize != 0) {
            logMsg = Utils::GetCurrentTime(DATA_SIZE_ERROR);
            exceptionLog.LogException(logMsg);
            return ""; // 数据长度不符合
        }
        char paddingValue = paddedData.back();
        if (paddingValue < 1 || paddingValue > blockSize) {
            logMsg = Utils::GetCurrentTime(DATA_FILL_ERROR);
            exceptionLog.LogException(logMsg);
            return "";// 填充值不合理
        }
        size_t paddingLength = (size_t)paddingValue;
        for (size_t i = 0; i < paddingLength; ++i) {
            if (paddedData[paddedData.size() - 1 - i] != paddingValue) {
                logMsg = Utils::GetCurrentTime(DATA_MARCH_ERROR);
                exceptionLog.LogException(logMsg);
                return ""; // 填充数据不一致
            }
        }
        logMsg = Utils::GetCurrentTime(DATA_SIZE_FILL_MARCH_CORRECT);
        exceptionLog.LogException(logMsg);
        return paddedData.substr(0, paddedData.size() - paddingLength);
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        exceptionLog.LogException(logMsg);
        return "";
    }
}