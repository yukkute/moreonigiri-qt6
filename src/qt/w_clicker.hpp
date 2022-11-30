#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class WClicker final : public QWidget, public ClickerAPI
{
  Q_OBJECT

 public:
  WClicker(QWidget* parent) : QWidget(parent) {
    button = new QPushButton(this);

    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(button);

    connect(button, &QPushButton::pressed, this, &WClicker::click);

    CLICKER->connectAPI(*this);

    updateClickingPower();
  }

 private:
  QPushButton* button       = nullptr;
  QString      clickLiteral = Q_TR_GET(ClickerData, kitchenClickName);

  void updateClickingPower() final {
    QString text;

    text.append(clickLiteral);
    text.append("\n( +");
    text.append(Q_DEC(CLICKER->getClickingPower()));
    text.append(YEN);
    text.append(" )");

    button->setText(text);
  }
  static void click() { CLICKER->click(); }
};