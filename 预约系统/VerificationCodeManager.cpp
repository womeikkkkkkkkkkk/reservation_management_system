#include "VerificationCodeManager.h"
#include "ExceptionLog.h"
#include <cstdlib>
#include <ctime>

// 构造函数
VerificationCodeManager::VerificationCodeManager()
{
    this->captcha = "";
    this->times = "";
    this->timess = "";
}

// 获取时间戳1
std::string VerificationCodeManager::GetTimes()
{
    return this->times;
}

// 获取时间戳2
std::string VerificationCodeManager::GetTimess()
{
    return this->timess;
}

// 获取验证码
std::string VerificationCodeManager::GetVerificationCode()
{
    return this->captcha;
}

// 显示验证码并返回验证码字符串
std::string VerificationCodeManager::ShowVerificationCode()
{
    this->captcha.clear();  // 清空验证码字符串

    // 获取当前时间戳1
    this->times = Utils::GetCurrentTimes();

    srand(static_cast<unsigned int>(time(nullptr)));

    // 生成6位验证码
    for (int i = 0; i < 6; ++i)
    {
        this->captcha += CaptchaUtils::randomChar();
    }

    // 生成验证码图像
    Mat img(100, 200, CV_8UC3, Scalar(255, 255, 255));  // 白色背景

    // 绘制验证码字符
    for (int i = 0; i < this->captcha.length(); ++i)
    {
        Scalar color = CaptchaUtils::randomColor();
        putText(img, this->captcha.substr(i, 1), Point(20 + 30 * i, 50), FONT_HERSHEY_SIMPLEX, 1, color, 2, LINE_AA);
    }

    // 绘制干扰线和干扰点
    CaptchaUtils::drawRandomLines(img);
    CaptchaUtils::drawRandomDots(img);

    // 如果验证码图像为空，则记录错误并返回空字符串
    if (img.empty())
    {
        std::string errorMsg = "Failed to generate verification image.";
        ExceptionLog::GetInstance()->LogException(errorMsg);
        return "";
    }

    // 显示验证码图像
    namedWindow("Verification Code", WINDOW_NORMAL);
    resizeWindow("Verification Code", 400, 200);
    imshow("Verification Code", img);

    // 将验证码窗口置顶
    HWND hwnd = FindWindowA(nullptr, "Verification Code");
    if (hwnd != nullptr)
    {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    // 等待1毫秒
    waitKey(1);

    return this->captcha;  // 返回验证码
}

// 验证时间戳是否有效
bool VerificationCodeManager::TimeValid()
{
    ExceptionLog* exceptionLog = ExceptionLog::GetInstance();
    try
    {
        // 比较时间戳
        if (Utils::TimeCmp(this->GetTimes(), this->GetTimess()))
        {
            return true;  // 时间戳有效
        }
        else
        {
            return false;  // 时间戳无效
        }
    }
    catch (const std::exception& e)
    {
        // 捕获异常并记录
        std::string logMsg = "Error occurred while validating timestamps: " + std::string(e.what());
        exceptionLog->LogException(logMsg);
        return false;  // 返回时间戳无效
    }
    catch (...)
    {
        // 捕获未知异常并记录
        std::string logMsg = "Unknown exception occurred during time validation.";
        exceptionLog->LogException(logMsg);
        return false;  // 返回时间戳无效
    }
}