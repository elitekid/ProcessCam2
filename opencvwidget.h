#pragma once

#include <QtQuick>
#include <QObject>
#include <QQuickPaintedItem>
#include <QImage>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "util.h"
using namespace cv;

class CamObj : public QObject
{
    Q_OBJECT

public:
    explicit CamObj(QObject* parent = nullptr);

public slots:
    void showCam(int camNum, QString colorCode);
};

class ThreadedCamera {
public:
    ;
    // 초기화 함수 구현
    void initialize(int camNum) {
        stop(); // 이미 카메라가 열려 있다면 중지

        cap.open(camNum, cv::CAP_DSHOW);
        double codec = 0x47504A4D; // MJPG

        cap.set(CAP_PROP_FOURCC, codec);
        //cap.open("C:/Users/SYNERGY-USER/Downloads/abc/bear.mp4", cv::CAP_V4L2);
        cap.set(CAP_PROP_FPS, 24);
        cap.set(CAP_PROP_FRAME_WIDTH, 2560);
        cap.set(CAP_PROP_FRAME_HEIGHT, 1440);

        status = false;
        frame = Mat();
    }

    Mat grabFrame() {
        if (cap.isOpened()) {
            status = cap.read(frame);
        }

        if (status) {
            return frame;
        }
        return Mat();
    }

    void stop() {
        cap.release();
    }

    int getCols() const {
        if (cap.isOpened()) {
            return static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH));
        }
        return 0;
    }

    int getRows() const {
        if (cap.isOpened()) {
            return static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT));
        }
        return 0;
    }

private:
    VideoCapture cap;
    bool status;
    Mat frame;
};