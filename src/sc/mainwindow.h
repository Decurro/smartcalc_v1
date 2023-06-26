#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <creditform.h>
#include <depositform.h>
#include <graphform.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void digits_numbers();
  void all_clean();
  void clean();
  void result();
  void push_graph();
  void push_credit();
  void push_deposit();

  //    void on_graphic_clicked();

 private:
  Ui::MainWindow *ui;
  int check_res;
  bool GraphOpened;
  bool CreditOpened;
  bool DepositOpened;
  GraphForm *grapik;
  CreditForm *credidi;
  DepositForm *depopi;
};
#endif  // MAINWINDOW_H
