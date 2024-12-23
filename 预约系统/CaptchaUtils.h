#pragma once
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

class CaptchaUtils {
public:
    // 生成随机字符
    static char randomChar();

    // 生成随机颜色
    static Scalar randomColor();

    // 绘制干扰线
    static void drawRandomLines(Mat& img);

    // 绘制干扰点
    static void drawRandomDots(Mat& img);
};
