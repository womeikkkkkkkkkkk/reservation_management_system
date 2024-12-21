#include "VertificationCode.h"

VertificationCode::VertificationCode() {
    this->captcha = "";
    this->times = "";
    this->timess = "";
}

char VertificationCode::randomChar() {
    int type = rand() % 3;
    if (type == 0) {
        return 'A' + rand() % 26;
    }
    else if (type == 1) {
        return 'a' + rand() % 26;
    }
    return '0' + rand() % 10;
}

Scalar VertificationCode::randomColor() {
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    return Scalar(b, g, r);
}

void VertificationCode::drawRandomLines(Mat& img) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int numLines = rand() % 10 + 1;
    for (int i = 0; i < numLines; ++i) {
        Point p1(rand() % img.cols, rand() % img.rows);
        Point p2(rand() % img.cols, rand() % img.rows);
        Scalar color = randomColor();
        line(img, p1, p2, color, 1, LINE_AA);
    }
}

void VertificationCode::drawRandomDots(Mat& img) {
    srand(static_cast<unsigned int>(time(nullptr)));
    int numDots = rand() % 51 + 50;
    for (int i = 0; i < numDots; ++i) {
        Point p(rand() % img.cols, rand() % img.rows);
        Scalar color = randomColor();
        circle(img, p, 1, color, -1, LINE_AA);
    }
}

std::string VertificationCode::GetTimes() {
    return this->times;
}

std::string VertificationCode::GetTimess() {
    return this->timess;
}

std::string VertificationCode::GetVertificationCode() {
    return this->captcha;
}

std::string VertificationCode::ShowVertificationCode() {
    captcha.clear();  // �����֤������
    //��ʼ��ʱ���
    this->times = Utils::GetCurrentTime();
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < 6; ++i) {// ����6λ�����֤��
        this->captcha += randomChar();
    }

    // �����հ�ͼ��
    Mat img(100, 200, CV_8UC3, Scalar(255, 255, 255));

    // ������֤���ַ�
    for (int i = 0; i < this->captcha.length(); ++i) {
        Scalar color = randomColor();
        putText(img, this->captcha.substr(i, 1), Point(20 + 30 * i, 50), FONT_HERSHEY_SIMPLEX, 1, color, 2, LINE_AA);
    }

    // ���Ӹ���������
    drawRandomLines(img);

    // ���Ӹ��ŵ�����
    drawRandomDots(img);

    if (img.empty()) {
        std::cout << "�޷�����ͼ��" << std::endl;
        return "";
    }

    // ����һ������
    namedWindow("ͼ����֤��", WINDOW_NORMAL);
    resizeWindow("ͼ����֤��", 400, 200);

    imshow("ͼ����֤��", img);    // �ڴ�������ʾͼ��
    HWND hwnd = FindWindowA(nullptr, "ͼ����֤��");//���ö��㴰��
    if (hwnd != nullptr) {
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else {
    }
    // �ȴ��û�����
    waitKey(1);
    return this->captcha;
}

bool VertificationCode::TimeValid() {
    ExceptionLog exceptionLog(EXCEPTIONLOG);
    std::string logMsg;
    try {
        if (Utils::TimeCmp(this->GetTimes(), this->GetTimess())) {
            return true;
        }
        else {
            return false;
        }
    }
    catch (...) {
        logMsg = Utils::GetCurrentTime(UNKNOWN_EXCEPTION_OCCURRED);
        logMsg += Utils::GetCurrentTime();
        exceptionLog.LogException(logMsg);
        return;
    }
}