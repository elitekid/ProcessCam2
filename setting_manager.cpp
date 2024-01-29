#include "setting_manager.h"

SettingManager::SettingManager() : QObject(nullptr) {
  settings_ = new QSettings("ProcessCam", "elitekid");
  settings_->beginGroup("CamSetting");
}

void SettingManager::SetCamera(const int camera_num) {
  settings_->setValue("camera", camera_num);
  settings_->sync();
}

void SettingManager::SetFont(const QString& font) {
  settings_->setValue("font", font);
  settings_->sync();
}

void SettingManager::SetFontPath(const QString& font_path) {
  settings_->setValue("fontPath", font_path);
  settings_->sync();
}

void SettingManager::SetFontColor(const QString& color) {
  settings_->setValue("fontColor", color);
  settings_->sync();
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

void SettingManager::SetFullScreenMode(const bool checked) {
  settings_->setValue("isFullWindow", checked);
  settings_->sync();
}

int SettingManager::GetCamera() {
  return settings_->value("camera", 0).toInt();
}

QString SettingManager::GetFont() {
  std::filesystem::path absolutePath = Utils::GetFontPath();

  QString defaultFont;
  for (const auto& entry : std::filesystem::directory_iterator(absolutePath)) {
  // 폰트 데이터베이스를 가져옵니다.
  QFontDatabase fontDatabase;

  // 폰트 경로를 사용하여 폰트 ID를 가져옵니다.
  int fontId = fontDatabase.addApplicationFont(QString::fromStdString(entry.path().string()));

  // 폰트 ID를 사용하여 QFont 객체를 만듭니다.
  QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

  // font family를 가져옵니다.
  defaultFont = fontFamilies.first();
  }

  return settings_->value("font", defaultFont).toString();
}

QString SettingManager::GetFontPath() {
  std::filesystem::path absolutePath = Utils::GetFontPath();

  QString defaultFontPath;
  for (const auto& entry : std::filesystem::directory_iterator(absolutePath)) {
    defaultFontPath = QString::fromStdString(entry.path().string());
    break;
  }
  return settings_->value("fontPath", defaultFontPath).toString();
}

QString SettingManager::GetFontColor() {
  return settings_->value("fontColor", "blue").toString();
}

QString SettingManager::GetColorCode() {
  return settings_->value("colorCode", "0000ff").toString();
}

bool SettingManager::GetFullScreenMode() {
  return settings_->value("isFullWindow", false).toBool();
}
