#include "creditform.h"

#include <QCloseEvent>

#include "ui_creditform.h"

extern "C" {
#include "smartcalc.h"
}

CreditForm::CreditForm(QWidget* parent)
    : QWidget(parent), ui(new Ui::CreditForm) {
  ui->setupUi(this);

  QDate currentDate = QDate::currentDate();
  ui->dateEdit_date->setMinimumDate(currentDate);

  connect(ui->pushButton_calculate, SIGNAL(clicked()), this, SLOT(calculate()));
}

CreditForm::~CreditForm() { delete ui; }

void CreditForm::calculate() {
  ui->label_last_payment->setText("");
  QDate date_start = ui->dateEdit_date->date();
  QDate date_end;
  double per_month = 0;
  double overpayment = 0;
  double total_payment = 0;
  int distance = 0;
  QString per_month_text;
  QString total_payment_text;
  QString overpayment_text;
  QString last_payment_text;
  double total_credit = ui->doubleSpinBox_credit_amount->value();
  double total_credit_new = ui->doubleSpinBox_credit_amount->value();
  double percent = ui->doubleSpinBox_interest_rate->value() / 100;
  int currentIndex_type_period = ui->comboBox_type_period->currentIndex();
  if (currentIndex_type_period == 0) {
    distance = ui->spinBox_credit_period->value();
    date_end = date_start.addMonths(ui->spinBox_credit_period->value());
  } else {
    distance = ui->spinBox_credit_period->value() * 12;
    date_end = date_start.addYears(ui->spinBox_credit_period->value());
  }
  int currentIndex_type_credit = ui->comboBox_type_credit->currentIndex();
  if (currentIndex_type_credit == 0) {
    //Здесь функция из Си для ануитета
    credit_main(total_credit, distance, percent, &per_month, &overpayment,
                &total_payment);
    per_month_text = QString::number(per_month, 'g', 6);
  }

  if (currentIndex_type_credit == 1) {
    ui->textEdit_for_diff->setText(
        "Дата\t Сумма платежа\t Платеж по основному долгу\t Платеж по "
        "процентам\t Остаток долга\t\n");
    double first_payment = 0;
    double last_payment = 0;
    for (QDate date = date_start; date < date_end; date = date.addMonths(1)) {
      int days_m = date.daysInMonth();
      int days_y = date.daysInYear();
      QDate last_date = date_end.addMonths(-1);
      diff_2(total_credit, percent, distance, days_m, days_y, &total_credit_new,
             &total_payment, &overpayment, &per_month);
      if (date == date_start) first_payment = per_month;
      if (date == last_date) last_payment = per_month;
      if (total_credit_new < 0) total_credit_new = 0;
      QString list_diff = QString::number(per_month, 'g', 6);
      QString part_debt = QString::number(total_credit / distance, 'g', 6);
      QString pay_percent =
          QString::number(per_month - total_credit / distance, 'g', 6);
      QString last_debt = QString::number(total_credit_new, 'g', 6);
      ui->textEdit_for_diff->append(
          date.toString("MM.yyyy") + "\t" + list_diff + "\t\t\t" + part_debt +
          "\t\t\t" + pay_percent + "\t\t" + last_debt + "\n");
    }
    per_month_text = QString::number(first_payment, 'g', 6);
    last_payment_text = QString::number(last_payment, 'g', 6);
    ui->label_last_payment->setText("-> " + last_payment_text);
  }
  total_payment_text = QString::number(total_payment, 'g', 6);
  overpayment_text = QString::number(overpayment, 'g', 6);
  ui->label_per_month->setText(per_month_text);
  ui->label_total_payment->setText(total_payment_text);
  ui->label_overpayment->setText(overpayment_text);
}

void CreditForm::closeEvent(QCloseEvent* event) {
  event->accept();
  emit close();
}
