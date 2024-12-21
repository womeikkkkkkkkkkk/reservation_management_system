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
    std::string captcha;//��֤��

    std::string times;//ʱ���1

    std::string timess;//ʱ���2

    char randomChar();// ��������ַ�

    Scalar randomColor();// ���������ɫ

    void drawRandomLines(Mat& img);// ���Ƹ�����

    void drawRandomDots(Mat& img);// ���Ƹ��ŵ�
public:
    VertificationCode();

    std::string GetTimes();
    std::string GetTimess();
    std::string GetVertificationCode();//��ȡ���һ����֤��

    std::string ShowVertificationCode();//��ʾ��֤�봰��
    bool TimeValid()//��֤ʱ���
};