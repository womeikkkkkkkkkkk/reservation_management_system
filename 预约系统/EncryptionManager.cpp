#include "EncryptionManager.h"

EncryptionManager::EncryptionManager() {
    this->key = EncryotionUtils::GetKey();
}

EncryptionManager::~EncryptionManager() {
}

void EncryptionManager::SetKey(const std::string& key) {
    this->key = key;
}

std::string EncryptionManager::GetKey() const {
    return this->key;
}

std::string EncryptionManager::EncryptData(const std::string& data) {
    return EncryotionUtils::Encrypt(data, this->key);
}

std::string EncryptionManager::DecryptData(const std::string& encryptedData) {
    return EncryotionUtils::Decrypt(encryptedData, this->key);
}