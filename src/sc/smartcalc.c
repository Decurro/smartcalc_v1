#include "smartcalc.h"

///
/// \param string строка, которую будем проверять и решать
/// \param answer ответ, куда будет занесе в случае его получения
/// \return  возвращает значение о том, что решил и все хорошо или столкнулся с
/// проблемами.
int baza(char *string, double *answer) {
  int error = 0;
  if (s21_validator(string) == NORMALAISEN) {
    int len = strlen(string);
    char *token = malloc(len + 1);
    char **tokens = malloc(len * sizeof(char *));
    for (int i = 0; i < len; i++) {
      tokens[i] = (char *)calloc(256, sizeof(char));
    }
    int num_tokens = 0;
    s21_token(string, token, tokens, &num_tokens);
    if (num_tokens > 0) s21_sortir(tokens, num_tokens, answer);
    if (isnan(*answer) || isinf(*answer)) {
      error = 2;
    }
    for (int i = 0; i < len; i++) {
      free(tokens[i]);
    }
    free(tokens);
    free(token);

  } else {
    error = 1;
  }

  return error;
}
