#include "mainwindow.h"

#include <QWidget>

#include "creditform.h"
#include "depositform.h"
#include "graphform.h"
#include "ui_mainwindow.h"

extern "C" {
#include "smartcalc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  check_res = 0;
  GraphOpened = false;
  CreditOpened = false;
  DepositOpened = false;
  grapik = nullptr;
  credidi = nullptr;
  depopi = nullptr;
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_br_op, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_br_cl, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_c, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_answer, SIGNAL(clicked()), this,
          SLOT(digits_numbers()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->graphic, SIGNAL(clicked()), this, SLOT(push_graph()));
  connect(ui->pushButton_credit, SIGNAL(clicked()), this, SLOT(push_credit()));
  connect(ui->pushButton_deposit, SIGNAL(clicked()), this,
          SLOT(push_deposit()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbers() {
  QPushButton *button = (QPushButton *)sender();
  QString expression = button->text();
  if (check_res == 1) {
    ui->label_2->setText("0");
    check_res = 0;
  }
  if (ui->label_2->text() == "ERROR") {
    ui->label_2->setText("0");
  }
  if (expression == "=") {
    result();
  }
  if (ui->label_2->text() == "0" && expression != "." && expression != "=") {
    ui->label_2->setText(expression);
  } else {
    if (expression != "=") {
      ui->label_2->setText(ui->label_2->text() + expression);
    }
  }
  if ((expression == "sin" || expression == "cos" || expression == "tan" ||
       expression == "acos" || expression == "asin" || expression == "atan" ||
       expression == "log" || expression == "sqrt" || expression == "ln")) {
    ui->label_2->setText(ui->label_2->text() + "(");
  }
  if (expression == "AC") {
    all_clean();
  }
  if (expression == "C") {
    clean();
  }
}

void MainWindow::all_clean() { ui->label_2->setText("0"); }

void MainWindow::clean() {
  QString copy_expression = ui->label_2->text();
  copy_expression.chop(2);
  ui->label_2->setText(copy_expression);
}

void MainWindow::result() {
  int error = 0;
  double answer;
  QString x_value;
  if (ui->doubleSpinBox->value() < 0) {
    x_value = QString("(%1)").arg(QString::number(ui->doubleSpinBox->value()));
  } else {
    x_value = QString::number(ui->doubleSpinBox->value());
  }
  QString expression = ui->label_2->text();
  expression.replace("x", x_value);
  QByteArray arr_chars = expression.toLocal8Bit();
  char *ptr_arr_chars = arr_chars.data();
  error = baza(ptr_arr_chars, &answer);
  if (error == 0) {
    QString res = QString::number(answer, 'g', 15);
    ui->label_2->setText(res);
    check_res = 1;
  } else {
    ui->label_2->setText("ERROR");
  }
}

void MainWindow::push_graph() {
  if (!GraphOpened) {
    GraphOpened = true;
    grapik = new GraphForm(nullptr, ui->label_2->text());

    connect(grapik, &GraphForm::close, this, [=]() { GraphOpened = false; });
    grapik->show();
  }
}

void MainWindow::push_credit() {
  if (!CreditOpened) {
    CreditOpened = true;
    credidi = new CreditForm;

    connect(credidi, &CreditForm::close, this, [=]() { CreditOpened = false; });
    credidi->show();
  }
}

void MainWindow::push_deposit() {
  if (!DepositOpened) {
    DepositOpened = true;
    depopi = new DepositForm;

    connect(depopi, &DepositForm::close, this,
            [=]() { DepositOpened = false; });
    depopi->show();
  }
}
