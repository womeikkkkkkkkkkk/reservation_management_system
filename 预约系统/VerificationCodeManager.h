#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <Windows.h>
#include "CaptchaUtils.h"
#include "TimeUtils.h"
#include "ExceptionLog.h"

using namespace cv;

class VerificationCodeManager {
private:
    std::string captcha;  // ��֤��
    std::string times;    // ʱ���1
    std::string timess;   // ʱ���2

    // ��֤ʱ����Ƿ���Ч
    bool TimeValid();

public:
    VerificationCodeManager();

    // ��ȡʱ���1
    std::string GetTimes();

    // ��ȡʱ���2
    std::string GetTimess();

    // ��ȡ��֤��
    std::string GetVerificationCode();

    // ��ʾ��֤�벢������֤���ַ���
    std::string ShowVerificationCode();
};
