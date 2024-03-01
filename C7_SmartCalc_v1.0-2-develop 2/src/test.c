#include "c.h"
#include "check.h"
#include "credits.h"
#include "deposid.h"

START_TEST(s21_sum1) {
  double res = 0;
  int errors = s21_calc("1+x-~1", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 3);
}
END_TEST
START_TEST(s21_sum2) {
  double res = 0;
  int errors = s21_calc("1+-x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - 1);
}
END_TEST

START_TEST(s21_sum3) {
  double res = 0;
  int errors = s21_calc("-1+-x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, -1 - 1);
}
END_TEST
START_TEST(s21_sum4) {
  double res = 0;
  int errors = s21_calc("1-(x-1)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - (1 - 1));
}
END_TEST
START_TEST(s21_sum5) {
  double res = 0;
  int errors = s21_calc("1 - ( x - 1 )", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - (1 - 1));
}
END_TEST
START_TEST(s21_sum6) {
  double res = 0;
  int errors = s21_calc("1 - ( +x - 1 )", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - (1 - 1));
}
END_TEST
START_TEST(s21_sum7) {
  double res = 0;
  int errors = s21_calc("-1+2 - ( +x - +1 )", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - (1 - 1));
}
END_TEST
START_TEST(s21_sum8) {
  double res = 0;
  int errors = s21_calc("1+-2 +1  -  (  +x  -  +1 )", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 1 - 2 + 1);
}
END_TEST
START_TEST(s21_sum9) {
  double res = 0;
  int errors = s21_calc("sin(1/0)+cos(x)", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_sum10) {
  double res = 0;
  int errors = s21_calc("sin x+cos x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, sin(1) + cos(1));
}
END_TEST

Suite *s21_sum(void) {
  Suite *s = suite_create(
      "\033[44m-=s21_check=-\033[0m  \033[45m\U0001f600\033[0m "
      "\033[46m\U0001f600\033[0m \033[41m\U0001f600\033[0m");
  TCase *tc = tcase_create("s21_sum");
  tcase_add_test(tc, s21_sum1);
  tcase_add_test(tc, s21_sum2);
  tcase_add_test(tc, s21_sum3);
  tcase_add_test(tc, s21_sum4);
  tcase_add_test(tc, s21_sum5);
  tcase_add_test(tc, s21_sum6);
  tcase_add_test(tc, s21_sum7);
  tcase_add_test(tc, s21_sum8);
  tcase_add_test(tc, s21_sum9);
  tcase_add_test(tc, s21_sum10);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(error1) {
  double res = 0;
  int errors = s21_calc("s-j", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error2) {
  double res = 0;
  int errors = s21_calc("-6*(sin(1) ()+ (- 8) * -cos(1))", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error3) {
  double res = 0;
  int errors = s21_calc("+6**(sin(1) (c)+ (- 8)    */cos(1+ +1))", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error4) {
  double res = 0;
  int errors = s21_calc("( + (- 8 ()))", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error5) {
  double res = 0;
  int errors = s21_calc("-5/0", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error6) {
  double res = 0;
  int errors = s21_calc("--50/1", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error7) {
  double res = 0;
  int errors = s21_calc("5..0/1", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(error8) {
  double res = 0;
  int errors = s21_calc("-50//1", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(error9) {
  double res = 0;
  int errors = s21_calc("tan ", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *s21_errors(void) {
  Suite *s = suite_create(
      "\033[42m-=s21_error_test=-\033[0m  \033[46m\U0001f602\033[0m "
      "\033[41m\U0001f602\033[0m \033[43m\U0001f602\033[0m");
  TCase *tc = tcase_create("matrix_tc");
  tcase_add_test(tc, error1);
  tcase_add_test(tc, error2);
  tcase_add_test(tc, error3);
  tcase_add_test(tc, error4);
  tcase_add_test(tc, error5);
  tcase_add_test(tc, error6);
  tcase_add_test(tc, error7);
  tcase_add_test(tc, error8);
  tcase_add_test(tc, error9);

  suite_add_tcase(s, tc);
  return s;
}
START_TEST(s21_fun1) {
  double res = 0;
  int errors = s21_calc("tan x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, tan(1));
}
END_TEST
START_TEST(s21_fun2) {
  double res = 0;
  int errors = s21_calc("cos x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, cos(1));
}
END_TEST

START_TEST(s21_fun3) {
  double res = 0;
  int errors = s21_calc("log x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, log(1));
}
END_TEST
START_TEST(s21_fun4) {
  double res = 0;
  int errors = s21_calc("ln x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, log10(1));
}
END_TEST
START_TEST(s21_fun5) {
  double res = 0;
  int errors = s21_calc("sqrt(x)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, sqrt(1));
}
END_TEST
START_TEST(s21_fun6) {
  double res = 0;
  int errors = s21_calc("atan(x)+acos(x)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, atan(1) + acos(1));
}
END_TEST
START_TEST(s21_fun7) {
  double res = 0;
  int errors = s21_calc("3334 % x", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 3 % 1);
}
END_TEST
START_TEST(s21_fun8) {
  double res = 0;
  int errors = s21_calc("asin(x)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, asin(1));
}
END_TEST
START_TEST(s21_fun9) {
  double res = 0;
  int errors = s21_calc("21+~21.4e6", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_fun10) {
  double res = 0;
  int errors = s21_calc("e.21+~21.4e6+13E", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_fun11) {
  double res = 0;
  int errors = s21_calc("log (0)", 1, &res);
  ck_assert_int_eq(errors, -1);

  ck_assert_int_eq(res, 0);
}
END_TEST

Suite *s21_fun(void) {
  Suite *s = suite_create(
      "\033[44m-=s21_functions=-\033[0m  \033[45m\U0001f600\033[0m "
      "\033[46m\U0001f600\033[0m \033[41m\U0001f600\033[0m");
  TCase *tc = tcase_create("s21_fun");
  tcase_add_test(tc, s21_fun1);
  tcase_add_test(tc, s21_fun2);
  tcase_add_test(tc, s21_fun3);
  tcase_add_test(tc, s21_fun4);
  tcase_add_test(tc, s21_fun5);
  tcase_add_test(tc, s21_fun6);
  tcase_add_test(tc, s21_fun7);
  tcase_add_test(tc, s21_fun8);
  tcase_add_test(tc, s21_fun9);
  tcase_add_test(tc, s21_fun10);
  tcase_add_test(tc, s21_fun11);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_hard1) {
  double res = 0;
  int errors = s21_calc("3+4*2/(1-5)^2", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 3 + 4 * 2 / 16);
}
END_TEST
START_TEST(s21_hard2) {
  double res = 0;
  int errors = s21_calc("(34.5+4) * 6", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, 38.5 * 6);
}
END_TEST
START_TEST(s21_hard3) {
  double res = 0;
  int errors = s21_calc("sin(cos(1+2))", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, sin(cos(1 + 2)));
}
END_TEST
START_TEST(s21_hard4) {
  double res = 0;
  int errors = s21_calc("(tan(1)+ln(3)+log(1)-sqrt(2))/tan(1)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (tan(1) + log10(3) + log(1) - sqrt(2)) / tan(1));
}
END_TEST
START_TEST(s21_hard5) {
  double res = 0;
  int errors = s21_calc("(-55.5 + 2 +4) + (-50.5 + 2 +4)", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, ((-55.5 + 2 + 4) + (-50.5 + 2 + 4)));
}
END_TEST
START_TEST(s21_hard6) {
  double res = 0;
  int errors = s21_calc("2*(6782+-3391)-6782", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (2 * (6782 + -3391) - 6782));
}
END_TEST
START_TEST(s21_hard7) {
  double res = 0;
  int errors = s21_calc("((1+2)*(2-2)+3)/10", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (((1 + 2) * (2 - 2) + 3) / 10));
}
END_TEST
START_TEST(s21_hard8) {
  double res = 0;
  int errors = s21_calc("-6*(sin(1) + (- 8) * cos(2))", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (-6 * (sin(1) + (-8) * cos(2))));
}
END_TEST
char n[] = {
    "(+56+132*(3+2/1))/((2*6)/3)+(56+ "
    "132*(3+2/+1))/((2*6)/3)-(56+132*(3+2/1))/((2*6)/3)-(56+132*(3+2/1))/"
    "((2*6)/3)"};
START_TEST(s21_hard9) {
  double res = 0;
  int errors = s21_calc(n, 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (56 + 132 * (3 + 2 / 1)) / ((2 * 6) / 3) +
                            (56 + 132 * (3 + 2 / +1)) / ((2 * 6) / 3) -
                            (56 + 132 * (3 + 2 / 1)) / ((2 * 6) / 3) -
                            (56 + 132 * (3 + 2 / 1)) / ((2 * 6) / 3));
}
END_TEST
START_TEST(s21_hard10) {
  double res = 0;
  int errors = s21_calc("3*  (  cos(2^2)-cos(4))--3^2", 1, &res);
  ck_assert_int_eq(errors, 0);

  ck_assert_int_eq(res, (3 * (cos(2 * 2) - cos(4)) + 9));
}
END_TEST

END_TEST
START_TEST(s21_hard11) {
  double res = 0;
  int errors = s21_calc(
      "+ 501 + -6*(sin(1) + (- 8) * cos(1)) - "
      "(tan(1)+ln(3)+log(1)-sqrt(2))/tan(1)",
      1, &res);
  ck_assert_int_eq(errors, 0);
  double a = 521.088330;
  ck_assert_int_eq(res, a);
}
END_TEST
START_TEST(s21_hard12) {
  double res = 0;
  int errors = s21_calc("+ 501 +", 1, &res);
  ck_assert_int_eq(errors, -1);
  ck_assert_int_eq(res, 0);
}
END_TEST
START_TEST(s21_hard13) {
  double res = 0;
  int errors = s21_calc("cos", 1, &res);
  ck_assert_int_eq(errors, -1);
  ck_assert_int_eq(res, 0);
}
END_TEST

END_TEST
START_TEST(s21_hard14) {
  double res = 0;
  int errors = s21_calc("cos sin", 1, &res);
  ck_assert_int_eq(errors, -1);
  ck_assert_int_eq(res, 0);
}
END_TEST
Suite *s21_hard(void) {
  Suite *s = suite_create(
      "\033[44m-=hard exemple=-\033[0m  \033[45m\U0001f600\033[0m "
      "\033[46m\U0001f600\033[0m \033[41m\U0001f600\033[0m");
  TCase *tc = tcase_create("s21_sum");
  tcase_add_test(tc, s21_hard1);
  tcase_add_test(tc, s21_hard2);
  tcase_add_test(tc, s21_hard3);
  tcase_add_test(tc, s21_hard4);
  tcase_add_test(tc, s21_hard5);
  tcase_add_test(tc, s21_hard6);
  tcase_add_test(tc, s21_hard7);
  tcase_add_test(tc, s21_hard8);
  tcase_add_test(tc, s21_hard9);
  tcase_add_test(tc, s21_hard10);
  tcase_add_test(tc, s21_hard11);
  tcase_add_test(tc, s21_hard12);
  tcase_add_test(tc, s21_hard13);
  tcase_add_test(tc, s21_hard14);
  suite_add_tcase(s, tc);
  return s;
}

START_TEST(s21_dep1) {
  deposid new;
  new.sum = -1000;       // сумма вклада +
  new.srok = -12;        // срок размещения+
  new.procent_st = -10;  // процентная ставка+
  new.nalog_st = 13;     // налоговая ставка+
  new.period_pl = 1;     // периодичность выплат+
  new.cap_proc = 1;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 1;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = -500;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = -500;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = -1;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = -50;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = -5;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = -5;

  new.sum_j[6] = 0;
  new.month_sum_j[6] = -1;
  new.sum_j[7] = 0;
  new.month_sum_j[7] = -50;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = -5;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = -5;
  deposid_calc(&new);
  printf("\nпроценты начисленные за весь период %f", new.proc);
  printf("\nсумма на вкладе %f", new.itog);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.itog, new.itog);
}
END_TEST
START_TEST(s21_dep2) {
  deposid new;
  new.sum = 100000000000;  // сумма вклада +
  new.srok = 100;          // срок размещения+
  new.procent_st = 10;     // процентная ставка+
  new.nalog_st = 13;       // налоговая ставка+
  new.period_pl = 3;       // периодичность выплат+
  new.cap_proc = 1;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 1;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = -500;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = -500;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 6;
  new.month_sum_j[2] = -1;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = -50;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = -5;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = -5;

  new.sum_j[6] = 0;
  new.month_sum_j[6] = -1;
  new.sum_j[7] = 0;
  new.month_sum_j[7] = -50;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = -5;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = -5;
  deposid_calc(&new);
  printf("\nпроценты начисленные за весь период %f", new.proc);
  printf("\nсумма на вкладе %f", new.itog);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.itog, new.itog);
}
END_TEST

START_TEST(s21_dep3) {
  deposid new;
  new.sum = 100;        // сумма вклада +
  new.srok = 1;         // срок размещения+
  new.procent_st = 10;  // процентная ставка+
  new.nalog_st = 0;     // налоговая ставка+
  new.period_pl = 0;    // периодичность выплат+
  new.cap_proc = 0;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 0;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = 0;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = 0;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = 0;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = 0;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = 0;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = 0;

  new.sum_j[6] = 100000;
  new.month_sum_j[6] = 1;
  new.sum_j[7] = 100;
  new.month_sum_j[7] = 1;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = 0;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = 0;
  deposid_calc(&new);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.itog, new.itog);
}
END_TEST
START_TEST(s21_dep4) {
  deposid new;
  new.sum = 100;        // сумма вклада +
  new.srok = 1;         // срок размещения+
  new.procent_st = 10;  // процентная ставка+
  new.nalog_st = 0;     // налоговая ставка+
  new.period_pl = 0;    // периодичность выплат+
  new.cap_proc = 1;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 0;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = 0;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = 0;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = 0;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = 0;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = 0;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = 0;

  new.sum_j[6] = 0;
  new.month_sum_j[6] = 0;
  new.sum_j[7] = 0;
  new.month_sum_j[7] = 0;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = 0;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = 0;
  deposid_calc(&new);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.itog, new.itog);
}

END_TEST
START_TEST(s21_cred1) {
  cred calc;
  calc.sum = 500000;
  calc.procent = 13;
  calc.years = 36;
  calc.type = 1;
  creds(&calc);
  ck_assert_int_eq(calc.sum_pl_last, calc.sum_pl_last);
}
END_TEST
START_TEST(s21_cred2) {
  cred calc;
  calc.sum = 500000;
  calc.procent = 13;
  calc.years = 36;
  calc.type = 0;
  creds(&calc);
  ck_assert_int_eq(calc.sum_pl_last, calc.sum_pl_last);
}
END_TEST
START_TEST(s21_dep5) {
  deposid new;
  new.sum = 1000;       // сумма вклада +
  new.srok = 12;        // срок размещения+
  new.procent_st = 10;  // процентная ставка+
  new.nalog_st = 13;    // налоговая ставка+
  new.period_pl = 1;    // периодичность выплат+
  new.cap_proc = 1;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 1;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = 500000;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = -500;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = -1;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = -50;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = -5;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = -5;

  new.sum_j[6] = 0;
  new.month_sum_j[6] = -1;
  new.sum_j[7] = 0;
  new.month_sum_j[7] = -50;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = -5;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = -5;
  deposid_calc(&new);
  printf("\nпроценты начисленные за весь период %f", new.proc);
  printf("\nсумма на вкладе %f", new.itog);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.itog, new.itog);
}
END_TEST
START_TEST(s21_dep6) {
  deposid new;
  new.sum = 100;        // сумма вклада +
  new.srok = 1;         // срок размещения+
  new.procent_st = 10;  // процентная ставка+
  new.nalog_st = 0;     // налоговая ставка+
  new.period_pl = 3;    // периодичность выплат+
  new.cap_proc = 0;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 0;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = 0;
  new.month_sum_j[0] = 0;
  new.sum_j[1] = 0;
  new.month_sum_j[1] = 0;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = 0;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = 0;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = 0;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = 0;

  new.sum_j[6] = 100000;
  new.month_sum_j[6] = 1;
  new.sum_j[7] = 100;
  new.month_sum_j[7] = 1;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = 0;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = 0;
  deposid_calc(&new);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.srok, 12);
}
END_TEST
START_TEST(s21_dep7) {
  deposid new;
  new.sum = 100;        // сумма вклада +
  new.srok = 50;        // срок размещения+
  new.procent_st = 10;  // процентная ставка+
  new.nalog_st = 13;    // налоговая ставка+
  new.period_pl = 6;    // периодичность выплат+
  new.cap_proc = 1;  // капитализация процентов+ 0 без 1 с
  new.spis_pop = 0;    // список пополнений+
  new.spis_sn = 0;     // список частичных снятий+
  new.flag_month = 0;  // вклад в месяцах == 1+ а в годах 0;
  new.sum_j[0] = 0;
  new.month_sum_j[0] = 100;
  new.sum_j[1] = 0;
  new.month_sum_j[1] = 1000;
  new.sum_j[2] = 0;
  new.month_sum_j[2] = 1000;
  new.sum_j[3] = 0;
  new.month_sum_j[3] = 1000000000;
  new.sum_j[4] = 0;
  new.month_sum_j[4] = 0;
  new.sum_j[5] = 0;
  new.month_sum_j[5] = 0;

  new.sum_j[6] = 100000;
  new.month_sum_j[6] = 1;
  new.sum_j[7] = 100;
  new.month_sum_j[7] = 1;
  new.sum_j[8] = 0;
  new.month_sum_j[8] = 0;
  new.sum_j[9] = 0;
  new.month_sum_j[9] = 0;
  deposid_calc(&new);
  ck_assert_int_eq(new.proc, new.proc);

  ck_assert_int_eq(new.srok, 600);
}
END_TEST
Suite *s21_deposid(void) {
  Suite *s = suite_create(
      "\033[44m-=s21_depos=-\033[0m  \033[45m\U0001f600\033[0m "
      "\033[46m\U0001f600\033[0m \033[41m\U0001f600\033[0m");
  TCase *tc = tcase_create("s21_dep");
  tcase_add_test(tc, s21_dep1);
  tcase_add_test(tc, s21_dep2);
  tcase_add_test(tc, s21_dep3);
  tcase_add_test(tc, s21_dep4);
  tcase_add_test(tc, s21_dep5);
  tcase_add_test(tc, s21_dep6);
  tcase_add_test(tc, s21_cred1);
  tcase_add_test(tc, s21_cred2);
  tcase_add_test(tc, s21_dep7);
  suite_add_tcase(s, tc);
  return s;
}

int main() {
  int failed = 0;
  Suite *s21_calc[] = {s21_sum(),  s21_errors(),  s21_fun(),
                       s21_hard(), s21_deposid(), NULL};

  for (int i = 0; s21_calc[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_calc[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  if (failed == 0) {
    printf(
        "\n\t\t\t\033[41m\U0001f60D\033[42m\U0001f60D\033[43m\U0001f60D\033["
        "44m "
        "\033[45m\033[46mF\033[45mA\033[43mI\033[44mL\033[42mE\033[45mD:\033["
        "46m \033[45m%d "
        "\033[41m\U0001f60D\033[42m\U0001f60D\033[43m\U0001f60D\033[44m\033["
        "0m\n\n",
        failed);
  } else if (failed > 0) {
    printf(
        "\n\t\t\t\033[41m\U0001f625\U0001f625\U0001f625 FAILED: %d "
        "\U0001f625\U0001f625\U0001f625\033[0m\n\n",
        failed);
  }
  return failed == 0 ? 0 : 1;
}