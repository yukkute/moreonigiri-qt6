#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <sstream>

class WEnterpriseReport final : public QWidget, public EnterpriseAPI
{
  Q_OBJECT

 public:
  WEnterpriseReport(index_t index, QWidget* parent = nullptr) :
      QWidget(parent) {
    layout = new QFormLayout(this);
    this->setLayout(layout);

    e = ENTERPRISES.at(index);
    e->connectAPI(*this);

    initIncomePerUnit();
    initIncomeEnterprise();
    initSpentOnEnterprise();
    initEarnedByEnterprise();
  }

  void initIncomePerUnit() {
    incomePerUnitLabel =
        new label(Q_TR_GET(EnterpriseData, enterpriseIncomePerUnit));

    incomePerUnitWidget = new value();
    incomePerUnitWidget->setReadOnly(true);

    layout->addRow(incomePerUnitLabel, incomePerUnitWidget);

    updateIncomePerUnit();
  }

  void initIncomeEnterprise() {
    incomeEnterpriseLabel =
        new label(Q_TR_GET(EnterpriseData, enterpriseIncomeEnterprise));

    incomeEnterpriseWidget = new value();
    incomeEnterpriseWidget->setReadOnly(true);

    layout->addRow(incomeEnterpriseLabel, incomeEnterpriseWidget);

    updatePercentOfAfk();
  }

  void initEarnedByEnterprise() {
    earnedByLabel =
        new label(Q_TR_GET(EnterpriseData, enterpriseEarnedByEnterprise));

    earnedByWidget = new value();
    earnedByWidget->setReadOnly(true);

    layout->addRow(earnedByLabel, earnedByWidget);

    updateEarnedByEnterprise();
  }

  void initSpentOnEnterprise() {
    spentOnLabel =
        new label(Q_TR_GET(EnterpriseData, enterpriseSpentOnEnterprise));

    spentOnWidget = new value();
    spentOnWidget->setReadOnly(true);

    layout->addRow(spentOnLabel, spentOnWidget);

    updateSpentOnEnterprise();
  }

 private:
  using label = QLabel;
  using value = QLineEdit;

  std::shared_ptr<Enterprise> e;

  QFormLayout* layout;

  label* incomePerUnitLabel;
  value* incomePerUnitWidget;

  label* incomeEnterpriseLabel;
  value* incomeEnterpriseWidget;

  label* earnedByLabel;
  value* earnedByWidget;

  label* spentOnLabel;
  value* spentOnWidget;

  void updateIncomePerUnit() final {
    incomePerUnitWidget->setText(Q_DEC(e->getIncomePerUnit()) + YEN);
  }
  void updatePercentOfAfk() final {
    QString text;

    text.append(Q_DEC(e->getIncomeEnterprise()));
    text.append(YEN);
    text.append(" (");

    if (e->getPercentOfAfk() < 0.01)
      text.append("<1 %");
    else
      text.append(Q_DEC(e->getPercentOfAfk(), Dec::percentF, 1));

    text.append(" ");

    text.append(Q_TR_GET(EnterpriseData, enterprisePercentOfAfk));
    text.append(")");

    incomeEnterpriseWidget->setText(text);
  }
  void updateSpentOnEnterprise() final {
    spentOnWidget->setText(Q_DEC(e->getSpentOnEnterprise()) + YEN);
  }
  void updateEarnedByEnterprise() final {
    earnedByWidget->setText(Q_DEC(e->getEarnedByEnterprise()) + YEN);
  }
};