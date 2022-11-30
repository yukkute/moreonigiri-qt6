#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"  // IWYU pragma: export
#include "w_decimal_input.hpp"
#include "yen_sign.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class WFraudsBank final : public QWidget, public virtual FraudsAPI
{
  Q_OBJECT

 public:
  WFraudsBank(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    FRAUDS.connectAPI(*this);

    initEarnedByFrauds();
    initAddToBank();

    updateEarnedByFrauds();
    updateFraudIncome();
  }

 private:
  QVBoxLayout* layout;

  QWidget*   earnedByFrauds;
  QLabel*    earnedByFraudsLabel;
  QLineEdit* earnedByFraudsNumber;

  QWidget*       addToBank;
  QHBoxLayout*   addToBankLayout;
  QPushButton*   addToBankButton;
  QPushButton*   flushBankButton;
  WDecimalInput* addToBankInput;

  void updateEarnedByFrauds() final {
    earnedByFraudsNumber->setText(Q_DEC(FRAUDS.getEarnedByFrauds()) + YEN);
  }

  void initEarnedByFrauds() {
    earnedByFrauds = new QWidget(this);
    earnedByFrauds->setLayout(new QHBoxLayout());

    earnedByFraudsLabel = new QLabel(earnedByFrauds);
    earnedByFraudsLabel->setText(Q_TR_GET(FraudsData, fraudsEarnedByFrauds));

    earnedByFraudsNumber = new QLineEdit(earnedByFrauds);
    earnedByFraudsNumber->setReadOnly(true);

    earnedByFrauds->layout()->addWidget(earnedByFraudsLabel);
    earnedByFrauds->layout()->addWidget(earnedByFraudsNumber);

    layout->addWidget(earnedByFrauds);
  }

  void initAddToBank() {
    addToBank       = new QWidget(this);
    addToBankLayout = new QHBoxLayout(addToBank);
    addToBankButton =
        new QPushButton(Q_TR_GET(FraudsData, fraudsAddToBank), addToBank);

    flushBankButton =
        new QPushButton(Q_TR_GET(FraudsData, fraudsFlushBank), addToBank);

    addToBankInput = new WDecimalInput(addToBank);

    addToBank->setLayout(addToBankLayout);

    addToBankLayout->addWidget(addToBankButton);
    addToBankLayout->addWidget(flushBankButton);
    addToBankLayout->addWidget(addToBankInput);

    connect(addToBankButton, &QPushButton::pressed, this, [this] {
      FRAUDS.earnCheated(addToBankInput->getValue());
    });
    connect(flushBankButton, &QPushButton::pressed, this, [this] {
      BANK.flush();
    });

    layout->addWidget(addToBank);
  }
};