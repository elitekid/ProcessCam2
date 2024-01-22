#ifndef CAMERA_LIST_MODEL_H
#define CAMERA_LIST_MODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QVariantMap>
#include <QQmlListProperty>
#include <QMediaDevices>
#include <QCameraDevice>

class CameraListModel : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QVariantList available_cameras MEMBER available_cameras_ NOTIFY listChanged)

public:
    CameraListModel(QObject* parent = nullptr);

signals:
    void listChanged();

private:
    QVariantList available_cameras_;
};

#endif // CAMERA_LIST_MODEL_H
