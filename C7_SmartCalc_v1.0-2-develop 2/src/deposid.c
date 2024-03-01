#include "deposid.h"
void minus(deposid* n) {
  if (n->sum < 0) {
    n->sum = 0;
  }
  if (n->srok < 0) {
    n->srok = 0;
  }
  if (n->procent_st < 0) {
    n->procent_st = 0;
  }
  for (int i = 0; i < 10; i++) {
    if (n->sum_j[i] < 0) {
      n->sum_j[i] = 0;
    }
  }
}
int deposid_calc(deposid* n) {
  minus(n);
  if (n->sum > 0 && n->srok > 0 && n->procent_st > 0 &&
      (n->cap_proc == 0 && n->spis_pop == 0 &&
       n->spis_sn == 0 /* && n->period_pl==0*/)) {
    // если без капитализации, пополнений и снятий
    prost(n);
  } else if (n->sum > 0 && n->srok > 0 && n->procent_st > 0 &&
             n->cap_proc == 1 &&
             (n->spis_pop == 0 && n->spis_sn == 0 && n->period_pl == 0)) {
    // если с капитализацией, без пополнений и снятий
    prost_capit(n);
  } else if (n->sum > 0 && n->srok > 0 && n->procent_st > 0 &&
             n->cap_proc == 1 &&
             (n->spis_pop == 0 && n->spis_sn == 0 &&
              (n->period_pl == 3 || n->period_pl == 6 || n->period_pl == 1))) {
    // если с капитализацией, без пополнений и снятий и с ежеквартальными
    // платежами
    pay_cvartal(n);
  }
  //   if (n->itog<0) n->itog = 0;
  if (n->proc < 0) n->proc = 0;
  if (n->itog >= 0) sprintf(n->itog_t, "%.2f", n->itog);
  if (n->itog < 0) sprintf(n->itog_t, "A что, а где?");
  sprintf(n->proc_t, "%.2f", n->proc);
  if (n->proc > 75000) {
    n->sum_nalog = (n->proc - 75000) / 100 * 13;
  } else {
    n->sum_nalog = 0;
  }
  sprintf(n->sum_nalog_t, "%.2f", n->sum_nalog);

  return 0;
}
void post(double* new_summa, int j, const double* s, int t, deposid* n) {
  if (j == n->month_sum_j[t]) {
    *new_summa = *new_summa + s[t];
    n->sum = n->sum + s[t];
    n->sum_j[t] = 0;
    //   printf("\ncyмма пополнения  %f", n->sum_j[t]);
  }
}

void minPost(double* new_summa, int j, const double* s, int t, deposid* n) {
  if (j == n->month_sum_j[t]) {
    *new_summa = *new_summa - s[t];
    n->sum = n->sum - s[t];
    //    printf("\ncyмма списания  %f с месяца %d после открытия счета",
    //    n->sum_j[t],
    //           n->month_sum_j[t]);
    n->sum_j[t] = 0;
    //    printf("\ncyмма пополнения  %f", n->sum_j[t]);
  }
  if (*new_summa < 0) {
    *new_summa = 0;
  }
  if (n->sum < 0) {
    n->sum = 0;
  }
}
int prost(deposid* n) {
  double new_summa = n->sum;
  int j = 0;
  if (n->flag_month == 0) {
    n->srok = n->srok * 12;
  }
  int temp = n->srok;
  while (temp != 0) {
    double proc = 0;

    post(&new_summa, j, n->sum_j, 0, n);
    post(&new_summa, j, n->sum_j, 1, n);
    post(&new_summa, j, n->sum_j, 2, n);
    post(&new_summa, j, n->sum_j, 3, n);
    post(&new_summa, j, n->sum_j, 4, n);
    minPost(&new_summa, j, n->sum_j, 5, n);
    minPost(&new_summa, j, n->sum_j, 6, n);
    minPost(&new_summa, j, n->sum_j, 7, n);
    minPost(&new_summa, j, n->sum_j, 8, n);
    minPost(&new_summa, j, n->sum_j, 9, n);
    proc =
        (new_summa * n->procent_st * n->srok / 12 / 100) /
        n->srok;  // сумма процентов начисленная за месяц вклада без пополнений
    //   printf("\ncyмма процентов за месяц %f   |%f|", proc, new_summa);
    n->proc = n->proc + proc;
    temp--;
    j++;
  }
  new_summa = new_summa + n->sum_j[0] + n->sum_j[1] + n->sum_j[2] +
              n->sum_j[3] + n->sum_j[4];
  new_summa = okr(&new_summa);
  n->itog = new_summa;  // сумма на вкладе
  return 0;
}

