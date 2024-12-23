#pragma once
#include "EncryptionUtils.h"

std::string EncryotionUtils::GenerateKey() {
    try {
        CryptoPP::AutoSeededRandomPool rng;
        CryptoPP::SecByteBlock key(CryptoPP::AES::DEFAULT_KEYLENGTH);
        rng.GenerateBlock(key, key.size());
        std::string sKey;
        CryptoPP::ArraySource(key, key.size(), true, new CryptoPP::StringSink(sKey));
        return sKey;
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
}

std::string EncryotionUtils::GetKey() {
    std::ifstream ifs;
    std::string key;
    //密钥文件不存在
    try {
        ifs.open(KEY, std::ios::in);
        if (!ifs.is_open()) {
            ifs.close();
            ExceptionLog::GetInstance()->LogException(LOAD_FILE_ERROR);
            return "";
        }
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
    //密钥不存在
    try {
        key = "";
        ifs >> key;
        if (key == "") {
            ExceptionLog::GetInstance()->LogException(KEY_NO_EXIST);
        }
        else {
            return key;
        }
    }
    catch (...) {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
    return key;
}

std::string EncryotionUtils::Encrypt(const std::string& plaintext, const std::string& key) {
    try
    {
        std::string paddedPlaintext = PadData(plaintext, CryptoPP::AES::BLOCKSIZE);

        CryptoPP::SecByteBlock aesKey((const CryptoPP::byte*)key.c_str(), key.size());
        CryptoPP::AES::Encryption aesEncryption(aesKey, aesKey.size());
        CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, aesKey);

        std::string encryptedText;
        CryptoPP::StreamTransformationFilter stfEncrypt(cbcEncryption, new CryptoPP::StringSink(encryptedText));
        stfEncrypt.Put((const CryptoPP::byte*)paddedPlaintext.c_str(), paddedPlaintext.length());
        stfEncrypt.MessageEnd();

        CryptoPP::HexEncoder encoder;
        std::string encodeEncryptedText;
        encoder.Attach(new CryptoPP::StringSink(encodeEncryptedText));
        encoder.Put((const CryptoPP::byte*)encryptedText.c_str(), encryptedText.length());
        encoder.MessageEnd();
        return encodeEncryptedText;
    }
    catch (...)
    {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
}

std::string EncryotionUtils::Decrypt(const std::string& ciphertext, const std::string& key) {
    try
    {
        CryptoPP::SecByteBlock aesKey((const CryptoPP::byte*)key.c_str(), key.size());
        CryptoPP::AES::Decryption aesDecryption(aesKey, aesKey.size());
        CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, aesKey);

        // תΪ
        std::string decodedCiphertext;
        CryptoPP::HexDecoder decoder;
        decoder.Attach(new CryptoPP::StringSink(decodedCiphertext));
        decoder.Put((const CryptoPP::byte*)ciphertext.c_str(), ciphertext.length());
        decoder.MessageEnd();

        std::string decryptedText;
        CryptoPP::StreamTransformationFilter stfDecrypt(cbcDecryption, new CryptoPP::StringSink(decryptedText));
        stfDecrypt.Put((const CryptoPP::byte*)decodedCiphertext.c_str(), decodedCiphertext.length());
        stfDecrypt.MessageEnd();

        // ȥ
        return UnpadData(decryptedText, CryptoPP::AES::BLOCKSIZE);
    }
    catch (...)
    {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
}

std::string EncryotionUtils::PadData(const std::string& data, size_t blockSize) {
    try
    {
        size_t paddingSize = blockSize - (data.size() % blockSize);
        return data + std::string(paddingSize, (char)paddingSize);
    }
    catch (...)
    {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
}

std::string EncryotionUtils::UnpadData(const std::string& paddedData, size_t blockSize) {
    try
    {
        if (paddedData.size() % blockSize != 0)
        {
            ExceptionLog::GetInstance()->LogException(DATA_SIZE_ERROR);
            return ""; //    ݳ  Ȳ
        }
        char paddingValue = paddedData.back();
        if (paddingValue < 1 || paddingValue > blockSize)
        {
            ExceptionLog::GetInstance()->LogException(DATA_FILL_ERROR);
            return ""; //    ֵ
        }
        size_t paddingLength = (size_t)paddingValue;
        for (size_t i = 0; i < paddingLength; ++i)
        {
            if (paddedData[paddedData.size() - 1 - i] != paddingValue)
            {
                ExceptionLog::GetInstance()->LogException(DATA_MARCH_ERROR);
                return ""; //       ݲ һ
            }
        }
        ExceptionLog::GetInstance()->LogException(DATA_SIZE_FILL_MARCH_CORRECT);
        return paddedData.substr(0, paddedData.size() - paddingLength);
    }
    catch (...)
    {
        ExceptionLog::GetInstance()->LogException(UNKNOWN_EXCEPTION_OCCURRED);
        return "";
    }
}