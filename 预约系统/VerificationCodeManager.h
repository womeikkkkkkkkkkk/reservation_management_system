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
    std::string captcha;  // 验证码
    std::string times;    // 时间戳1
    std::string timess;   // 时间戳2

    // 验证时间戳是否有效
    bool TimeValid();

public:
    VerificationCodeManager();

    // 获取时间戳1
    std::string GetTimes();

    // 获取时间戳2
    std::string GetTimess();

    // 获取验证码
    std::string GetVerificationCode();

    // 显示验证码并返回验证码字符串
    std::string ShowVerificationCode();
};
