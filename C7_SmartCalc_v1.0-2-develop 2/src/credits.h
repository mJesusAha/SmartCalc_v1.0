#ifndef CREDITS_H
#define CREDITS_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// - Вход: общая сумма кредита, срок, процентная ставка, тип (аннуитетный,
// дифференцированный)
//- Выход: ежемесячный платеж, переплата по кредиту, общая выплата
typedef struct {
  double sum;            // общая сумма кредита
  int years;             // срок
  double procent;        // процентная ставка
  bool type;             // тип платежа
  double sum_pl_firsth;  // cумма платежа
  double sum_pl_last;
  double perepl;  // переплата по кредиту
  double all;     // общая выплата
  char all_t[100];
  char perepl_t[100];
  char sum_pl_firsth_t[100];
  char sum_pl_last_t[100];
} cred;

int diff(cred* calc);
int credits(cred* calc);
int creds(cred* calc);
int annuent(cred* calc);
double okr(double* t);
#endif  // CREDITS_H
