#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "Utils.h"
#include "ExceptionLog.h"
using namespace cv;

class VertificationCode {
private:
    std::string captcha;//验证码

    std::string times;//时间戳1

    std::string timess;//时间戳2

    char randomChar();// 生成随机字符

    Scalar randomColor();// 生成随机颜色

    void drawRandomLines(Mat& img);// 绘制干扰线

    void drawRandomDots(Mat& img);// 绘制干扰点
public:
    VertificationCode();

    std::string GetTimes();
    std::string GetTimess();
    std::string GetVertificationCode();//获取最后一次验证码

    std::string ShowVertificationCode();//显示验证码窗口
    bool TimeValid()//验证时间戳
};