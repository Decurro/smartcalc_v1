#include "smartcalc.h"

/*
priority (priority operation):
1 - + -
2 - / * mod
3 - ^ sin cos... log ln
*/

///
/// \param stack_znakov Массив знаков
/// \param stack_numbers Массив чисел
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \param num_count_numbers
/// Индекс вершины массива чисел / (Так же может быть как  текущее количество
/// элементов в стеке чисел)
/// \param num_tokens Общее количество токенов
/// \param znaks Счетчик количества знаков всего
/// \param numbers  Счетчик количества чисел всего
/// \param minus_help Помогатор для определения минуса
/// \param result Ответ
void reshala(char **stack_znakov, double *stack_numbers, int *num_count_znakov,
             int *num_count_numbers, int num_tokens, int znaks, int numbers,
             int minus_help, double *result) {
  int last_sym = 0;
  int current_sym = 0;
  double answer = 0;
  if (minus_help == 1)
    minus(stack_znakov, stack_numbers, num_count_znakov, num_count_numbers);
  if (*num_count_numbers == num_tokens)
    *result = stack_numbers[*num_count_numbers - 1];
  if (*num_count_znakov >= 1 &&
      strcmp(stack_znakov[(*num_count_znakov) - 1], "(") != 0) {
    if (*num_count_znakov >= 2 &&
        strcmp(stack_znakov[(*num_count_znakov) - 2], "(") != 0) {
      /// Тут работа со степенью
      if (strcmp(stack_znakov[(*num_count_znakov) - 2], "^") == 0 &&
          strcmp(stack_znakov[(*num_count_znakov) - 1], "^") != 0) {
        reshala_stepen(stack_znakov, stack_numbers, num_count_znakov,
                       num_count_numbers);
      } else if (strcmp(stack_znakov[(*num_count_znakov) - 1], "^") != 0 &&
                 *num_count_numbers >= 2 &&
                 strcmp(stack_znakov[(*num_count_znakov) - 1], ")") != 0) {
        last_sym = priority(stack_znakov, (*num_count_znakov - 2));
        current_sym = priority(stack_znakov, (*num_count_znakov - 1));
        if (last_sym >= current_sym) {
          calculation(stack_znakov, stack_numbers, num_count_znakov,
                      num_count_numbers);
          if (*num_count_znakov >= 2) {
            last_sym = priority(stack_znakov, (*num_count_znakov - 2));
            current_sym = priority(stack_znakov, (*num_count_znakov - 1));
            if (last_sym >= current_sym)
              calculation(stack_znakov, stack_numbers, num_count_znakov,
                          num_count_numbers);
          }
          /// Функция возьмет два последних числа и предпоследний оператор
        }
      }
    }
    if (*num_count_znakov > 1 &&
        strcmp(stack_znakov[(*num_count_znakov) - 1], ")") == 0) {
      if (*num_count_znakov > 0) (*num_count_znakov)--;
      while ((*num_count_znakov >= 1) &&
             strcmp(stack_znakov[(*num_count_znakov) - 1], "(") != 0) {
        reshala_scobs(stack_znakov, stack_numbers, num_count_numbers,
                      num_count_znakov);
        if (*num_count_znakov > 0) (*num_count_znakov)--;
      }
      /// Здесь функция которая будет чекать, стоит ли перед скобкой "("
      /// какая-нибудь функция(cos,sin и т.п.), чтобы произвести вычисления и
      /// занести в стек
      if (*num_count_znakov > 0) (*num_count_znakov)--;
      if (*num_count_znakov >= 1 &&
          priority(stack_znakov, (*num_count_znakov) - 1) == 3) {
        reshala_trigan(stack_znakov, stack_numbers, num_count_numbers,
                       num_count_znakov);
      }
    }
    if (znaks + numbers == num_tokens) {
      dobivka(stack_numbers, stack_znakov, num_count_znakov, num_count_numbers);
      if (*num_count_numbers == 1)
        answer = stack_numbers[*num_count_numbers - 1];
      if (*num_count_znakov > 0) {
        int check = priority(stack_znakov, *num_count_znakov - 1);
        if (check == 3 || check == 2) answer = NAN;
      }
      *result = answer;
    }
  }
}

///
/// \param stack_znakov Массив знаков
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \return Возвращает приоритет знака
int priority(char **stack_znakov, int num_count_znakov) {
  int result = 0;
  if ((strcmp(stack_znakov[num_count_znakov], "+") == 0) ||
      (strcmp(stack_znakov[num_count_znakov], "-") == 0)) {
    result = 1;
  }
  if ((strcmp(stack_znakov[num_count_znakov], "*") == 0) ||
      (strcmp(stack_znakov[num_count_znakov], "/") == 0) ||
      (strcmp(stack_znakov[num_count_znakov], "mod") == 0)) {
    result = 2;
  }
  if (result != 1 && result != 2 &&
      ((strcmp(stack_znakov[num_count_znakov], "(") != 0) &&
       (strcmp(stack_znakov[num_count_znakov], ")") != 0)) &&
      (strcmp(stack_znakov[num_count_znakov], "^") != 0)) {
    result = 3;
  }
  return result;
}

