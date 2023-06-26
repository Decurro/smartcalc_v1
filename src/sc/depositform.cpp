#include "depositform.h"

#include <QCloseEvent>
#include <QDate>

#include "ui_depositform.h"

extern "C" {
#include "smartcalc.h"
}

DepositForm::DepositForm(QWidget *parent)
    : QWidget(parent), ui(new Ui::DepositForm) {
  ui->setupUi(this);
  list_lists = QList<QList<QVariant>>();

  connect(ui->pushButton_add, SIGNAL(clicked()), this, SLOT(add_action()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
}

DepositForm::~DepositForm() { delete ui; }

void DepositForm::add_action() {
  ui->textEdit->append(
      ui->comboBox_type_action->currentText() + "->" +
      ui->dateEdit_action->date().toString("MM.yyyy") + "->" +
      QString::number(ui->doubleSpinBox_amount_action->value()));
  add_list();
}

void DepositForm::add_list() {
  QList<QVariant> sublist;
  int type_action = ui->comboBox_type_action->currentIndex();
  QDate date_action = ui->dateEdit_action->date();
  date_action.setDate(date_action.year(), date_action.month(), 1);
  double amount_action = ui->doubleSpinBox_amount_action->value();
  sublist << type_action << QVariant(date_action) << amount_action;
  list_lists << sublist;
}

void DepositForm::calculate() {
  ui->textEdit_table->setText("");
  double total_deposit = ui->doubleSpinBox_amount_deposit->value();
  double percent = ui->doubleSpinBox_percent->value() / 100;
  int type_distance = ui->comboBox_type_distance->currentIndex();
  int distance;
  distance_convert(&distance, type_distance);
  int type_percent = ui->comboBox_type_percent->currentIndex();
  QDate date_start = ui->dateEdit_start_date->date();
  QDate date_end = date_start.addMonths(distance);
  double total_tax = 0;
  double amount_percent = 0;
  int time_year = 0;
  for (QDate date = date_start; date <= date_end; date = date.addMonths(1)) {
    deposit_add(date, &total_deposit);
    if (type_percent == 0 && date != date_start) {  //Ежемесячно
      deposit_main(&total_deposit, percent, &amount_percent, &total_tax);
      time_year = 0;

    } else {  // ежегодные проценты
      if (time_year == 12)
        deposit_year(&total_deposit, percent, &amount_percent, &total_tax);
    }
    if (time_year == 0 || time_year == 12) {
      ui->textEdit_table->append(
          date.toString("MM.yyyy") + "\t" + "Капитализация\t" +
          QString::number(total_deposit, 'g', 11) + "\t" +
          QString::number(amount_percent, 'g', 11) + "\t" +
          QString::number(total_tax, 'g', 6) + "\n");
      time_year = 0;
    }
    time_year++;
  }
  ui->label_total_amount->setText(QString::number(total_deposit, 'g', 6));
  ui->label_total_percent->setText(QString::number(amount_percent, 'g', 6));
  ui->label_total_tax->setText(QString::number(total_tax, 'g', 6));
  list_lists.clear();
  ui->textEdit->setText("");
}

void DepositForm::distance_convert(int *distance, int type_distance) {
  if (type_distance == 1) {
    *distance = ui->spinBox_count_distance->value() * 12;
  } else {
    *distance = ui->spinBox_count_distance->value();
  }
}

void DepositForm::deposit_add(QDate date, double *total_deposit) {
  for (const QList<QVariant> &sublist : list_lists) {
    int type_act = sublist[0].toInt();
    QString type_act_text;
    if (type_act == 0) type_act_text = "Зачисление";
    if (type_act == 1) type_act_text = "Списание";
    double am_act = sublist[2].toDouble();
    QDate sublistDate = sublist[1].toDate();
    if (sublistDate == date) {
      deposit_plus_minus(total_deposit, am_act, type_act);
      ui->textEdit_table->append(
          sublistDate.toString("MM.yyyy") + "\t" + type_act_text + "\t" +
          QString::number(am_act, 'g', 11) + "\t" +
          "Текущая сумма вклада: " + QString::number(*total_deposit, 'g', 11));
    }
  }
}

void DepositForm::closeEvent(QCloseEvent *event) {
  event->accept();
  emit close();
}
