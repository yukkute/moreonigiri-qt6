#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

class WBank final : public QWidget, public BankAPI, public FraudsAPI

{
  Q_OBJECT

 public:
  WBank(QWidget* parent = nullptr) : QWidget(parent) {
    this->setLayout(new QVBoxLayout());

    auto bankLiteral = Q_TR_GET(BankData, kitchenBankName);
    this->layout()->addWidget(new QLabel(bankLiteral, this));

    lineedit = new QLineEdit(this);

    this->layout()->addWidget(lineedit);
    lineedit->setReadOnly(true);

    BANK.connectAPI(*this);
    FRAUDS.connectAPI(*this);

    updateFunds();
    updateGratisPurchase();
  }

 private:
  QLineEdit* lineedit = nullptr;

  void updateFunds() final {
    this->lineedit->setText(Q_DEC(BANK.getFunds()) + YEN);
  };

  void updateGratisPurchase() final {
    lineedit->setDisabled(FRAUDS.isGratisPurchase());
  }
};