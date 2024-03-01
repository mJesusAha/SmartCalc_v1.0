#include "c.h"
void sort(int i, str* text, char* string);
int s21_calc(char* string, double x, double* result) {
  char res[100];
  cleanArray(res, 100);
  int errors = s21_result(string, res, x);
  *result = myatof(res);
  return errors;
}

int s21_result(const char* st, char* re, double X) {
  char string[MAX];
  for (int i = 0; i < MAX; i++) {
    string[i] = 0;
  }
  for (int i = 0; st[i] != 0; i++) {
    string[i] = st[i];
  }
  str text;
  text.errors = (strlen(string) > 255) ? 1 : 0;
  text.flagNum = 0;
  cleanMass(&text, MAX);
  int res = stringProcessing(string);
  if (res > 0) {
    text.errors = 1;
  }
  if (res == 0) {
    for (int i = 0; string[i] != 0; i++) {
      sort(i, &text, string);
    }
  }
  text.errors = checkNat(text.string_out) + text.errors;
  text.X = X;
  double result = 0;
  if (text.errors == 0) {
    result = calculation(&text);
  }
  int ret = 0;
  if ((text.errors) > 0) {
    ret = -1;
  }
  sprintf(re, "%.10f", result);
  return ret;
}

void sort(int i, str* text, char* string) {
  int n = transferringNumberToString(text, string, i);
  if (n == 1) {
    if ((string[i] != ')' && string[i] != '(' && string[i + 1] != 0)) {
      int j = strlen(text->stek) - 1;

      while (functionPriority(string, i) <= functionPriority((text->stek), j) &&
             j >= 0 && text->stek[j] != '(') {
        transferringSimbolToStrOut(text);
        j--;
      }
      transferringsimbolToSteck(text, string, i);
    } else {
      transferringsimbolToSteck(text, string, i);
      forBracket(text, string, i);
    }
  }
  if (string[i + 1] == 0) {
    while (strlen(text->stek) > 0) {
      transferringSimbolToStrOut(text);
    }
  }
}

int checkNat(char* str) {
  int ret = 0;
  int j = strlen(str);
  if ((j >= 2 && (str[j - 1] == '~' || str[j - 1] == '.' ||
                  (str[j - 2] >= 48 && str[j - 2] <= 57) || str[j - 2] == 'X' ||
                  str[j - 2] == 'x' || str[j - 2] == 'E' ||
                  (str[j - 1] >= 48 && str[j - 1] <= 57) || str[j - 1] == 'X' ||
                  str[j - 1] == 'x' || str[j - 1] == 'E' || str[j - 1] == 'e' ||
                  str[j - 2] == 'e')) ||
      j < 2) {
    ret = 1;
  }
  return ret;
}

int transferringSimbolToStrOut(str* text) {
  int k = strlen(text->string_out);
  text->string_out[k] = text->stek[strlen(text->stek) - 1];
  text->stek[strlen(text->stek) - 1] = 0;
  text->string_out[k + 1] = 0;
  return 0;
}
int forBracket(str* text, const char* string, int i) {
  int res = 0;
  int j = strlen(text->stek);
  int k = strlen(text->string_out);
  if (string[i] == ')' && k + j < MAX) {
    while (j > 1 && text->stek[j - 1] != '(') {
      if (text->stek[j - 1] != ')') {
        int t = strlen(text->string_out);
        text->string_out[t] = text->stek[j - 1];
        text->string_out[t + 1] = 0;
        text->stek[j - 1] = 0;
      }
      j--;
    }
    if (text->stek[j - 1] == '(' && j - 1 > 0) {
      text->stek[j - 1] = 0;
    }
  }
  return res;
}

int functionPriority(char* string, int i) {
  int priority = 0;
  if (i >= 0) {
    char func[] = {"sctmCSTqlL"};
    if (strchr(func, string[i]) != NULL) {
      priority = 3;
    } else if (string[i] == '+' || string[i] == '-') {
      priority = 1;
    } else if (string[i] == '*' || string[i] == '/' || string[i] == '%') {
      priority = 2;
    } else if (string[i] == '^') {
      priority = 4;
    }
  }
  return priority;
}

int transferringsimbolToSteck(str* text, const char* string, int i) {
  int j = strlen(text->stek);
  if (j + 2 < MAX && j >= 0) {
    text->stek[j] = string[i];
    text->stek[j + 1] = 0;
  }
  return 0;
}
int transferringNumberToString(str* text, const char* string, int i) {
  int res = 1;
  if (((string[i] == 126 && (string[i + 1] >= 48 && string[i + 1] <= 57)) ||
       (string[i] >= 48 && string[i] <= 57)) &&
      strlen(text->string_out) < MAX) {
    text->flagNum = 1;
    res = 0;
  }
  if ((((string[i] == 'x' || string[i] == 'X') ||
        (string[i] == 126 && (string[i + 1] == 'x' || string[i + 1] == 'X'))) &&
       strlen(text->string_out) < MAX) &&
      text->flagNum == 0) {
    res = 0;
    // Если есть унарный минус, a за ним x или X и нет права ставить точку то
    // помечаем что перед нами цифра
  }
  if ((string[i] == 46 && text->flagNum == 1) &&
      strlen(text->string_out) < MAX) {
    text->flagNum = 0;
    res = 0;

    // Если уже точно цифра, и можно поставить символ дроби (точку)
  }
  if (((string[i] == 'x' || string[i] == 'X') && text->flagNum == 1) ||
      ((string[i] == 46 && (string[i + 1] == 'x' || string[i + 1] == 'X')) ||
       ((string[i] == 'e' || string[i] == 'E') &&
        text->flagNum == 0)) /*||(string[i] == 46 && text->flagNum == 1)*/) {
    res = -1;  // Если есть цифра и пошел х, если есть точка и пошел х, или ecть
               // е но перед ней не было цифры
    // Если есть точка но перед ней нет цифры, если есть x, и перед ним точка,
    // если есть точка и пошел х, если пошла цифра и за ней х
    //  то re = -1 это ошибка выражения!!!!
  }
  if (res < 0) {
    text->errors = 1;
  }
  if (res == 0) {
    text->string_out[strlen(text->string_out)] = string[i];
    text->string_out[strlen(text->string_out)] = 0;
  }
  if ((res == 0 &&
       (string[i + 1] != 126 && string[i + 1] != 46 && string[i + 1] != 'x' &&
        string[i + 1] != 'X') &&
       (string[i + 1] < 48 || string[i + 1] > 57)) &&
      strlen(text->string_out) < MAX) {
    text->flagNum = 0;
    text->string_out[strlen(text->string_out)] = ' ';
    text->string_out[strlen(text->string_out)] = 0;
  }

  return res;
}
void cleanMass(str* mas, int max) {
  for (int i = 0; i < max; i++) {
    mas->stek[i] = 0;
    mas->string_out[i] = 0;
  }
}
