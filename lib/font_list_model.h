#ifndef FONT_LIST_MODEL_H
#define FONT_LIST_MODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QVariantMap>
#include <QFontDatabase>

#include <iostream>
#include <filesystem>
#include <Windows.h>

#include "util.h"

class FontListModel : public QObject {
  Q_OBJECT
  Q_PROPERTY(QVariantList font_list MEMBER font_list_ NOTIFY
                 listChanged)

 public:
    FontListModel(QObject* parent = nullptr);
    Q_INVOKABLE QVariantMap GetItem(int index) const;
    Q_INVOKABLE int GetIndexByText(const QString& text) const;

 signals:
    void listChanged();

 private:
   QVariantList font_list_;
};

#endif  // FONT_LIST_MODEL_H
