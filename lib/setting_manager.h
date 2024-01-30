#ifndef SETTING_MANAGER_H
#define SETTING_MANAGER_H

#include <QColor>
#include <QObject>
#include <QSettings>
#include <QFontDatabase>
#include <QString>

#include "util.h"

class SettingManager : public QObject {
  Q_OBJECT

 public:
  SettingManager();

  Q_INVOKABLE void SetCamera(const int camera_num);
  Q_INVOKABLE void SetFont(const QString& font);
  Q_INVOKABLE void SetFontPath(const QString& font_path);
  Q_INVOKABLE void SetFontColor(const QString& color);
  Q_INVOKABLE void SetColorCode(const QString& color);
  Q_INVOKABLE void SetFullScreenMode(const bool checked);

  Q_INVOKABLE int GetCamera();
  Q_INVOKABLE QString GetFont();
  Q_INVOKABLE QString GetFontPath();
  Q_INVOKABLE QString GetFontColor();
  Q_INVOKABLE QString GetColorCode();
  Q_INVOKABLE bool GetFullScreenMode();

 private:
  QSettings* settings_;
};

#endif  // SETTING_MANAGER_H