#ifndef SETTING_MANAGER_H
#define SETTING_MANAGER_H

#include <QColor>
#include <QObject>
#include <QSettings>
#include <QString>

class SettingManager : public QObject {
  Q_OBJECT

 public:
  SettingManager();

  Q_INVOKABLE void SetFontColor(const QString& color);
  Q_INVOKABLE QString GetFontColor();
  Q_INVOKABLE void SetColorCode(const QString& colorCode);
  Q_INVOKABLE QString GetColorCode();

 private:
  QSettings* settings_;
};

#endif  // SETTING_MANAGER_H