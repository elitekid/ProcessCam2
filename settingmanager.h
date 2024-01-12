#ifndef SETTINGMANAGER_H
#define SETTINGMANAGER_H

#include <QObject>
#include <QSettings>
#include <QColor>
#include <QString>

class SettingManager : public QObject
{
    Q_OBJECT

public:
    SettingManager(QObject* parent = nullptr) : QObject(parent) {
        settings = new QSettings("ProcessCam", "elitekid");
        settings->beginGroup("CamSetting");
    }

    Q_INVOKABLE void setFontColor(const QString& color) {
        settings->setValue("fontColor", color);
        settings->sync();
    }
    Q_INVOKABLE QString getFontColor() {
        return settings->value("fontColor", "blue").toString();
    }
    Q_INVOKABLE void setColorCode(const QString& colorCode) {
        if (colorCode.startsWith('#')) {
            // Remove '#' if it's at the beginning
            QString codeWithoutHash = colorCode.mid(1);
            settings->setValue("colorCode", codeWithoutHash);
        }
        else {
            settings->setValue("colorCode", colorCode);
        }
        settings->sync();
    }
    Q_INVOKABLE QString getColorCode() {
        return settings->value("colorCode", "0000ff").toString();
    }

private:
    QSettings* settings;
};

#endif // SETTINGMANAGER_H
