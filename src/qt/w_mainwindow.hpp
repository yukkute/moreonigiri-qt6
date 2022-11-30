#pragma once

#include "game.hpp"
#include "w_mainwidget.hpp"

#include <QHBoxLayout>
#include <QMainWindow>
#include <QTimer>

class MainWindow final : public QMainWindow
{
 public:
  explicit MainWindow(Game& game) {
    Q_INIT_RESOURCE(resources);

    setWindowIcon(QIcon(":/images/e00.svg"));
    setWindowTitle("More Onigiri!");

    setMinimumSize({800, 480});
    setCentralWidget(new MainWidget(this));

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, [this, &game]() { game.tick(); });
    timer->start(1000 / AnyTicker::tickPerSec);
  }

  ~MainWindow() final {
    Q_CLEANUP_RESOURCE(resources);
    timer->stop();
  };

 private:
  QTimer* timer = nullptr;
};
