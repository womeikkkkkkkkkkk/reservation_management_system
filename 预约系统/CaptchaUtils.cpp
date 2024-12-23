#include "CaptchaUtils.h"
#include <cstdlib>
#include <ctime>

// 生成随机字符
char CaptchaUtils::randomChar()
{
    int type = rand() % 3;
    if (type == 0)
    {
        return 'A' + rand() % 26;  // 大写字母
    }
    else if (type == 1)
    {
        return 'a' + rand() % 26;  // 小写字母
    }
    return '0' + rand() % 10;     // 数字
}

// 生成随机颜色
Scalar CaptchaUtils::randomColor()
{
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return Scalar(b, g, r);  // OpenCV中，颜色格式为 BGR
}

// 绘制干扰线
void CaptchaUtils::drawRandomLines(Mat& img)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int numLines = rand() % 10 + 1;
    for (int i = 0; i < numLines; ++i)
    {
        Point p1(rand() % img.cols, rand() % img.rows);
        Point p2(rand() % img.cols, rand() % img.rows);
        Scalar color = randomColor();
        line(img, p1, p2, color, 1, LINE_AA);  // 绘制干扰线
    }
}

// 绘制干扰点
void CaptchaUtils::drawRandomDots(Mat& img)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int numDots = rand() % 51 + 50;
    for (int i = 0; i < numDots; ++i)
    {
        Point p(rand() % img.cols, rand() % img.rows);
        Scalar color = randomColor();
        circle(img, p, 1, color, -1, LINE_AA);  // 绘制干扰点
    }
}