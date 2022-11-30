#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"

#include <QComboBox>
#include <QHBoxLayout>
#include <QWidget>

class WUpgradeSort : public QWidget
{
  Q_OBJECT

 public:
  WUpgradeSort(QWidget* parent = nullptr) : QWidget(parent) {
    layout = new QHBoxLayout(this);
    this->setLayout(layout);

    sortCombobox = new QComboBox(this);

    sortCombobox->addItem(Q_TR_GET(UpgradeData, sortPricetagName));
    sortCombobox->addItem(Q_TR_GET(UpgradeData, sortMorphologicName));

    layout->addWidget(sortCombobox);

    connect(
        sortCombobox,
        &QComboBox::currentIndexChanged,
        this,
        &WUpgradeSort::sort);
  }

 private:
  QHBoxLayout* layout       = nullptr;
  QComboBox*   sortCombobox = nullptr;

  void sort() {
    switch (sortCombobox->currentIndex()) {
      case 0:  // By pricetag
        UPGRADELIST.setSortingType(UpgradeList::SortingType::by_pricetag);
        break;

      case 1:  // Morphologic
        UPGRADELIST.setSortingType(UpgradeList::SortingType::morphologic);
        break;
      default: break;
    }
    UPGRADELIST.sort();
  }
};
