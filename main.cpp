#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QtDebug>
#include <QColor>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "opencvwidget.h"
#include "cameralistmodel.h"
#include "settingmanager.h"

int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    // Qt GUI 어플리케이션 초기화
    QGuiApplication app(argc, argv);

    // QQmlApplicationEngine 객체 생성
    QQmlApplicationEngine engine;

    // Cam 객체 생성
    CamObj camObj;

    // QQmlContext에 Cam 객체 등록
    engine.rootContext()->setContextProperty("camObj", &camObj);

    // 연결된 카메라 목록을 관리하는 모델 객체 생성
    CameraListModel cameraListModel;

    // 설정 관리자 객체 생성
    SettingManager settingManager;

    // QQmlContext에 모델 객체 및 설정 관리자 객체 등록
    engine.rootContext()->setContextProperty("cameraListModel", &cameraListModel);
    engine.rootContext()->setContextProperty("settingManager", &settingManager);

    // QML 파일 로드
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/processcam2/main.qml")));

    // QML 파일 로드에 실패한 경우 종료
    if (engine.rootObjects().isEmpty())
        return -1;

    // 어플리케이션 이벤트 루프 실행
    return app.exec();
}
