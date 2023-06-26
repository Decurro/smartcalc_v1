#include "graphform.h"

#include "ui_graphform.h"

extern "C" {
#include "smartcalc.h"
}

GraphForm::GraphForm(QWidget *parent, QString input1)
    : QWidget(parent), ui(new Ui::GraphForm) {
  ui->setupUi(this);
  input = input1;
  connect(ui->pushButton_create_g, SIGNAL(clicked()), this,
          SLOT(create_graph()));
}

GraphForm::~GraphForm() { delete ui; }

void GraphForm::create_graph() {
  double result = 0.0;
  int error = 0;
  double stepik = 0.0;
  double x_start = ui->double_x_min->value();
  double x_stop = ui->double_x_max->value();
  double y_start = ui->doubleSpinBox_y_min->value();
  double y_stop = ui->doubleSpinBox_y_max->value();
  if (x_start < -1000000.0) x_start = -1000000.0;
  if (x_stop > 1000000.0) x_stop = 1000000.0;
  if (y_start < -1000000.0) y_start = -1000000.0;
  if (y_stop > 1000000.0) y_stop = 1000000.0;
  ui->widget->xAxis->setRange(x_start, x_stop);
  ui->widget->yAxis->setRange(y_start, y_stop);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
  step(x_start, x_stop, &stepik);

  for (double X = x_start; X <= x_stop; X += stepik) {
    x.push_back(X);
    QString x_value;
    if (X < 0) {
      x_value = QString("(%1)").arg(QString::number(X));
    } else {
      x_value = QString::number(X);
    }
    QString expression = input;
    expression.replace("x", x_value);
    QByteArray arr_chars = expression.toLocal8Bit();
    char *ptr_arr_chars = arr_chars.data();
    error = baza(ptr_arr_chars, &result);
    if (error == 0 && razriv(X, X + stepik) != 1) {
      y.push_back(result);

    } else {
      y.push_back(NAN);
    }
  }
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  x.clear();
  y.clear();
}

void GraphForm::step(double x_start, double x_stop, double *stepik) {
  if (x_stop - x_start <= 10) *stepik = 0.00001;
  if (x_stop - x_start <= 100) *stepik = 0.0001;
  if (x_stop - x_start <= 1000) *stepik = 0.001;
  if (x_stop - x_start <= 10000) *stepik = 0.01;
  if (x_stop - x_start > 10000) *stepik = 0.1;
}

int GraphForm::razriv(double x_1, double x_2) {
  double result_1 = 0.0;
  double result_2 = 0.0;
  int check = 0;
  QString x_value_1;
  QString x_value_2;
  if (x_1 < 0) {
    x_value_1 = QString("(%1)").arg(QString::number(x_1));
  } else {
    x_value_1 = QString::number(x_1);
  }
  if (x_2 < 0) {
    x_value_2 = QString("(%1)").arg(QString::number(x_2));
  } else {
    x_value_2 = QString::number(x_2);
  }

  QString y_1 = input;
  QString y_2 = input;
  y_1.replace("x", x_value_1);
  y_2.replace("x", x_value_2);
  QByteArray arr_chars_1 = y_1.toLocal8Bit();
  char *ptr_arr_chars_1 = arr_chars_1.data();
  QByteArray arr_chars_2 = y_2.toLocal8Bit();
  char *ptr_arr_chars_2 = arr_chars_2.data();
  baza(ptr_arr_chars_1, &result_1);
  baza(ptr_arr_chars_2, &result_2);
  if (fabs(fabs(result_1) - fabs(result_2)) > 1) check = 1;
  return check;
}

void GraphForm::closeEvent(QCloseEvent *event) {
  event->accept();
  emit close();
}
