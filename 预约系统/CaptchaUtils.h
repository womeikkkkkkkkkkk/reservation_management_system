#pragma once
#include <opencv2/opencv.hpp>
#include <string>

using namespace cv;

class CaptchaUtils {
public:
    // ��������ַ�
    static char randomChar();

    // ���������ɫ
    static Scalar randomColor();

    // ���Ƹ�����
    static void drawRandomLines(Mat& img);

    // ���Ƹ��ŵ�
    static void drawRandomDots(Mat& img);
};