int prost_capit(deposid* n) {
  // double proc = 0;
  double new_summa = n->sum;
  int j = 0;
  if (n->flag_month == 0) {
    n->srok = n->srok * 12;
  }
  int temp = n->srok;
  //  double proc = 0;
  // если выбрано в месяцах срок
  while (temp != 0) {
    double proc = 0;
    post(&new_summa, j, n->sum_j, 0, n);
    post(&new_summa, j, n->sum_j, 1, n);
    post(&new_summa, j, n->sum_j, 2, n);
    post(&new_summa, j, n->sum_j, 3, n);
    post(&new_summa, j, n->sum_j, 4, n);
    minPost(&new_summa, j, n->sum_j, 5, n);
    minPost(&new_summa, j, n->sum_j, 6, n);
    minPost(&new_summa, j, n->sum_j, 7, n);
    minPost(&new_summa, j, n->sum_j, 8, n);
    minPost(&new_summa, j, n->sum_j, 9, n);
    proc =
        (new_summa * n->procent_st * n->srok / 12 / 100) /
        n->srok;  // сумма процентов начисленная за месяц вклада без пополнений
    //    printf("\ncyмма процентов за месяц %f", proc);
    new_summa = new_summa + proc;
    temp--;
    j++;
  }
  new_summa = new_summa + n->sum_j[1] + n->sum_j[2] + n->sum_j[3] +
              n->sum_j[4] + n->sum_j[0];
  new_summa = okr(&new_summa);
  n->itog = new_summa;  // сумма на вкладе
  n->proc = n->itog - n->sum;
  return 0;
}
int pay_cvartal(deposid* n) {
  // double proc = 0;
  double new_summa = n->sum;
  int temp2 = 1;
  if (n->flag_month == 0) {
    n->srok = n->srok * 12;
  }
  int temp = n->srok;
  double proc_cvartal = 0;
  int j = 0;
  // если выбрано в месяцах срок
  while (temp != 0) {
    double proc = 0;
    post(&new_summa, j, n->sum_j, 0, n);
    post(&new_summa, j, n->sum_j, 1, n);
    post(&new_summa, j, n->sum_j, 2, n);
    post(&new_summa, j, n->sum_j, 3, n);
    post(&new_summa, j, n->sum_j, 4, n);
    minPost(&new_summa, j, n->sum_j, 5, n);
    minPost(&new_summa, j, n->sum_j, 6, n);
    minPost(&new_summa, j, n->sum_j, 7, n);
    minPost(&new_summa, j, n->sum_j, 8, n);
    minPost(&new_summa, j, n->sum_j, 9, n);
    proc =
        (new_summa * n->procent_st * n->srok / 12 / 100) /
        n->srok;  // сумма процентов начисленная за месяц вклада без пополнений
    if (temp2 < 4 && n->period_pl == 3) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 4 && n->period_pl == 3) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //     printf("\ncyмма процентов eжеквартально %f", proc_cvartal);
      proc_cvartal = 0;
    }
    if (temp2 < 7 && n->period_pl == 6) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 7 && n->period_pl == 6) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //   printf("\ncyмма процентов пол года %f", proc_cvartal);
      proc_cvartal = 0;
    }
    if (temp2 < 13 && n->period_pl == 1) {
      proc_cvartal = proc_cvartal + proc;
      temp2++;
    }
    if (temp2 == 13 && n->period_pl == 1) {
      new_summa = new_summa + proc_cvartal;
      temp2 = 1;
      //     printf("\ncyмма процентов за год. %f", proc_cvartal);
      proc_cvartal = 0;
    }
    j++;
    temp--;
  }
  new_summa = new_summa + proc_cvartal + n->sum_j[0] + n->sum_j[1] +
              n->sum_j[2] + n->sum_j[3] + n->sum_j[4];
  new_summa = okr(&new_summa);
  n->itog = new_summa;  // сумма на вкладе
  n->proc = n->itog - n->sum;
  return 0;
}
