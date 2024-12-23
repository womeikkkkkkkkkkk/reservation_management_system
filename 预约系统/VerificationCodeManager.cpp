#include "VerificationCodeManager.h"
#include "ExceptionLog.h"
#include <cstdlib>
#include <ctime>

// ���캯��
VerificationCodeManager::VerificationCodeManager()
{
    this->captcha = "";
    this->times = "";
    this->timess = "";
}

// ��ȡʱ���1
std::string VerificationCodeManager::GetTimes()
{
    return this->times;
}

// ��ȡʱ���2
std::string VerificationCodeManager::GetTimess()
{
    return this->timess;
}

// ��ȡ��֤��
std::string VerificationCodeManager::GetVerificationCode()
{
    return this->captcha;
}

// ��ʾ��֤�벢������֤���ַ���
std::string VerificationCodeManager::ShowVerificationCode()
{
    this->captcha.clear();  // �����֤���ַ���

    // ��ȡ��ǰʱ���1
    this->times = Utils::GetCurrentTimes();

    srand(static_cast<unsigned int>(time(nullptr)));

    // ����6λ��֤��
    for (int i = 0; i < 6; ++i)
    {
        this->captcha += CaptchaUtils::randomChar();
    }

    // ������֤��ͼ��
    Mat img(100, 200, CV_8UC3, Scalar(255, 255, 255));  // ��ɫ����

    // ������֤���ַ�
    for (int i = 0; i < this->captcha.length(); ++i)
    {
        Scalar color = CaptchaUtils::randomColor();
        putText(img, this->captcha.substr(i, 1), Point(20 + 30 * i, 50), FONT_HERSHEY_SIMPLEX, 1, color, 2, LINE_AA);
    }

    // ���Ƹ����ߺ͸��ŵ�
    CaptchaUtils::drawRandomLines(img);
    CaptchaUtils::drawRandomDots(img);

    // �����֤��ͼ��Ϊ�գ����¼���󲢷��ؿ��ַ���
    if (img.empty())
    {
        std::string errorMsg = "Failed to generate verification image.";
        ExceptionLog::GetInstance()->LogException(errorMsg);
        return "";
    }

    // ��ʾ��֤��ͼ��
    namedWindow("Verification Code", WINDOW_NORMAL);
    resizeWindow("Verification Code", 400, 200);
    imshow("Verification Code", img);

    // ����֤�봰���ö�
    HWND hwnd = FindWindowA(nullptr, "Verification Code");
    if (hwnd != nullptr)
    {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    // �ȴ�1����
    waitKey(1);

    return this->captcha;  // ������֤��
}

// ��֤ʱ����Ƿ���Ч
bool VerificationCodeManager::TimeValid()
{
    ExceptionLog* exceptionLog = ExceptionLog::GetInstance();
    try
    {
        // �Ƚ�ʱ���
        if (Utils::TimeCmp(this->GetTimes(), this->GetTimess()))
        {
            return true;  // ʱ�����Ч
        }
        else
        {
            return false;  // ʱ�����Ч
        }
    }
    catch (const std::exception& e)
    {
        // �����쳣����¼
        std::string logMsg = "Error occurred while validating timestamps: " + std::string(e.what());
        exceptionLog->LogException(logMsg);
        return false;  // ����ʱ�����Ч
    }
    catch (...)
    {
        // ����δ֪�쳣����¼
        std::string logMsg = "Unknown exception occurred during time validation.";
        exceptionLog->LogException(logMsg);
        return false;  // ����ʱ�����Ч
    }
}