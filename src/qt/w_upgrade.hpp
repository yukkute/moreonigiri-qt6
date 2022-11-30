#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "yen_sign.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class WUpgrade final : public QWidget, public AnyUpgradeAPI
{
  Q_OBJECT

 public:
  WUpgrade(AnyUpgrade& upgrade, QWidget* parent = nullptr) :
      QWidget(parent), upgrade(&upgrade) {
    this->setMaximumHeight(150);

    layout = new QHBoxLayout(this);
    this->setLayout(layout);
    layout->setContentsMargins({});

    this->upgrade->connectAPI(*this);

    initImage();
    initLabel();
    initPurchase();

    updateAffordable();
    updatePurchased();
  }
  AnyUpgrade* upgrade = nullptr;

  index_t indexInScroll;

 private:
  void updateAffordable() final {
    if (upgrade->isPurchased()) return;
    upgradePurchaseButton->setEnabled(upgrade->isAvailableForPurchase());
  };

  void updatePurchased() final {
    if (upgrade->isPurchased()) {
      upgradePurchaseButton->setText("✓");

      upgradePurchaseButton->setDisabled(true);
      upgradePurchaseButton->setFlat(true);
    }
  }

  void initLabel() {
    upgradeButton = new QPushButton(this);
    upgradeButton->setLayout(new QVBoxLayout());
    upgradeButton->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding);

    upgradeName = new QLabel(upgradeButton);
    upgradeName->setText(Q_SVW(upgrade->getName()));
    upgradeName->setStyleSheet("font-size: 20px; text-align: left");

    upgradeHint = new QLabel(upgradeButton);
    upgradeHint->setText(Q_SVW(upgrade->getHint()));
    upgradeHint->setStyleSheet("text-align: left");
    upgradeHint->setDisabled(true);

    upgradeButton->layout()->addWidget(upgradeName);
    upgradeButton->layout()->addWidget(upgradeHint);

    layout->addWidget(upgradeButton, 7);
  }

  void initImage() {
    imageWidget = new QPushButton(this);
    imageWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    layout->addWidget(imageWidget, 1);

    std::string path;

    path.append(":/images/");
    path.append(upgrade->getFormalId());
    path.append(".svg");

    image = new QPixmap(Q_STR(path));

    if (FALLBACK_IMG or image->isNull()) {
      initImageWithEmoji();
    }

    else {
      imageWidget->setMinimumSize({72, 72});
      imageWidget->setIconSize({60, 60});

      *image = image->scaled(512, 512);

      imageWidget->setIcon(*image);
    }
  }

  void initImageWithEmoji() {
    imageWidget->setLayout(new QHBoxLayout());
    imageWidget->setMinimumSize({100, 72});

    QString icon;

    switch (upgrade->getType()) {
      case AnyUpgrade::Type::enterpriseTier: {
        icon = Q_SVW(enterpriseEmoji.at(upgrade->getParentNumber()));
        break;
      }
      case AnyUpgrade::Type::clicker: {
        icon = Q_SVW(clickerEmoji);
        break;
      }
      default: break;
    }

    QLabel* imageWidgetIcon = new QLabel(icon, imageWidget);
    imageWidgetIcon->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    imageWidgetIcon->setStyleSheet("font-size: 50px; text-align: center");

    imageWidget->layout()->addWidget(imageWidgetIcon);
  }

  void initPurchase() {
    upgradePurchaseButton = new QPushButton(this);
    upgradePurchaseButton->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding);

    layout->addWidget(upgradePurchaseButton, 2);

    connect(upgradePurchaseButton, &QPushButton::pressed, this, [this] {
      upgrade->buy();
    });

    upgradePurchaseButton->setText(Q_DEC(this->upgrade->getPricetag()) + YEN);
  }

  QHBoxLayout* layout;

  QPushButton* imageWidget;
  QPixmap*     image;

  QPushButton* upgradeButton;
  QLabel*      upgradeName;
  QLabel*      upgradeHint;

  QPushButton* upgradePurchaseButton;
};