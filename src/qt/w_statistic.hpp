#pragma once

#include "w_afk_report.hpp"
#include "w_clicker_report.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QWidget>

class WStatistics : public QWidget
{
 public:
  WStatistics(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    setLayout(layout);

    clickerReport = new WClickerReport();
    layout->addWidget(clickerReport);

    afkReport = new WAfkReport();
    layout->addWidget(afkReport);
  }

 private:
  QVBoxLayout* layout;

  WClickerReport* clickerReport;
  WAfkReport*     afkReport;
};