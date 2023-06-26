#ifndef CREDITFORM_H
#define CREDITFORM_H

#include <QWidget>

namespace Ui {
class CreditForm;
}

class CreditForm : public QWidget {
  Q_OBJECT

 public:
  explicit CreditForm(QWidget *parent = nullptr);
  ~CreditForm();
 private slots:
  void calculate();
  void closeEvent(QCloseEvent *event);

 signals:
  void close();

 private:
  Ui::CreditForm *ui;
};

#endif  // CREDITFORM_H
