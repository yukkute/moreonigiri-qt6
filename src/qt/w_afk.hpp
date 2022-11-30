#pragma once

#include "w_enterprise.hpp"
#include "w_multimerch_controls.hpp"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class WAfk final : public QWidget
{
  Q_OBJECT

 public:
  WAfk(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    scrollarea = new QScrollArea(this);
    scrollarea->setSizePolicy(
        QSizePolicy::MinimumExpanding,
        QSizePolicy::Expanding);
    scrollarea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollarea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollarea->setWidgetResizable(true);

    layout->addWidget(scrollarea);

    scroll       = new QWidget(scrollarea);
    scrollLayout = new QVBoxLayout(scroll);
    scroll->setLayout(scrollLayout);
    scrollarea->setWidget(scroll);

    for (size_t i = 0; i < wenterprises.size(); i++) {
      wenterprises.at(i) = new WEnterprise(i, scroll);
      scrollLayout->addWidget(wenterprises.at(i), 0);
    }
    scrollLayout->addStretch();

    afkControls = new WMultiMerchControls(this);
    layout->addWidget(afkControls);
  }

 private:
  std::array<WEnterprise*, EnterpriseData::implemented> wenterprises;

  QVBoxLayout* layout;

  QScrollArea* scrollarea;

  QWidget*     scroll;
  QVBoxLayout* scrollLayout;

  WMultiMerchControls* afkControls;
};