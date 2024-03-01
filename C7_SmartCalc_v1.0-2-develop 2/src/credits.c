#include "credits.h"

int creds(cred* calc) {
  if (calc->type == 1) {
    annuent(calc);
  }  // ежемесячный платеж фиксированный
  else {
    diff(calc);
  }  // когда процент постепенно уменьшается
  return 0;
}

double okr(double* t);
int annuent(cred* calc) {
  okr(&calc->sum);
  okr(&calc->procent);
  double m = (calc->procent / 12) / 100;
  double t = m * (pow(1 + m, calc->years)) / (pow(1 + m, calc->years) - 1);
  double s = calc->sum * t;
  s = okr(&s);
  calc->sum_pl_firsth = s;
  sprintf(calc->sum_pl_firsth_t, "%.2f", calc->sum_pl_firsth);
  calc->sum_pl_last = calc->sum_pl_firsth;
  sprintf(calc->sum_pl_last_t, "%.2f", calc->sum_pl_last);
  calc->perepl = (calc->sum_pl_firsth * calc->years) - calc->sum;
  calc->perepl = okr(&calc->perepl);
  sprintf(calc->perepl_t, "%.2f", calc->perepl);
  calc->all = calc->sum + calc->perepl;
  calc->all = okr(&calc->all);
  sprintf(calc->all_t, "%.2f", calc->all);
  return 0;
}
double okr(double* t) {
  double p = (*t * 100);
  *t = round(p) / 100;
  return *t;
}

int diff(cred* calc) {
  int t = calc->years;
  okr(&calc->sum);
  double s = calc->sum;
  okr(&calc->procent);
  double OsnDolg = calc->sum / calc->years;
  OsnDolg = okr(&OsnDolg);
  double summaD = calc->sum;
  double summa = 0;
  while (t != 0) {
    double NacProc = calc->sum * (calc->procent / (12 * 100));
    NacProc = okr(&NacProc);
    double sumUplat = OsnDolg + NacProc;
    sumUplat = okr(&sumUplat);
    if (t == calc->years) {
      calc->sum_pl_firsth = sumUplat;
    }
    if (t == 1) {
      { calc->sum_pl_last = sumUplat; }
    }
    summaD = summaD - OsnDolg;
    summa = summa + sumUplat;
    calc->sum = calc->sum - OsnDolg;

    t--;
  }
  calc->all = summa;
  calc->perepl = summa - s;
  sprintf(calc->all_t, "%.2f", calc->all);
  sprintf(calc->perepl_t, "%.2f", calc->perepl);
  sprintf(calc->sum_pl_firsth_t, "%.2f", calc->sum_pl_firsth);
  sprintf(calc->sum_pl_last_t, "%.2f", calc->sum_pl_last);

  return 0;
}
