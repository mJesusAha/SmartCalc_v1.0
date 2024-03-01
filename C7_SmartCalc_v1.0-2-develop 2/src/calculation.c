#include "c.h"

double calculation(str *string) {
  calc count;
  count.flag1 = 0;
  count.flag2 = 0;
  cleanArray(count.str_A, MAX);
  cleanArray(count.str_B, MAX);
  cleanArray(count.string_out, MAX);
  count.result_j = 0;
  printf("\nCтрока в обратной польск = |%s|\n", string->string_out);
  int i = 0, temp = 0;
  while (string->string_out[i] != 0 && string->errors == 0) {
    temp++;
    int s = readSimbols(string, i);
    if (s == 1) {
      workDigitS(&count, string, i);
    } else if (s == 2) {
      workBackSpace(&count);
    } else if (s == 3) {
      workBinaryFunc(&count, string, i);
      i = -1;
      cleanArrayAfterFunc(&count);
    } else if (s == 4) {
      workUnaryFunc(&count, string, i);
      i = -1;
      cleanArrayAfterFunc(&count);
    }
    i++;
  }
  double result = count.res;
  if (string->errors > 0 || result == NAN || result == 1.0 / 0.0 ||
      result == -1.0 / 0.0) {
    result = 0;
    string->errors = 1;
  }
  return result;
}

int workUnaryFunc(calc *count, str *string, int i) {
  if (count->flag2 == 0 && count->flag1 == 0) {
    string->errors = 666;
  }
  if (count->flag2 == 1) {
    rewiriteArray(count->str_A, count->str_B);
  }
  if (count->flag2 == 2) {
    for (int t = 0; count->str_A[t] != 0; t++) {
      count->string_out[strlen(count->string_out)] = count->str_A[t];
      count->string_out[strlen(count->string_out)] = 0;
    }
    count->string_out[strlen(count->string_out)] = ' ';
  }
  double b = preparingTheNum(string, count->str_B, count->result);
  ////      ////////////////////////
  double c = UnaryFunction(b, string->string_out[i]);
  string->errors = (c == NAN || c == INFINITY || c == -INFINITY)
                       ? string->errors + 1
                       : string->errors;
  //////////////////////////////////////////////////////
  convertAdressToNum(count, string, i, c);
  rewiriteArray(count->string_out, string->string_out);
  cleanArrayAfterFunc(count);  // oчищение массивов после использования знака
  return 0;
}

int workDigitS(calc *count, str *string, int i) {
  int j;
  if (count->flag1 == 0 && count->flag2 == 0) {
    count->str_A[0] = string->string_out[i];
    count->str_A[1] = 0;
    count->flag1 = 1;
  } else if (count->flag1 == 1 && count->flag2 == 0) {
    j = strlen(count->str_A);
    count->str_A[j] = string->string_out[i];
    count->str_A[j + 1] = 0;
  } else if ((count->flag1 == 0 && count->flag2 == 1)) {
    count->str_B[0] = string->string_out[i];
    count->str_B[1] = 0;
    count->flag1 = 1;
  } else if (count->flag1 == 1 && count->flag2 == 1) {
    j = strlen(count->str_B);
    count->str_B[j] = string->string_out[i];
    count->str_B[j + 1] = 0;
  } else if (count->flag1 == 0 && count->flag2 == 2) {
    for (int t = 0; count->str_A[t] != 0; t++) {
      int k = strlen(count->string_out);
      count->string_out[k] = count->str_A[t];
      if (count->str_A[t + 1] == 0) {
        count->string_out[k + 1] = ' ';
        k++;
      }
      count->string_out[k + 1] = 0;
    }
    cleanArray(count->str_A, MAX);
    for (int t = 0; count->str_B[t] != 0; t++) {
      int k = strlen(count->str_A);
      count->str_A[k] = count->str_B[t];
      count->str_A[k + 1] = 0;
    }
    cleanArray(count->str_B, MAX);
    count->str_B[0] = string->string_out[i];
    count->str_B[1] = 0;
    count->flag1 = 1;
    count->flag2 = 1;
  }
  return 0;
}
int workBackSpace(calc *count) {
  if (count->flag1 == 1 && count->flag2 == 0) {
    count->flag2 = 1;
    count->flag1 = 0;
  } else if (count->flag1 == 1 && count->flag2 == 1) {
    count->flag2 = 2;
    count->flag1 = 0;
  }
  return 0;
}

int workBinaryFunc(calc *count, str *string, int i) {
  //  char res_j[6];
  if (count->flag2 != 2) {
    string->errors = 1;
  }
  if (count->flag2 == 2) {
    double a = preparingTheNum(string, count->str_A, count->result);
    double b = preparingTheNum(string, count->str_B, count->result);
    ////      ////////////////////////
    double c = binaryFunction(a, b, string->string_out[i]);
    if (c == NAN || c == INFINITY || c == -INFINITY) {
      string->errors = 1;
    }
    //////////////////////////////////////////////////////
    convertAdressToNum(count, string, i, c);
    //  printf("|2вход выход = |%s %s|", count->string_out, string->string_out);
    rewiriteArray(count->string_out, string->string_out);
    cleanArrayAfterFunc(count /*, string*/);
    //     //oчищение массивов после использования знака
  }
  return 0;
}

