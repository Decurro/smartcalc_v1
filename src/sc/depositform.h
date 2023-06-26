#ifndef DEPOSITFORM_H
#define DEPOSITFORM_H

#include <QDate>
#include <QWidget>

namespace Ui {
class DepositForm;
}

class DepositForm : public QWidget {
  Q_OBJECT

 public:
  explicit DepositForm(QWidget *parent = nullptr);
  ~DepositForm();
 private slots:
  void add_action();
  void add_list();
  void calculate();
  void distance_convert(int *distance, int type_distance);
  void deposit_add(QDate date, double *total_deposit);
  void closeEvent(QCloseEvent *event);

 signals:
  void close();

 private:
  Ui::DepositForm *ui;
  QList<QList<QVariant>> list_lists;
  int distance;
  int type_distance;
  QDate date;
};

#endif  // DEPOSITFORM_H
