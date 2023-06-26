#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NORMALAISEN 0  // Нормально стелишь, кожаный ублюдок
#define INCORRECT 1  // Неверные данные
#define OVER_STRING 2  // Слишком длинная строка(больше 256)
#define SADNESS_MATH 3  // Делить на ноль незя!
#define LONE_BRACE 4  // Количество скобок не совпадает, не разлучай их
#define VACUUM 5      // В скобках пусто

/// Validator ///
int baza(char *string,
         double *answer);  // Это база! Она вызывается в вьюшке qt.
int s21_validator(
    char *string);  // Батя, который решит пускать сына в замес или нет
void s21_check_low_start(char *string,
                         int *check);  // Проверка на начало выражения
void s21_check_braces(char *string, int index,
                      int *check);  // Проверка на скобочки
void s21_check_znaki(char *string, int index,
                     int *check);  // Проверка на арифметические знаки
void s21_check_full(char *string, int *index, int *brace_open, int *brace_close,
                    int *check);  // Полная проверка с функциями
void s21_check_quantity_braces(
    int brace_open, int brace_close,
    int *check);  // Проверка на общее количество скобок
void s21_token(char *string, char *token, char **tokens,
               int *num_tokens);  // Токенизируем строку
void s21_sortir(char **tokens, int num_tokens,
                double *answer);  // Выполняем сортировку чисел и знаков
void reshala(char **stack_znakov, double *stack_numbers, int *num_count_znakov,
             int *num_count_numbers, int num_tokens, int znaks, int numbers,
             int minus, double *result);  // Тут вычисляшки
int priority(
    char **stack_znakov,
    int num_count_znakov);  // Выставляем приоритет текущему и последнему знаку
int znak(char **stack_znakov, int num_count_znakov);  // Определяет оператор
double pop(const double *stack_numbers,
           int *num_count_numbers);  // Вытаскивает верхнее число стека
void calculation(char **stack_znakov, double *stack_numbers,
                 int *num_count_znakov,
                 int *num_count_numbers);  // Вычисляшки при приоритетах
void push(double *stack_numbers, int *num_count_numbers,
          double value);  // Засовывает значение в стек
void replaceOper(
    char **stack_znakov,
    int *num_count_znakov);  // Замена предпоследнего знака на последний
void dobivka(double *stack_numbers, char **stack_znakov, int *num_count_znakov,
             int *num_count_numbers);  // Окончательный ответ
double dobivka_help(double num_1, double num_2, double *result,
                    int oper);  //помогатор для добивки
void reshala_scobs(char **stack_znakov, double *stack_numbers,
                   int *num_count_numbers,
                   int *num_count_znakov);  // Тут решаются скобки
void reshala_trigan(char **stack_znakov, double *stack_numbers,
                    int *num_count_numbers,
                    int *num_count_znakov);  // тут решаются триг функции
void reshala_stepen(char **stack_znakov, double *stack_numbers,
                    int *num_count_znakov,
                    int *num_count_numbers);  //  Работа со степенью
void minus(char **stack_znakov, double *stack_numbers, int *num_count_znakov,
           int *num_count_numbers);  // Здесь колдуются отрицательные числа
struct CreditInfo {
  double total_credit;
  int distance;
  double percent;
};
int credit_main(
    double total_credit, int distance, double percent, double *per_month,
    double *overpayment,
    double *total_payment);  // сюда приходит все для вычисления кредита
void annuitent(const struct CreditInfo *info, double *per_month,
               double *overpayment,
               double *total_payment);  // Тут расчет аннуитента
void diff_2(double total_credit, double percent, int distance, int days_m,
            int days_y, double *total_credit_new, double *total_payment,
            double *overpayment, double *per_month);  // Тут расчет диф платежа
void deposit_main(double *deposit_amount, double percent,
                  double *interest_charges,
                  double *tax);  // Главная функция для депозита
void deposit_year(double *deposit_amount, double percent,
                  double *interest_charges,
                  double *tax);  // Депозит ежемесячный
void deposit_plus_minus(double *deposit_amount, double am_act,
                        int type_act);  // Депозит при списании и зачислении