///
/// \param stack_znakov Массив знаков
/// \param stack_numbers  Массив чисел
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
void calculation(char **stack_znakov, double *stack_numbers,
                 int *num_count_znakov, int *num_count_numbers) {
  double num_2 = pop(stack_numbers, num_count_numbers);
  double num_1 = pop(stack_numbers, num_count_numbers);
  int operator= 0;
  double result = 0;
  operator= znak(stack_znakov, (*num_count_znakov - 2));
  switch (operator) {
    case 1:
      result = num_1 + num_2;
      break;
    case 2:
      result = num_1 - num_2;
      break;
    case 3:
      result = num_1 * num_2;
      break;
    case 4:
      result = num_1 / num_2;
      break;
    case 5:
      result = fmod(num_1, num_2);
      break;
    default:
      break;
  }
  push(stack_numbers, num_count_numbers, result);
  replaceOper(stack_znakov, num_count_znakov);
}

///
/// \param stack_znakov Массив знаков
/// \param num_count_znakov  Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \return Возвращает значение, определяющее знак
int znak(char **stack_znakov, int num_count_znakov) {
  int result = 0;
  if (num_count_znakov >= 0) {
    if (strcmp(stack_znakov[num_count_znakov], "+") == 0) {
      result = 1;
    } else if (strcmp(stack_znakov[num_count_znakov], "-") == 0) {
      result = 2;
    } else if (strcmp(stack_znakov[num_count_znakov], "*") == 0) {
      result = 3;
    } else if (strcmp(stack_znakov[num_count_znakov], "/") == 0) {
      result = 4;
    } else if (strcmp(stack_znakov[num_count_znakov], "mod") == 0) {
      result = 5;
    } else if (strcmp(stack_znakov[num_count_znakov], "^") == 0) {
      result = 15;
    }
  }
  if (num_count_znakov >= 1 && result == 0) {
    if (strcmp(stack_znakov[num_count_znakov - 1], "cos") == 0) {
      result = 6;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "sin") == 0) {
      result = 7;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "tan") == 0) {
      result = 8;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "acos") == 0) {
      result = 9;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "asin") == 0) {
      result = 10;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "atan") == 0) {
      result = 11;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "sqrt") == 0) {
      result = 12;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "ln") == 0) {
      result = 13;
    } else if (strcmp(stack_znakov[num_count_znakov - 1], "log") == 0) {
      result = 14;
    }
  }
  return result;
}

///
/// \param stack_numbers Массив чисел
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \return Возвращает последее(верхнее) чисало стека чисел
double pop(const double *stack_numbers, int *num_count_numbers) {
  double value = 0;
  if (*num_count_numbers > 0) {
    value = stack_numbers[*num_count_numbers - 1];

    (*num_count_numbers)--;
  }
  return value;
}

///
/// \param stack_numbers Массив чисел
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
/// \param value Значение, которое будет отправлено в стек чисел
void push(double *stack_numbers, int *num_count_numbers, double value) {
  stack_numbers[*num_count_numbers] = value;
  (*num_count_numbers)++;
}

///
/// \param stack_znakov Массив знаков
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
void replaceOper(char **stack_znakov, int *num_count_znakov) {
  if ((*num_count_znakov - 2 >= 0)) {
    strcpy(stack_znakov[*num_count_znakov - 2],
           stack_znakov[*num_count_znakov - 1]);
  }
  if (*num_count_znakov > 0) (*num_count_znakov)--;
}

///
/// \param stack_numbers Массив чисел
/// \param stack_znakov Массив знаков
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
void dobivka(double *stack_numbers, char **stack_znakov, int *num_count_znakov,
             int *num_count_numbers) {
  double result = 0;
  while (*num_count_numbers > 1) {
    double num_2 = pop(stack_numbers, num_count_numbers);
    double num_1 = pop(stack_numbers, num_count_numbers);
    int operator= 0;
    operator= znak(stack_znakov, (*num_count_znakov - 1));
    push(stack_numbers, num_count_numbers,
         dobivka_help(num_1, num_2, &result, operator));
    if (*num_count_znakov > 0) (*num_count_znakov)--;
  }
}

