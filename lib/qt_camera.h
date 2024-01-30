// Copyright 2024 elitekid

#ifndef QT_CAMERA_H_
#define QT_CAMERA_H_

#include <windows.h>

#include <glad/glad.h>
#include <QtQuick>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <glm/gtx/transform.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "setting_manager.h"
#include "util.h"
#include "camera.h"
#include "frame_info.h"
#include "text_geom_store.h"
#include "box_geom_store.h"
#include "cam_geom_store.h"

using namespace cv;
using namespace std;
using namespace Concurrency;

class QtCamera : public QObject
{
    Q_OBJECT

public:
    explicit QtCamera(QObject* parent = nullptr);

signals:

public slots:
    void ShowCam();

private:
    Camera cam_;
    SettingManager setting_manager_;

    FrameInfo frame_info_;
    CamGeomStore cam_geom_store_;
    BoxGeomStore box_geom_store_;
    TextGeomStore text_geom_store_;

    GLFWwindow* window_;

   private:
    void processInput(GLFWwindow* window);
};

#endif  // QT_CAMERA_H_