#include "camera_list_model.h"


CameraListModel::CameraListModel(QObject* parent)
    : QObject(parent)
{
    for (const QCameraDevice& device : QMediaDevices::videoInputs()) {
        QVariantMap cameraMap;
        cameraMap.insert("value", device.position());
        cameraMap.insert("text", device.description());
        available_cameras_.append(cameraMap);
        emit listChanged();
    }
}