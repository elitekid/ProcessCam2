#include "setting_manager.h"

SettingManager::SettingManager() : QObject(nullptr) {
  settings_ = new QSettings("ProcessCam", "elitekid");
  settings_->beginGroup("CamSetting");
}

void SettingManager::SetFontColor(const QString& color) {
  settings_->setValue("fontColor", color);
  settings_->sync();
}

QString SettingManager::GetFontColor() {
  return settings_->value("fontColor", "blue").toString();
}

void SettingManager::SetColorCode(const QString& colorCode) {
  if (colorCode.startsWith('#')) {
    QString codeWithoutHash = colorCode.mid(1);
    settings_->setValue("colorCode", codeWithoutHash);
  } else {
    settings_->setValue("colorCode", colorCode);
  }
  settings_->sync();
}

QString SettingManager::GetColorCode() {
  return settings_->value("colorCode", "0000ff").toString();
}
