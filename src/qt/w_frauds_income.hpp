#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "w_decimal_input.hpp"
#include "yen_sign.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class WFraudsIncome final : public QWidget, public virtual FraudsAPI
{
  Q_OBJECT

 public:
  WFraudsIncome(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    FRAUDS.connectAPI(*this);

    initFraudIncome();
    initSetIncome();

    updateFraudIncome();
  }

 private:
  QVBoxLayout* layout;

  QWidget*   fraudIncome;
  QLabel*    fraudIncomeLabel;
  QLineEdit* fraudIncomeNumber;

  QWidget*       setIncome;
  QHBoxLayout*   setIncomeLayout;
  QPushButton*   setIncomeButton;
  QPushButton*   resetIncomeButton;
  WDecimalInput* incomeInput;

  void updateFraudIncome() final {
    fraudIncomeNumber->setText(Q_DEC(FRAUDS.getFraudIncome()) + YEN_PER_SEC);
  }

  void initFraudIncome() {
    fraudIncome = new QWidget(this);
    fraudIncome->setLayout(new QHBoxLayout());

    fraudIncomeLabel = new QLabel(fraudIncome);
    fraudIncomeLabel->setText(Q_TR_GET(FraudsData, fraudsIncome));

    fraudIncomeNumber = new QLineEdit(fraudIncome);
    fraudIncomeNumber->setReadOnly(true);

    fraudIncome->layout()->addWidget(fraudIncomeLabel);
    fraudIncome->layout()->addWidget(fraudIncomeNumber);

    layout->addWidget(fraudIncome);
  }

  void initSetIncome() {
    setIncome       = new QWidget(this);
    setIncomeLayout = new QHBoxLayout(setIncome);

    setIncomeButton =
        new QPushButton(Q_TR_GET(FraudsData, fraudsSetIncome), setIncome);
    resetIncomeButton =
        new QPushButton(Q_TR_GET(FraudsData, fraudsResetIncome), setIncome);

    incomeInput = new WDecimalInput(setIncome);

    setIncomeLayout->addWidget(setIncomeButton);
    setIncomeLayout->addWidget(resetIncomeButton);
    setIncomeLayout->addWidget(incomeInput);

    connect(setIncomeButton, &QPushButton::pressed, this, [this] {
      FRAUDS.setFraudIncome(incomeInput->getValue());
    });
    connect(resetIncomeButton, &QPushButton::pressed, this, [] {
      FRAUDS.resetFraudIncome();
    });

    layout->addWidget(setIncome);
  }
};