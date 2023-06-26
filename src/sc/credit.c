#include "smartcalc.h"
/*
 * 1- аннуитетный
 * 2 - дифференцированный
 */

///
/// \param total_credit Общая сумма кредита
/// \param distance Срок кредита
/// \param percent Процентная ставка
/// \param per_month Ежемесячный платеж
/// \param overpayment Переплата
/// \param total_payment Общая выплата
/// \return Возвращает результат операции.
int credit_main(double total_credit, int distance, double percent,
                double *per_month, double *overpayment, double *total_payment) {
  int error = 0;
  struct CreditInfo info = {0};
  info.total_credit = total_credit;
  info.distance = distance;
  info.percent = percent;
  annuitent(&info, per_month, overpayment, total_payment);
  if (isnan(*per_month) || isnan(*overpayment) || isnan(*total_payment))
    error = 1;
  return error;
}

///
/// \param info Стуктура запроса кредита
/// \param per_month Ежемесячная плата
/// \param overpayment  Переплата
/// \param total_payment Общая выплата
void annuitent(const struct CreditInfo *info, double *per_month,
               double *overpayment, double *total_payment) {
  double m = info->percent / 12;  // процентная ставка в месяц
  *per_month = info->total_credit * (m / (1 - pow((1 + m), -(info->distance))));
  *total_payment = *per_month * info->distance;
  *overpayment = *total_payment - info->total_credit;
}

///
/// \param total_credit Общая сумма кредита
/// \param percent Процентная ставка
/// \param distance Срок кредита
/// \param days_m Количество дней в месяцев
/// \param days_y Количество дней в году
/// \param total_credit_new Изменяемый общий кредит
/// \param total_payment Общая выплата
/// \param overpayment Переплата
/// \param per_month Ежемесячный платеж
void diff_2(double total_credit, double percent, int distance, int days_m,
            int days_y, double *total_credit_new, double *total_payment,
            double *overpayment, double *per_month) {
  double pay_per_month_total = total_credit / distance;
  double interest = *total_credit_new * days_m * percent / days_y;
  *per_month = pay_per_month_total + interest;
  *total_credit_new -= pay_per_month_total;
  *total_payment += *per_month;
  *overpayment = *total_payment - total_credit;
}
