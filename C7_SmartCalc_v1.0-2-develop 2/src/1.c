#include "c.h"
int stringProcessing(char* string) {
  flags A = {0};
  int res = 0, res1 = 0, res2 = 0, res3 = 0, res4 = 0, res5 = 0, res6 = 0,
      res7 = 0;
  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] != ' ') {
      res1 += readSign(string, i, &A);
      res7 += readFunc(string, i, &A);
      res2 += readSymbols(string, i);
      res3 = checkingBrackets(string, i, &A);
      res5 += checkingDoubleSign(string, i);
      res4 += readSignPlus(string, i);
      res6 += readSignMultDev(string, i);
    }
  }
  backspaseDelete(string);
  for (int i = 0; string[i] != '\0'; i++) {
    readSignPlus(string, i);
  }
  backspaseDelete(string);
  res = res + res1 + res2 + res3 + res4 + res5 + res6 + res7;
  return res;
}

int checkingDoubleSign(const char* string, int i) {
  // int temp = 1;
  int res = 0;
  if (string[i] == '*' || string[i] == '/' || string[i] == '^' ||
      string[i] == '%') {
    int temp = 1;
    while (string[i + temp] == ' ') {
      temp++;
    }
    if (string[i + temp] == '*' || string[i + temp] == '/' ||
        string[i + temp] == '^' || string[i + temp] == '%') {
      res = 1;
    }
  }
  return res;
}

int readSignPlus(char* string, int i) {
  int temp = 1;
  int res = 0;
  if (string[i] == '(' || string[i] == '^') {
    while (string[i + temp] == ' ') temp++;
    if (string[i + temp] == ')' || string[i + temp] == '*' ||
        string[i + temp] == '/' || string[i + temp] == '\0' ||
        string[i + temp] == '^' || string[i + temp] == '%') {
      res = 1;
    } else if (string[i + temp] == '+') {
      string[i + temp] = ' ';
    }
    if (string[i] == '(') {
      while (string[i + temp] == ' ') temp++;
      if (string[i + temp] == '-') string[i + temp] = '~';
    }
  }
  if (string[i] == '+') {
    while (string[i + temp] == ' ') temp++;
    if (string[i + temp] == '+') {
      string[i + temp] = ' ';
    }
    if (string[i + temp] == '-' || string[i + temp] == '~') {
      string[i + temp] = ' ';
      string[i] = '-';
    }
  }
  if (string[i] == '-') {
    while (string[i + temp] == ' ') temp++;
    if (string[i + temp] == '+') {
      string[i + temp] = ' ';
    }
    if (string[i + temp] == '-') {
      string[i + temp] = ' ';
      string[i] = '+';
    }
  }
  if (string[i] == '*' || string[i] == '/' || string[i] == '%') {
    while (string[i + temp] == ' ') temp++;
    if (string[i + temp] == '-') {
      string[i + temp] = '~';
    }
    if (string[i + temp] == '+') {
      string[i + temp] = ' ';
    }
  }
  return res;
}
int readSignMultDev(const char* string, int i) {
  int res = 0;
  if ((string[i] == '*') || (string[i] == '/') || string[i] == '%' ||
      (string[i] == '^')) {
    int temp = 1;
    while (string[i + temp] == ' ') temp++;
    if ((string[i + temp] == '*') || (string[i + temp] == '/') ||
        string[i + temp] == '%' || (string[i + temp] == '^')) {
      res = 1;
    }
  }
  return res;
}

int checkingBrackets(const char* string, int i, flags* flag) {
  int res = 1;
  if (string[i] == '(') {
    flag->counter1++;
  }
  if (string[i] == ')') {
    flag->counter2++;
  }
  if (flag->counter1 == flag->counter2)
    res = 0;
  else
    res = 1;
  return res;
}
int checkingTheFunction(const char* func, int n, char simbol, char* string,
                        int i) {
  int counter = 0, res = 1;
  for (int j = 0; j < n; j++) {
    if (string[i + j] != func[j]) {
      break;
    } else {
      counter = counter + 1;
    }
  }
  if (counter == n) {
    res = 0;
  }
  if (res == 0) {
    for (int j = 1; j < n; j++) {
      string[i] = simbol;
      string[i + j] = ' ';
    }
  }
  return res;
}
int readFunc(char* string, int i, flags* flag) {
  flag->error_f = 0;
  char* simbols = "sctmal";
  for (int j = 0; simbols[j] != '\0'; j++) {
    if (string[i] == simbols[j]) {
      int res = 0;
      res += checkingTheFunction("sin", 3, 's', string, i);
      res += checkingTheFunction("cos", 3, 'c', string, i);
      res += checkingTheFunction("tan", 3, 't', string, i);
      res += checkingTheFunction("mod", 3, 'm', string, i);
      res += checkingTheFunction("acos", 4, 'C', string, i);
      res += checkingTheFunction("asin", 4, 'S', string, i);
      res += checkingTheFunction("atan", 4, 'T', string, i);
      res += checkingTheFunction("sqrt", 4, 'q', string, i);
      res += checkingTheFunction("ln", 2, 'l', string, i);
      res += checkingTheFunction("log", 3, 'L', string, i);

      if (res == 9) {
        flag->error_f = 0;
      } else {
        flag->error_f = 1;
      }
    }
  }
  return flag->error_f;
}
int readSign(char* string, int i, flags* flag) {
  if (i == 0 && string[i] == '+') {
    string[i] = ' ';
  } else if (string[i] == '(') {
    int temp = 1;
    if (string[i + temp] == '+') {
      string[i + temp] = ' ';
    }
  }

  if (i == 0 && string[i] == '-') {
    string[i] = 126;
  } else if (string[i] == '(') {
    int temp = 1;
    if (string[i + temp] == '-') {
      string[i + temp] = 126;
    }
  }
  return flag->error_s;
}
int readSymbols(char* string, int i) {
  const char specSymb[] = "%%~0123456789.()eExXsctmCSTqlL */+-^";
  int counter = 0;
  int res = 0;
  for (int j = 0; specSymb[j] != 0; j++) {
    if (string[i] == specSymb[j]) {
      counter++;
      break;
    }
  }
  if (counter == 0) {
    res = 1;
  }
  return res;
}

int backspaseDelete(char* string) {
  int j = 0, n = 0;
  for (int i = 0; string[i] != 0; i++, n++) {
    if (string[i] != ' ') {
      string[i - j] = string[i];
    } else {
      j++;
    }
  }
  string[n - j] = '\0';
  return 0;
}
