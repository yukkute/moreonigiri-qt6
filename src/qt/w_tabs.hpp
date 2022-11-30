#pragma once

#include "qstring_from_std.hpp"
#include "w_afk.hpp"
#include "w_frauds.hpp"
#include "w_statistic.hpp"
#include "w_upgrade_list.hpp"

#include <QLabel>
#include <QTabWidget>
#include <QWidget>

class WTabs final : public QTabWidget
{
 public:
  WTabs(QWidget* parent = nullptr) : QTabWidget(parent) {
    tabAfk        = new WAfk(this);
    tabUpgrades   = new WUpgradeList(this);
    tabStatistics = new WStatistics(this);
    tabFrauds     = new WFrauds(this);

    addTab(tabAfk, Q_TR_GET(AfkData, tabAfkName));
    addTab(tabUpgrades, Q_TR_GET(UpgradeData, tabUpgradesName));
    addTab(tabStatistics, Q_TR_GET(GameData, tabStatisticsName));
    addTab(tabFrauds, Q_TR_GET(FraudsData, tabFraudsName));
  }

 private:
  WAfk*         tabAfk        = nullptr;
  WUpgradeList* tabUpgrades   = nullptr;
  WStatistics*  tabStatistics = nullptr;
  WFrauds*      tabFrauds     = nullptr;
};
