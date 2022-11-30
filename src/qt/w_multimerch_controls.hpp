#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class WMultiMerchControls final : public QWidget, virtual public FraudsAPI
{
  Q_OBJECT

 public:
  WMultiMerchControls(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    maxCheckbox = new QCheckBox(this);
    maxCheckbox->setCheckState(Qt::CheckState::Unchecked);
    maxCheckbox->setTristate(false);

    cumulative01 = new QPushButton("1", this);
    cumulative10 = new QPushButton("10", this);
    cumulative50 = new QPushButton("50", this);

    cumulativeSpinbox = new QSpinBox(this);
    cumulativeSpinbox->setRange(1, 999);
    cumulativeSpinbox->setValue(1);

    connect(
        maxCheckbox,
        &QCheckBox::stateChanged,
        this,
        &WMultiMerchControls::maxCheckboxToggled);

    connect(cumulative01, &QPushButton::pressed, this, [this] {
      cumulativeSpinbox->setValue(1);
    });
    connect(cumulative10, &QPushButton::pressed, this, [this] {
      cumulativeSpinbox->setValue(10);
    });
    connect(cumulative50, &QPushButton::pressed, this, [this] {
      cumulativeSpinbox->setValue(50);
    });
    connect(cumulativeSpinbox, &QSpinBox::valueChanged, this, [this] {
      AnyMultiMerch::setCumulative(cumulativeSpinbox->value());
    });

    layout->addWidget(maxCheckbox);
    layout->addStretch();
    layout->addWidget(cumulative01);
    layout->addWidget(cumulative10);
    layout->addWidget(cumulative50);
    layout->addWidget(cumulativeSpinbox);

    FRAUDS.connectAPI(*this);

    updateGratisPurchase();
  }

 private:
  void maxCheckboxToggled() {
    if (maxCheckbox->checkState() == Qt::CheckState::Checked) {
      AnyMultiMerch::enableMaxout();
      enableCumulative(false);
    } else {
      AnyMultiMerch::disableMaxout();
      enableCumulative(true);
    }
  }

  void enableCumulative(bool e) {
    cumulative01->setEnabled(e);
    cumulative10->setEnabled(e);
    cumulative50->setEnabled(e);
    cumulativeSpinbox->setEnabled(e);
  };

  void updateGratisPurchase() final {
    maxCheckbox->setDisabled(FRAUDS.isGratisPurchase());

    maxCheckbox->setText(
        FRAUDS.isGratisPurchase() ? Q_TR_GET(FraudsData, fraudsGratiasPurchase)
                                  : Q_TR_GET(AfkData, afkMaxName));

    enableCumulative(true);
  }

  QCheckBox* maxCheckbox;

  QPushButton* cumulative01;
  QPushButton* cumulative10;
  QPushButton* cumulative50;

  QSpinBox* cumulativeSpinbox;

  QHBoxLayout* layout;
};
