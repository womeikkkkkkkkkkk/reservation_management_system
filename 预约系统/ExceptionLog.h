#pragma once
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

class ExceptionLog//��־��
{
private:
    std::ofstream LogFile;
public:
    ExceptionLog(const std::string& LogFilePath);//����
    ~ExceptionLog();//����
    void LogException(const std::string& ExceptionMessage);//д��־
};