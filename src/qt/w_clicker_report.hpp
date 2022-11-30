#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

class WClickerReport : public virtual ClickerAPI, public QGroupBox
{
 public:
  WClickerReport() : QGroupBox() {
    setTitle(Q_TR_GET(ClickerData, clickerReport));
    layout = new QFormLayout(this);
    setLayout(layout);

    CLICKER->connectAPI(*this);

    initClickingPower();
    initClicksMade();
    initEarnedByClick();

    updateClickingPower();
    updateClicksMade();
    updateEarnedByClick();
  }

 private:
  QFormLayout* layout;

  QLabel*    clickingPowerLabel;
  QLineEdit* clickingPowerWidget;

  QLabel*    clicksMadeLabel;
  QLineEdit* clicksMadeWidget;

  QLabel*    earnedByClickLabel;
  QLineEdit* earnedByClickWidget;

  void updateClickingPower() final {
    clickingPowerWidget->setText(Q_DEC(CLICKER->getClickingPower()) + YEN);
  }

  void updateClicksMade() final {
    clicksMadeWidget->setText(Q_DEC(CLICKER->getClicksMade(), Dec::integerF));
  }

  void updateEarnedByClick() final {
    earnedByClickWidget->setText(Q_DEC(CLICKER->getEarnedByClick()) + YEN);
  }

  void initClickingPower() {
    clickingPowerLabel = new QLabel(this);
    clickingPowerLabel->setText(Q_TR_GET(ClickerData, clickingPower));

    clickingPowerWidget = new QLineEdit(this);
    clickingPowerWidget->setReadOnly(true);

    layout->addRow(clickingPowerLabel, clickingPowerWidget);
  }

  void initClicksMade() {
    clicksMadeLabel = new QLabel(this);
    clicksMadeLabel->setText(Q_TR_GET(ClickerData, clicksMade));

    clicksMadeWidget = new QLineEdit(this);
    clicksMadeWidget->setReadOnly(true);

    layout->addRow(clicksMadeLabel, clicksMadeWidget);
  }

  void initEarnedByClick() {
    earnedByClickLabel = new QLabel(this);
    earnedByClickLabel->setText(Q_TR_GET(ClickerData, earnedByClick));

    earnedByClickWidget = new QLineEdit(this);
    earnedByClickWidget->setReadOnly(true);

    layout->addRow(earnedByClickLabel, earnedByClickWidget);
  }
};