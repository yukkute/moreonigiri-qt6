#include "game.hpp"
#include "w_mainwindow.hpp"

#include <QApplication>
#include <QTimer>

int main(int argc, char* argv[]) {
  Game::createNewInstance();

  QApplication a(argc, argv);

  MainWindow w = MainWindow(Game::getGame());
  w.show();
  return a.exec();
}
