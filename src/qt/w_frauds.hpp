#pragma once

#include "w_frauds_bank.hpp"
#include "w_frauds_gratias.hpp"
#include "w_frauds_income.hpp"

#include <QVBoxLayout>
#include <QWidget>

class WFrauds final : public QWidget
{
  Q_OBJECT

 public:
  WFrauds(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    fraudsBank    = new WFraudsBank(this);
    fraudsIncome  = new WFraudsIncome(this);
    fraudsGratias = new WFraudsGratias(this);

    layout->addWidget(fraudsBank);
    layout->addWidget(fraudsIncome);
    layout->addWidget(fraudsGratias);
    layout->addStretch();
  }

 private:
  QVBoxLayout* layout;

  WFraudsBank*    fraudsBank;
  WFraudsIncome*  fraudsIncome;
  WFraudsGratias* fraudsGratias;
};
