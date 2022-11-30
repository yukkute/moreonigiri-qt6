#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

class WAfkReport : public virtual AfkAPI, public QGroupBox
{
 public:
  WAfkReport() : QGroupBox() {
    setTitle(Q_TR_GET(AfkData, afkReport));
    layout = new QFormLayout(this);
    setLayout(layout);

    AFK.connectAPI(*this);

    initInvestedInAfk();
    initEarnedByAfk();

    updateInvestedInAfk();
    updateEarnedByAfk();
  }

 private:
  QFormLayout* layout;

  QLabel*    investedInAfkLabel;
  QLineEdit* investedInAfkWidget;

  QLabel*    earnedByAfkLabel;
  QLineEdit* earnedByAfkWidget;

  void updateInvestedInAfk() final {
    investedInAfkWidget->setText(Q_DEC(AFK.getInvestedInAfk()) + YEN);
  }

  void updateEarnedByAfk() final {
    earnedByAfkWidget->setText(Q_DEC(AFK.getEarnedByAfk()) + YEN);
  }

  void initInvestedInAfk() {
    investedInAfkLabel = new QLabel(this);
    investedInAfkLabel->setText(Q_TR_GET(AfkData, afkInvestedInAfk));

    investedInAfkWidget = new QLineEdit(this);
    investedInAfkWidget->setReadOnly(true);

    layout->addRow(investedInAfkLabel, investedInAfkWidget);
  }

  void initEarnedByAfk() {
    earnedByAfkLabel = new QLabel(this);
    earnedByAfkLabel->setText(Q_TR_GET(AfkData, afkEarnedByAfk));

    earnedByAfkWidget = new QLineEdit(this);
    earnedByAfkWidget->setReadOnly(true);

    layout->addRow(earnedByAfkLabel, earnedByAfkWidget);
  }
};