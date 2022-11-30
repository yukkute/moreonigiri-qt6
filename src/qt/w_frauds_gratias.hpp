#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"

#include <QCheckBox>
#include <QVBoxLayout>
#include <QWidget>

class WFraudsGratias : public QWidget
{
  Q_OBJECT

 public:
  WFraudsGratias(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    gratisPurchase = new QCheckBox(this);
    gratisPurchase->setText(Q_TR_GET(FraudsData, fraudsGratiasPurchase));
    gratisPurchase->setChecked(false);

    layout->addWidget(gratisPurchase);

    connect(
        gratisPurchase,
        &QCheckBox::stateChanged,
        this,
        &WFraudsGratias::onCheckboxChanged);
  }

 private:
  void onCheckboxChanged() {
    if (gratisPurchase->isChecked())
      FRAUDS.enableGratisPurchase();
    else
      FRAUDS.disableGratisPurchase();
  }

  QVBoxLayout* layout;

  QCheckBox* gratisPurchase;
};