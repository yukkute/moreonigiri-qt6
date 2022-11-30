#pragma once

#include "game.hpp"
#include "w_upgrade.hpp"
#include "w_upgrade_sort.hpp"

#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class WUpgradeList final : public QWidget, public UpgradeListAPI
{
 public:
  WUpgradeList(QWidget* parent = nullptr) : QWidget(parent) {
    for (auto u : UPGRADELIST.getUpgrades()) {
      widgetsUpgrades.push_back(new WUpgrade(*u, this));
    }

    layout = new QVBoxLayout(this);
    this->setLayout(layout);

    sortUpgrades = new WUpgradeSort(this);
    layout->addWidget(sortUpgrades);

    scrollarea = new QScrollArea(this);
    scrollarea->setWidgetResizable(true);

    layout->addWidget(scrollarea);

    scroll       = new QWidget(scrollarea);
    scrollLayout = new QVBoxLayout(scroll);
    scroll->setLayout(scrollLayout);

    scrollLayout->addStretch();

    scrollarea->setWidget(scroll);

    UPGRADELIST.connectAPI(*this);

    onSorted();
  };
  void onSorted() final {
    qDeleteAll(scrollLayout->children());

    for (int i = 0; auto upgrade : UPGRADELIST.getUpgrades()) {
      auto showUpgradeFound = std::find_if(
          widgetsUpgrades.begin(),
          widgetsUpgrades.end(),
          [upgrade](WUpgrade* widgetUpgrade) {
            return widgetUpgrade->upgrade == upgrade;
          });

      auto wUpgrade = *showUpgradeFound;

      if (showUpgradeFound == widgetsUpgrades.end()) {
        throw std::out_of_range("Not found upgrade " + std::to_string(i));
      }

      wUpgrade->indexInScroll = i;
      i++;

      std::sort(
          widgetsUpgrades.begin(),
          widgetsUpgrades.end(),
          [](WUpgrade* lhs, WUpgrade* rhs) {
            return lhs->indexInScroll < rhs->indexInScroll;
          });

      for (auto* u : widgetsUpgrades) {
        scrollLayout->insertWidget(scrollLayout->count() - 1, u);
      }
    }
  };

 private:
  std::vector<WUpgrade*> widgetsUpgrades;

  QVBoxLayout* layout = nullptr;

  QScrollArea* scrollarea = nullptr;

  QWidget*     scroll       = nullptr;
  QVBoxLayout* scrollLayout = nullptr;

  WUpgradeSort* sortUpgrades = nullptr;
};