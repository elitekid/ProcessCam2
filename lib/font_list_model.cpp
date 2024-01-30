#include "font_list_model.h"

FontListModel::FontListModel(QObject* parent) : QObject(parent) {
  std::filesystem::path absolutePath = Utils::GetFontPath();

  for (const auto& entry : std::filesystem::directory_iterator(absolutePath)) {
    QVariantMap fontMap;
    qDebug() << "File Path: " << entry.path().native();

    // 폰트 데이터베이스를 가져옵니다.
    QFontDatabase fontDatabase;

    // 폰트 경로를 사용하여 폰트 ID를 가져옵니다.
    int fontId = fontDatabase.addApplicationFont(QString::fromStdString(entry.path().string()));

    // 폰트 ID를 사용하여 QFont 객체를 만듭니다.
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    // font family를 가져옵니다.
    QString family = fontFamilies.first();

    fontMap.insert("value", QString::fromStdWString(entry.path().native()));
    fontMap.insert("text", family);
    font_list_.append(fontMap);
    emit listChanged();
  }
}

QVariantMap FontListModel::GetItem(int index) const {
  if (index >= 0 && index < font_list_.size()) {
    return font_list_.at(index).toMap();
  } else {
    return QVariantMap();  // 유효하지 않은 인덱스에 대한 처리
  }
}

int FontListModel::GetIndexByText(const QString& text) const {
  for (int i = 0; i < font_list_.size(); ++i) {
    QVariantMap map = font_list_.at(i).toMap();
    if (map["text"].toString() == text) {
      return i;  // 해당 텍스트를 가진 아이템의 인덱스 반환
    }
  }
  return -1;  // 해당 텍스트를 가진 아이템이 없을 경우 -1 반환
}