///
/// \param num_1 Предпоследнее число массива чисел
/// \param num_2 Последнее число массива чисел
/// \param result Результат вычисления между числами
/// \param oper Значение, определяющая знак для выполнения вычисления
/// \return Возвращает результат вычисления
double dobivka_help(double num_1, double num_2, double *result, int oper) {
  switch (oper) {
    case 1:
      *result = num_1 + num_2;
      break;
    case 2:
      *result = num_1 - num_2;
      break;
    case 3:
      *result = num_1 * num_2;
      break;
    case 4:
      *result = num_1 / num_2;
      break;
    case 5:
      *result = fmod(num_1, num_2);
      break;
    case 15:
      *result = pow(num_1, num_2);
      break;
    default:
      break;
  }
  return *result;
}

///
/// \param stack_znakov Массив знаков
/// \param stack_numbers Массив чисел
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
void reshala_scobs(char **stack_znakov, double *stack_numbers,
                   int *num_count_numbers, int *num_count_znakov) {
  if (*num_count_numbers >= 1) {
    double num_2 = pop(stack_numbers, num_count_numbers);
    double num_1 = pop(stack_numbers, num_count_numbers);
    int operator= 0;
    double result = 0;
    operator= znak(stack_znakov, (*num_count_znakov - 1));
    push(stack_numbers, num_count_numbers,
         dobivka_help(num_1, num_2, &result, operator));
  }
}

///
/// \param stack_znakov Массив знаков
/// \param stack_numbers Массив чисел
/// \param num_count_numbers  Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
void reshala_trigan(char **stack_znakov, double *stack_numbers,
                    int *num_count_numbers, int *num_count_znakov) {
  double num_1 = pop(stack_numbers, num_count_numbers);
  int minus = 1;
  if ((*num_count_znakov > 2 &&
       strcmp(stack_znakov[*num_count_znakov - 2], "-") == 0 &&
       strcmp(stack_znakov[*num_count_znakov - 3], "(") == 0))
    minus = -1;
  int operator= 0;
  double result = 0;
  operator= znak(stack_znakov, (*num_count_znakov));
  switch (operator) {
    case 6:
      result = cos(num_1) * minus;
      break;
    case 7:
      result = sin(num_1) * minus;
      break;
    case 8:
      result = tan(num_1) * minus;
      break;
    case 9:
      result = acos(num_1) * minus;
      break;
    case 10:
      result = asin(num_1) * minus;
      break;
    case 11:
      result = atan(num_1) * minus;
      break;
    case 12:
      result = sqrt(num_1) * minus;
      break;
    case 13:
      result = log(num_1) * minus;
      break;
    case 14:
      result = log10(num_1) * minus;
      break;
    default:
      break;
  }
  push(stack_numbers, num_count_numbers, result);
  if (*num_count_znakov > 0) {
    (*num_count_znakov)--;
    if (minus == -1) (*num_count_znakov)--;
  }
}

///
/// \param stack_znakov Массив знаков
/// \param stack_numbers  Массив чисел
/// \param num_count_znakov  Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
void reshala_stepen(char **stack_znakov, double *stack_numbers,
                    int *num_count_znakov, int *num_count_numbers) {
  while (*num_count_znakov > 1 &&
         strcmp(stack_znakov[(*num_count_znakov) - 2], "^") == 0) {
    double num_2 = pop(stack_numbers, num_count_numbers);
    double num_1 = pop(stack_numbers, num_count_numbers);
    double result = 0;
    result = pow(num_1, num_2);
    push(stack_numbers, num_count_numbers, result);
    replaceOper(stack_znakov, num_count_znakov);
  }
}

///
/// \param stack_znakov Массив чисел
/// \param stack_numbers Массив знаков
/// \param num_count_znakov Индекс вершины массива знаков / (Так же может быть
/// как  текущее количество элементов в стеке знаков)
/// \param num_count_numbers Индекс вершины массива чисел / (Так же может быть
/// как  текущее количество элементов в стеке чисел)
void minus(char **stack_znakov, double *stack_numbers, int *num_count_znakov,
           int *num_count_numbers) {
  double result = 0;
  double num_1 = 0;
  if (*num_count_znakov == 1 && *num_count_numbers == 1 &&
      (strcmp(stack_znakov[(*num_count_znakov) - 1], "-") == 0)) {
    num_1 = pop(stack_numbers, num_count_numbers);
    result = 0 - num_1;
    push(stack_numbers, num_count_numbers, result);
    if (*num_count_znakov > 0) (*num_count_znakov)--;
  }
  if (*num_count_znakov > 2 &&
      (strcmp(stack_znakov[(*num_count_znakov) - 1], "-") == 0 &&
       (strcmp(stack_znakov[(*num_count_znakov) - 2], "(") == 0)) &&
      *num_count_znakov > *num_count_numbers &&
      priority(stack_znakov, *num_count_znakov - 3) != 3) {
    num_1 = pop(stack_numbers, num_count_numbers);
    result = 0 - num_1;
    push(stack_numbers, num_count_numbers, result);
    if (*num_count_znakov > 0) (*num_count_znakov) -= 1;
  }
}
