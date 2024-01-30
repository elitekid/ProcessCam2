#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QtDebug>
#include <QColor>

#include "lib/util.h"
#include "lib/qt_camera.h"
#include "lib/camera_list_model.h"
#include "lib/font_list_model.h"
#include "lib/setting_manager.h"

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
    QtCamera qt_camera;

    //database.applicationFontFamilies(database.styles("Arial").first());
    // QQmlContext에 Cam 객체 등록
    engine.rootContext()->setContextProperty("qt_camera", &qt_camera);

    // 연결된 카메라 목록을 관리하는 모델 객체 생성
    CameraListModel camera_list_model;

    // 연결된 카메라 목록을 관리하는 모델 객체 생성
    FontListModel font_list_model;
    
    // 설정 관리자 객체 생성
    SettingManager setting_manager;

    // QQmlContext에 모델 객체 및 설정 관리자 객체 등록
    engine.rootContext()->setContextProperty("camera_list_model", &camera_list_model);
    engine.rootContext()->setContextProperty("font_list_model", &font_list_model);
    engine.rootContext()->setContextProperty("setting_manager", &setting_manager);

    // QML 파일 로드
    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/processcam2/main.qml")));

    // QML 파일 로드에 실패한 경우 종료
    if (engine.rootObjects().isEmpty())
        return -1;

    // 어플리케이션 이벤트 루프 실행
    return app.exec();
}
