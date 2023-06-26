#include "smartcalc.h"

///
/// \param string Строка которую мы проверяем
/// \return
int s21_validator(char *string) {
  int check = NORMALAISEN;
  int brace_open = 0, brace_close = 0;
  s21_check_low_start(string, &check);
  for (int i = 0; i < (int)strlen(string); i++) {
    if (check == NORMALAISEN) {
      s21_check_braces(string, i, &check);
    }
    if (check == NORMALAISEN) {
      s21_check_znaki(string, i, &check);
    }
    if (check == NORMALAISEN) {
      s21_check_full(string, &i, &brace_open, &brace_close, &check);
    }
  }
  s21_check_quantity_braces(brace_open, brace_close, &check);
  return check;
}

///
/// \param string Строка в которой делаем проверку на начальное выражние и её
/// длину \param check Результат проверки
void s21_check_low_start(char *string, int *check) {
  if (strlen(string) < 1 || strlen(string) > 256) {
    *check = OVER_STRING;
  }
  if (string[0] == '0' && string[1] == '0') {
    *check = INCORRECT;
  } else if (string[0] == '*' || string[0] == '/' || string[0] == 'm' ||
             string[0] == '^') {
    *check = INCORRECT;
  }
}

///
/// \param string Строка, в которой проверяем скобки
/// \param index Индекс символа который проверяем
/// \param check Результат проверки
void s21_check_braces(char *string, int index, int *check) {
  if ((string[index] == '(') && (string[index + 1] == ')')) {
    *check = VACUUM;
  }
  if ((string[index] == '*' || string[index] == '/' || string[index] == '+' ||
       string[index] == '-' || string[index] == '^') &&
      (string[index + 1] == ')') && (*check == NORMALAISEN)) {
    *check = INCORRECT;
  }
}

///
/// \param string Строка, в которой проверяем знаки
/// \param index Индекс символа, который проверяем
/// \param check Результат проверки
void s21_check_znaki(char *string, int index, int *check) {
  if ((string[index] == '*' || string[index] == '/' || string[index] == '^' ||
       string[index] == '+' || string[index] == '-') &&
      (string[index + 1] == '*' || string[index + 1] == '/' ||
       string[index + 1] == '^' || string[index + 1] == '+' ||
       string[index + 1] == '-')) {
    *check = INCORRECT;
  }
  if (*check == NORMALAISEN) {
    int index_last_char = strlen(string) - 1;
    if ((string[index_last_char] == '*' || string[index_last_char] == '/' ||
         string[index_last_char] == '^' || string[index_last_char] == '+' ||
         string[index_last_char] == '-') &&
        *check == NORMALAISEN) {
      *check = INCORRECT;
    }
    if (string[index] == '/' && string[index + 1] == '0' &&
        string[index + 2] != '.' && *check == NORMALAISEN) {
      *check = SADNESS_MATH;
    }
  }
}

///
/// \param string Строка в которой будем все проверять
/// \param index Индекс текущего символа на проверку
/// \param brace_open Счетчик количества открывающих скобок
/// \param brace_close Счетчик количество закрывающих скобок
/// \param check Результат проверки
void s21_check_full(char *string, int *index, int *brace_open, int *brace_close,
                    int *check) {
  if (string[*index] == '.') {
    *index = *index;
  } else if (*index > 0 && string[*index - 1] == ')' &&
             (string[*index] == 'a' || string[*index] == 'c' ||
              string[*index] == 's' || string[*index] == 't' ||
              string[*index] == 'l')) {
    *check = INCORRECT;
  } else if (string[*index] == 'x') {
    *index = *index;
  } else if (string[*index] >= '0' && string[*index] <= '9') {
    *index = *index;
  } else if ((string[*index] == '*' || string[*index] == '/' ||
              string[*index] == '^' || string[*index] == '+' ||
              string[*index] == '-')) {
    *index = *index;
  } else if (string[*index] == '(') {
    *brace_open = *brace_open + 1;
  } else if (string[*index] == ')') {
    *brace_close = *brace_close + 1;
  } else if (string[*index] == 'c' && string[*index + 1] == 'o' &&
             string[*index + 2] == 's' && string[*index + 3] == '(') {
    *index = *index + 2;
  } else if (string[*index] == 's' && string[*index + 1] == 'i' &&
             string[*index + 2] == 'n' && string[*index + 3] == '(') {
    *index = *index + 2;
  } else if (string[*index] == 't' && string[*index + 1] == 'a' &&
             string[*index + 2] == 'n' && string[*index + 3] == '(') {
    *index = *index + 2;
  } else if (string[*index] == 'a' && string[*index + 1] == 'c' &&
             string[*index + 2] == 'o' && string[*index + 3] == 's' &&
             string[*index + 4] == '(') {
    *index = *index + 3;
  } else if (string[*index] == 'a' && string[*index + 1] == 's' &&
             string[*index + 2] == 'i' && string[*index + 3] == 'n' &&
             string[*index + 4] == '(') {
    *index = *index + 3;
  } else if (string[*index] == 'a' && string[*index + 1] == 't' &&
             string[*index + 2] == 'a' && string[*index + 3] == 'n' &&
             string[*index + 4] == '(') {
    *index = *index + 3;
  } else if (string[*index] == 's' && string[*index + 1] == 'q' &&
             string[*index + 2] == 'r' && string[*index + 3] == 't' &&
             string[*index + 4] == '(') {
    *index = *index + 3;
  } else if (string[*index] == 'l' && string[*index + 1] == 'o' &&
             string[*index + 2] == 'g' && string[*index + 3] == '(') {
    *index = *index + 2;
  } else if (string[*index] == 'l' && string[*index + 1] == 'n' &&
             string[*index + 2] == '(') {
    *index = *index + 1;
  } else if (string[*index] == 'm' && string[*index + 1] == 'o' &&
             string[*index + 2] == 'd' &&
             (string[*index + 3] >= '0' || string[*index + 3] <= '9' ||
              string[*index + 3] == '(')) {
    *index = *index + 2;
  } else {
    *check = INCORRECT;
  }
  if (*brace_close > *brace_open) {
    *check = INCORRECT;
  }
}

///
/// \param brace_open Счетчик количества октрывающих скобок
/// \param brace_close Счетчик количества закрывающих
/// \param check Результат проверки
void s21_check_quantity_braces(int brace_open, int brace_close, int *check) {
  if (brace_open != brace_close && *check == 0) {
    *check = LONE_BRACE;
  }
}