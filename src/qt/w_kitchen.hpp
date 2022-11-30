#pragma once

#include "w_bank.hpp"
#include "w_clicker.hpp"
#include "w_income.hpp"

#include <QVBoxLayout>
#include <QWidget>

class WKitchen final : public QWidget
{
  Q_OBJECT

 public:
  WKitchen(QWidget* parent = nullptr) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout();
    this->setLayout(layout);

    wClicker = new WClicker(this);
    wBank    = new WBank(this);
    wIncome  = new WIncome(this);

    layout->addWidget(wClicker, 1);
    layout->addWidget(wBank, 0);
    layout->addWidget(wIncome, 0);
  };

 private:
  WClicker* wClicker = nullptr;
  WBank*    wBank    = nullptr;
  WIncome*  wIncome  = nullptr;
};