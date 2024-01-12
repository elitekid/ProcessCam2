#include "cameralistmodel.h"
#include <QQmlListProperty>
#include <QMediaDevices>
#include <QCameraDevice>

CameraListModel::CameraListModel(QObject* parent)
    : QObject(parent)
{
    for (const QCameraDevice& device : QMediaDevices::videoInputs()) {
        QVariantMap cameraMap;
        cameraMap.insert("value", device.position());
        cameraMap.insert("text", device.description());
        m_availableCameras.append(cameraMap);
        emit listChanged();
    }
}