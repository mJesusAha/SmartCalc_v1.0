#ifndef DEPOSID_H
#define DEPOSID_H
#include <stdio.h>

#include "credits.h"
typedef struct {
  double sum;         // сумма вклада +
  double srok;        // срок размещения+
  double procent_st;  // процентная ставка+
  double nalog_st;    // налоговая ставка+
  double period_pl;  // периодичность выплат+ (3-eжеквартально 0-ежемесячно 6 -
                     // пол года 1 - год)
  double cap_proc;   // капитализация процентов+
  double spis_pop;   // список пополнений+
  double spis_sn;    // список частичных снятий+
  double proc;       // начисленные проценты-
  double sum_nalog;  // сумма налога-
  double itog;       // сумма на вкладе к концу срока
  int flag_month;    // выбрано в месяцах
  int day_o;         // день открытия
  int month_o;       // месяц открытия
  int years_o;       // год открытия
  char sum_nalog_t[100];
  char itog_t[100];
  char proc_t[100];
  double sum_j[10];  // сумма для поступления
  int month_sum_j[10];  // месяц когда поступит от начала периода

} deposid;
int deposid_calc(deposid* n);
int prost_capit(deposid* n);
int prost(deposid* n);
int pay_cvartal(deposid* n);
void minus(deposid* n);

#endif  // DEPOSID_H
