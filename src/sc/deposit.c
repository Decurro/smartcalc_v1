#include "smartcalc.h"

///
/// \param deposit_amount Сумма вклада
/// \param percent Процентная ставка
/// \param interest_charges Общая выплата процентов
/// \param tax Налоги
void deposit_main(double *deposit_amount, double percent,
                  double *interest_charges, double *tax) {
  double percent_month = percent / 12;
  double per_month = *deposit_amount * percent_month;
  double taxes = per_month * 0.13;
  *deposit_amount += per_month;
  *interest_charges += per_month;
  *tax += taxes;
}

///
/// \param deposit_amount Сумма вклада
/// \param percent Процентная ставка
/// \param interest_charges  Общая выплата процентов
/// \param tax Налоги
void deposit_year(double *deposit_amount, double percent,
                  double *interest_charges, double *tax) {
  double per_year = *deposit_amount * percent;
  double taxes = per_year * 0.13;
  *deposit_amount += per_year;
  *interest_charges += per_year;
  *tax += taxes;
}

///
/// \param deposit_amount Сумма вклада
/// \param am_act Сумма действия
/// \param type_act Тип действия(списание/зачисление)
void deposit_plus_minus(double *deposit_amount, double am_act, int type_act) {
  if (type_act == 0) {
    *deposit_amount += am_act;
  }
  if (type_act == 1) {
    *deposit_amount -= am_act;
  }
}