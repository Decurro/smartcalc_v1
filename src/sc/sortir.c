#include "smartcalc.h"

///
/// \param tokens Массив строк(токенов)
/// \param num_tokens  Общее количество токенов
/// \param answer Ответ полученного выражения
void s21_sortir(char **tokens, int num_tokens, double *answer) {
  double *stack_numbers_v = (double *)malloc(num_tokens * sizeof(double));
  char **stack_znakov_v = (char **)calloc(num_tokens, sizeof(char *));
  int num_count_numbers = 0;
  int num_count_znakov = 0;
  int znaks = 0;
  int numbers = 0;
  int minus_help = 0;

  for (int i = 0; i < num_tokens; i++) {
    stack_znakov_v[i] = (char *)calloc(256, sizeof(char));
  }
  for (int i = 0; i < num_tokens; i++) {
    char *endptr;
    double num = strtod(tokens[i], &endptr);
    while (isspace(*endptr)) {
      endptr++;
    }
    if (*endptr == '\0') {
      stack_numbers_v[num_count_numbers++] = num;
      numbers++;
      minus_help++;
    } else {
      strcpy(stack_znakov_v[num_count_znakov], tokens[i]);
      num_count_znakov++;
      znaks++;
    }
    reshala(stack_znakov_v, stack_numbers_v, &num_count_znakov,
            &num_count_numbers, num_tokens, znaks, numbers, minus_help, answer);
    minus_help = 0;
  }
  for (int i = 0; i < num_tokens; i++) {
    free(stack_znakov_v[i]);
  }
  free(stack_znakov_v);
  free(stack_numbers_v);
}
