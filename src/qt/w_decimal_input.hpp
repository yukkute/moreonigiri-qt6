#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"

#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

class WDecimalInput final : public QWidget
{
  Q_OBJECT

 public:
  WDecimalInput(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    characteristic = new QSpinBox(this);
    characteristic->setRange(1, 999);
    characteristic->setValue(1);

    mantissa = new QComboBox(this);

    for (auto m : Dec::prexl) { mantissa->addItem(Q_SVW(m)); }

    mantissa->setCurrentIndex(0);

    layout->addWidget(characteristic);
    layout->addWidget(mantissa);

    connect(characteristic, &QSpinBox::valueChanged, this, &WDecimalInput::set);
    connect(
        mantissa,
        &QComboBox::currentIndexChanged,
        this,
        &WDecimalInput::set);

    set();
  }
  money_t getValue() const { return value; }

 private:
  money_t value;

  QHBoxLayout* layout;

  QSpinBox*  characteristic;
  QComboBox* mantissa;
  void       set() {
          value =
              characteristic->value() * std::pow(10, (3 * mantissa->currentIndex()));
  }
};
