#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  //    setlocale(LC_NUMERIC,"C");
  setenv("LC_NUMERIC", "C", 1);
  //    QLocale::setDefault(QLocale::C);
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
