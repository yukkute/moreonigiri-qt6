#pragma once

#include "w_kitchen.hpp"
#include "w_tabs.hpp"

#include <QHBoxLayout>
#include <QWidget>

class MainWidget final : public QWidget
{
  Q_OBJECT
 public:
  explicit MainWidget(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    auto kitchen = new WKitchen(this);
    auto tabs    = new WTabs(this);

    layout->addWidget(kitchen, 2);
    layout->addWidget(tabs, 5);
  }

 private:
  QHBoxLayout* layout = nullptr;
};
