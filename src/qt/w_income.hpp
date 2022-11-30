#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

class WIncome final : public QWidget, public AfkAPI
{
  Q_OBJECT

 public:
  WIncome(QWidget* parent = nullptr) : QWidget(parent) {
    this->setLayout(new QVBoxLayout());

    this->layout()->addWidget(
        new QLabel(Q_TR_GET(AfkData, kitchenIncomeName), this));

    lineedit = new QLineEdit(this);

    this->layout()->addWidget(lineedit);
    lineedit->setReadOnly(true);

    AFK.connectAPI(*this);

    updateIncomeAfk();
  }

 private:
  QLineEdit* lineedit;
  void       updateIncomeAfk() final {
    QString text = Q_DEC(AFK.getIncomeAfk()) + YEN_PER_SEC;

    lineedit->setText(text);
  }
};
