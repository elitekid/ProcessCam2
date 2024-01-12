#ifndef CAMERALISTMODEL_H
#define CAMERALISTMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QVariantMap>

class CameraListModel : public QObject
{
    Q_OBJECT
        Q_PROPERTY(QVariantList availableCameras MEMBER m_availableCameras NOTIFY listChanged)

public:
    CameraListModel(QObject* parent = nullptr);

signals:
    void listChanged();

private:
    QVariantList m_availableCameras;
};

#endif // CAMERALISTMODEL_H
