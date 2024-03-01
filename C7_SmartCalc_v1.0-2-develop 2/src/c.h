#ifndef C_H
#define C_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 500

typedef struct {
  char string_out[MAX];
  char stek[MAX];
  int flagNum;
  double X;  // x от пользователя
  int errors;
} str;

typedef struct {
  int error_s;
  int error_f;
  int counter1;
  int counter2;
} flags;

typedef struct {
  int flag1;
  int flag2;
  char str_A[MAX];
  char str_B[MAX];
  double result[250];
  double res;
  char string_out[MAX];
  int result_j;
} calc;

int readSign(char* string, int i, flags* flag);
int stringProcessing(char* string);
int readFunc(char* string, int i, flags* flag);
int readSymbols(char* string, int i);
int checkingBrackets(const char* string, int i, flags* flag);
int readSignPlus(char* string, int i);
int checkingDoubleSign(const char* string, int i);
int backspaseDelete(char* string);
int readSignMultDev(const char* string, int i);
int checkingTheFunction(const char* func, int n, char simbol, char* string,
                        int i);

//////////////////////////////////
int s21_result(const char* string, char* re, double X);
void cleanMass(str* mas, int max);  // Очищает массив
int s21_calc(char* string, double x, double* result);
int sortingStations(char* string, double X);
int transferringNumberToString(str* text, const char* string, int i);
int transferringsimbolToSteck(str* text, const char* string, int i);
int transferringSimbolToStrOut(str* text);
int forBracket(str* text, const char* string, int i);
int functionPriority(char* string, int i);
int checkNat(char* str);

///////////calc//////////////////////
double calculation(str* string);
double myatof(char* s);
void cleanArray(char* str, int max);  // Очищает массив
int readSimbols(str* string, int i);  // Что за символ пришел
int funkcionUn(str* string, int i);
void cleanArrayAfterFunc(calc* count);
void rewiriteArray(const char* count, char* string);
double preparingTheNum(str* string, char* str, const double* result);
int workDigitS(calc* count, str* string, int i);
int workUnaryFunc(calc* count, str* string, int i);
int workBackSpace(calc* count);
int workBinaryFunc(calc* count, str* string, int i);
int WorDigitD(calc* count, str* string, int i);
int WorDigitX(calc* count, str* string, int i);
void convertAdressToNum(calc* count, str* string, int i, double c);
double binaryFunction(double A, double B, char znak);
double UnaryFunction(double A, char znak);

#endif  // C_H