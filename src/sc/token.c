#include "smartcalc.h"

///
/// \param string Строка, которую будем разбивать на токены
/// \param token Массив строки для токена, он будет наполняться символами
/// \param tokens Массив строк. Сюда будет добавляться токен, когда наполнится.
/// \param num_tokens Общее количество токенов.
void s21_token(char *string, char *token, char **tokens, int *num_tokens) {
  int token_len = 0;
  for (int i = 0; i < (int)strlen(string); i++) {
    if (isdigit(string[i]) || string[i] == '.') {
      /// Catch mod 1
      if (i > 0 && string[i - 1] == 'd') {
        token[token_len] = '\0';
        strcpy(tokens[(*num_tokens)++], token);
        token_len = 0;
      }
      token[token_len++] = string[i];
    } else if (isalpha(string[i])) {
      /// Catch mod 2
      if (string[i] == 'm') {
        token[token_len] = '\0';
        strcpy(tokens[(*num_tokens)++], token);

        token_len = 0;
      }
      token[token_len++] = string[i];
    } else {
      if (token_len > 0) {
        token[token_len] = '\0';
        strcpy(tokens[(*num_tokens)++], token);

        token_len = 0;
      }
      if (!isspace(string[i])) {
        char delim[2] = {string[i], '\0'};
        strcpy(tokens[(*num_tokens)++], delim);
      }
    }
  }
  if (token_len > 0) {
    token[token_len] = '\0';
    strcpy(tokens[(*num_tokens)++], token);
  }
}
