#pragma once

#include "game.hpp"
#include "qstring_from_std.hpp"
#include "w_enterprise_report.hpp"
#include "yen_sign.hpp"

#include <QHBoxLayout>
#include <QIcon>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class WEnterprise final : public QWidget, public EnterpriseAPI
{
  Q_OBJECT

 public:
  WEnterprise(index_t index, QWidget* parent = nullptr) :
      QWidget(parent), e(ENTERPRISES.at(index)) {
    this->setLayout(new QVBoxLayout());
    this->layout()->setContentsMargins({});
    this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);

    widgetSpoilerHead = new QWidget(this);
    layoutSpoilerHead = new QHBoxLayout(widgetSpoilerHead);
    layoutSpoilerHead->setContentsMargins({});
    this->layout()->addWidget(widgetSpoilerHead);

    widgetReport = new WEnterpriseReport(index, this);
    this->layout()->addWidget(widgetReport);
    widgetReport->setHidden(hideReport);

    ENTERPRISES.at(index)->connectAPI(*this);

    initImageWidget();
    initNameWidget();
    initPurchaseButton();

    updateQuantity();
    updatePricetag();
    updateAffordable();

    purchaseButtonLayout->update();
  }

 private:
  void initImageWidget() {
    imageWidget = new QPushButton(widgetSpoilerHead);
    layoutSpoilerHead->addWidget(imageWidget);
    imageWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    std::string path;
    path.append(":/images/");
    path.append(e->getFormalId());
    path.append(".svg");

    image = new QIcon(Q_STR(path));

    if (FALLBACK_IMG or image->isNull()) {
      imageWidget->setText(Q_SVW(enterpriseEmoji.at(e->getIndex())));
      imageWidget->setStyleSheet("font-size: 50px");
    }

    else {
      imageWidget->setIcon(*image);
      imageWidget->setIconSize({84, 84});
    }
  }

  void initNameWidget() {
    nameWidget            = new QPushButton(widgetSpoilerHead);
    auto nameWidgetLayout = new QVBoxLayout(nameWidget);
    nameWidget->setLayout(nameWidgetLayout);
    nameWidget->setSizePolicy(
        QSizePolicy::MinimumExpanding,
        QSizePolicy::Expanding);

    nameWidgetName = new QLabel(
        Q_TR_GET(EnterpriseData, enterpriseNames.at(e->getIndex())),
        nameWidget);
    nameWidgetName->setAlignment(Qt::AlignLeft);
    nameWidgetName->setStyleSheet("font-size: 20px");

    nameWidgetDesc = new QLabel(
        "…" + Q_TR_GET(EnterpriseData, enterpriseDescs.at(e->getIndex())),
        nameWidget);
    nameWidgetDesc->setAlignment(Qt::AlignRight);
    nameWidgetDesc->setDisabled(true);

    nameWidgetLayout->addWidget(nameWidgetName, 3);
    nameWidgetLayout->addWidget(nameWidgetDesc, 2);

    connect(nameWidget, &QPushButton::pressed, this, [this] {
      hideReport = not hideReport;
      widgetReport->setHidden(hideReport);
    });

    layoutSpoilerHead->addWidget(nameWidget, 7);
  }

  void initPurchaseButton() {
    purchaseButton       = new QPushButton(widgetSpoilerHead);
    purchaseButtonLayout = new QVBoxLayout(purchaseButton);
    purchaseButton->setLayout(purchaseButtonLayout);
    purchaseButton->setSizePolicy(
        QSizePolicy::MinimumExpanding,
        QSizePolicy::Expanding);

    quantityLabel = new QLabel(purchaseButton);
    quantityLabel->setAlignment(Qt::AlignCenter);
    quantityLabel->setStyleSheet("font-size: 18px");

    pricetagLabel = new QLabel(purchaseButton);
    pricetagLabel->setAlignment(Qt::AlignCenter);

    purchaseButtonLayout->addWidget(quantityLabel);
    purchaseButtonLayout->addWidget(pricetagLabel);

    layoutSpoilerHead->addWidget(purchaseButton, 3);

    connect(purchaseButton, &QPushButton::pressed, this, [this] { e->buy(); });
  }

  bool hideReport = true;

  std::shared_ptr<Enterprise> e;

  QWidget*     widgetSpoilerHead;
  QHBoxLayout* layoutSpoilerHead;

  WEnterpriseReport* widgetReport;

  QPushButton* imageWidget;
  QIcon*       image;

  QPushButton* nameWidget;
  QLabel*      nameWidgetName;
  QLabel*      nameWidgetDesc;

  QPushButton* purchaseButton;
  QVBoxLayout* purchaseButtonLayout;
  QLabel*      quantityLabel;
  quantity_t   maxQuantity = 0;
  QLabel*      pricetagLabel;

  void updateQuantity() final {
    quantityLabel->setText("" + Q_DEC(e->getQuantity()));
    quantityLabel->setHidden(e->getQuantity() == 0);
  }
  void updateMaxoutQuantity() final { maxQuantity = e->getMaxQuantity(); }

  void updatePricetag() final {
    QString text;

    text.append(Q_DEC(e->getPricetag()) + YEN);

    if (AnyMultiMerch::isMaxout() and maxQuantity != 0)
      text.append(" (+" + Q_DEC(maxQuantity, Dec::integerF) + ")");

    pricetagLabel->setText(text);
  }

  void updateAffordable() final {
    purchaseButton->setEnabled(e->isAffordable());
  }
};