void convertAdressToNum(
    calc *count, str *string, int i,
    double c) {  // переведет индекс адреса в строку и закинет
  char res_j[6];
  count->string_out[strlen(count->string_out)] = '$';
  snprintf(res_j, 4, "%d", count->result_j);
  for (int j = 0; res_j[j] != 0; j++) {
    count->string_out[strlen(count->string_out)] = res_j[j];
    count->string_out[strlen(count->string_out)] = 0;
  }
  count->result[count->result_j] = c;
  count->res = count->result[count->result_j];
  count->result_j = count->result_j + 1;
  count->string_out[strlen(count->string_out)] = ' ';
  count->string_out[strlen(count->string_out)] = 0;

  for (int t = i + 1; string->string_out[t] != 0; t++) {
    count->string_out[strlen(count->string_out)] = string->string_out[t];
    count->string_out[strlen(count->string_out)] = 0;
  }
}

double preparingTheNum(
    str *string, char *str,
    const double *result) {  // Готовит число к переводу в цифру (адрес = -1)
  // Ecли встретился адрес, то результат положителен.
  // По итогу возвращает число или по адресу или как есть
  int adress = -1;
  double a = 0;
  for (int j = 0; str[j] != 0; j++) {
    if (str[j] == 126) {
      str[j] = 45;
    }
    if (str[j] == 'x' || str[j] == 'X') {
      adress = -2;
    } else if (str[j] == 36) {
      str[j] = ' ';
      adress = atof(str);
    }
  }
  if (adress == -2) {
    a = string->X;  // обработка Х здесь
  } else if (adress == -1) {
    //  a = atof(str);
    a = myatof(str);
  } else {
    a = result[adress];
  }
  return a;
}

void rewiriteArray(const char *count, char *string) {  // из count в sfring
  cleanArray(string, MAX);
  for (int j = 0; count[j] != 0; j++) {
    string[j] = count[j];
  }
}

void cleanArrayAfterFunc(calc *count) {
  cleanArray(count->string_out, MAX);
  cleanArray(count->str_A, MAX);
  cleanArray(count->str_B, MAX);
  count->flag2 = 0;
  count->flag1 = 0;
  // oчищение массивов после использования знака
}

int readSimbols(str *string, int i) {
  int res = 0;
  if (string->string_out[i] == '$' || string->string_out[i] == 126 ||
      string->string_out[i] == 46 ||
      (string->string_out[i] == 'e' || string->string_out[i] == 'E') ||
      (string->string_out[i] >= 48 && string->string_out[i] <= 57)) {
    res = 1;  // Если прочитало цифру
  } else if (string->string_out[i] == ' ') {
    res = 2;  // Если прочитало пробел
  } else if (string->string_out[i] == '+' || string->string_out[i] == '-' ||
             string->string_out[i] == '*' || string->string_out[i] == '^' ||
             string->string_out[i] == '/' || string->string_out[i] == 'm' ||
             string->string_out[i] == '%') {
    res = 3;  // Если прочитало бинарную функцию
  } else if (funkcionUn(string, i) == 1) {
    res = 4;  // Если прочитало унарную функцию
  } else if (string->string_out[i] == 'x' || string->string_out[i] == 'X') {
    res = 1;  // Если прочитало x
  }
  return res;
}

int funkcionUn(str *string, int i) {
  char *simbols = "sctCSTqlL";
  int res = 0;
  for (int j = 0; simbols[j] != '\0'; j++) {
    if (string->string_out[i] == simbols[j]) {
      res = 1;
    }
  }
  return res;
}

void cleanArray(char *str, int max) {
  for (int i = 0; i < max; i++) {
    str[i] = 0;
  }
}

double binaryFunction(double A, double B, char znak) {  // Возвращает вычисление
  double res = 0;
  if (znak == '+')
    res = A + B;
  else if (znak == '-')
    res = A - B;
  else if (znak == '*')
    res = A * B;
  else if (znak == '/')
    res = A / B;
  else if (znak == '^')
    res = powf(A, B);
  else if (znak == 'm' || znak == '%')
    res = fmod(A, B);
  return res;
}
double UnaryFunction(double A, char znak) {  // Возвращает вычисление
  double res = 0;
  if (znak == 's')
    res = sin(A);
  else if (znak == 'c')
    res = cos(A);
  else if (znak == 't')
    res = tan(A);
  else if (znak == 'C')
    res = acos(A);
  else if (znak == 'S')
    res = asin(A);
  else if (znak == 'T')
    res = atan(A);
  else if (znak == 'q')
    res = sqrt(A);
  else if (znak == 'l')
    res = log(A);
  else if (znak == 'L')
    res = log10(A);
  return res;
}

double myatof(char *s) {
  char *ptrEnd;
  double res = strtod(s, &ptrEnd);
  return res;
}
