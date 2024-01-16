#pragma once
#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <QtQuick>
#include <QObject>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "util.h"
#include "camera.h"
#include "frame_info.h"
#include "text_geom_store.h"
#include "box_geom_store.h"
#include "cam_geom_store.h"

using namespace cv;
using namespace std;
using namespace Concurrency;

class QtCamObj : public QObject
{
    Q_OBJECT

public:
    explicit QtCamObj(QObject* parent = nullptr);

signals:

public slots:
    void showCam(int camNum, QString colorCode);

private:
    Camera cam;

    frame_info frameInfo;
    cam_geom_store camGeomStore;
    box_geom_store boxGeomStore;
    text_geom_store textGeomStore;

    GLFWwindow* window;

private:
    void processInput(GLFWwindow* window);
};