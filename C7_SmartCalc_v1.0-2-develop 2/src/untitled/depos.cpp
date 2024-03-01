#include "depos.h"

#include <QDateTimeEdit>

#include "ui_depos.h"
depos::depos(QWidget *parent) : QWidget(parent), ui(new Ui::depos) {
  ui->setupUi(this);
  QDate date = QDate::currentDate();
  QDate date1 = date, date2 = date, date3 = date, date4 = date, date5 = date;
  QDate date6 = date, date7 = date, date8 = date, date9 = date, date10 = date;
  ui->dateEdit->setDate(date);
  ui->dateEdit_2->setDate(date1);
  ui->dateEdit_3->setDate(date2);
  ui->dateEdit_4->setDate(date3);
  ui->dateEdit_5->setDate(date4);
  ui->dateEdit_6->setDate(date5);

  ui->dateEdit_7->setDate(date6);
  ui->dateEdit_8->setDate(date7);
  ui->dateEdit_9->setDate(date8);
  ui->dateEdit_10->setDate(date9);
  ui->dateEdit_11->setDate(date10);
  N.day_o = date.day();
  N.years_o = date.year();
  N.month_o = date.month();
  printf("DATE %d %d %d", N.day_o, N.month_o, N.years_o);
  ui->radioButton->setChecked(true);
}

depos::~depos() { delete ui; }
void depos::popDep() {
  QString date_1 = ui->lineEdit_4->text(), date_2 = ui->lineEdit_5->text(),
          date_3 = ui->lineEdit_6->text(), date_4 = ui->lineEdit_7->text(),
          date_5 = ui->lineEdit_8->text();
  QByteArray d1 = date_1.toLocal8Bit(), d2 = date_2.toLocal8Bit(),
             d3 = date_3.toLocal8Bit(), d4 = date_4.toLocal8Bit(),
             d5 = date_5.toLocal8Bit();
  char *date_d_1 = d1.data(), *date_d_2 = d2.data(), *date_d_3 = d3.data(),
       *date_d_4 = d4.data(), *date_d_5 = d5.data();
  N.sum_j[0] = atof(date_d_1);
  N.sum_j[1] = atof(date_d_2);
  N.sum_j[2] = atof(date_d_3);
  N.sum_j[3] = atof(date_d_4);
  N.sum_j[4] = atof(date_d_5);
  //    if (date_1.isEmpty() || N.sum_j[0] == 0.0) {
  //        ui->lineEdit_4->setText("0");}
  //    else {ui->lineEdit_4->setText(d1.data());}
  (date_1.isEmpty() || N.sum_j[0] == 0.0) ? ui->lineEdit_4->setText("0")
                                          : ui->lineEdit_4->setText(d1.data());
  (date_2.isEmpty() || N.sum_j[1] == 0.0) ? ui->lineEdit_5->setText("0")
                                          : ui->lineEdit_5->setText(d2.data());
  (date_3.isEmpty() || N.sum_j[2] == 0.0) ? ui->lineEdit_6->setText("0")
                                          : ui->lineEdit_6->setText(d3.data());
  (date_4.isEmpty() || N.sum_j[3] == 0.0) ? ui->lineEdit_7->setText("0")
                                          : ui->lineEdit_7->setText(d4.data());
  (date_5.isEmpty() || N.sum_j[4] == 0.0) ? ui->lineEdit_8->setText("0")
                                          : ui->lineEdit_8->setText(d5.data());
}
void depos::minusDep() {
  QString date_6 = ui->lineEdit_9->text(), date_7 = ui->lineEdit_10->text(),
          date_8 = ui->lineEdit_11->text(), date_9 = ui->lineEdit_12->text(),
          date_10 = ui->lineEdit_13->text();
  QByteArray d6 = date_6.toLocal8Bit(), d7 = date_7.toLocal8Bit(),
             d8 = date_8.toLocal8Bit(), d9 = date_9.toLocal8Bit(),
             d10 = date_10.toLocal8Bit();
  char *date_d_6 = d6.data(), *date_d_7 = d7.data(), *date_d_8 = d8.data(),
       *date_d_9 = d9.data(), *date_d_10 = d10.data();
  N.sum_j[5] = atof(date_d_6);
  N.sum_j[6] = atof(date_d_7);
  N.sum_j[7] = atof(date_d_8);
  N.sum_j[8] = atof(date_d_9);
  N.sum_j[9] = atof(date_d_10);
  //    if (date_1.isEmpty() || N.sum_j[0] == 0.0) {
  //        ui->lineEdit_4->setText("0");}
  //    else {ui->lineEdit_4->setText(d1.data());}
  (date_6.isEmpty() || N.sum_j[5] == 0.0) ? ui->lineEdit_9->setText("0")
                                          : ui->lineEdit_9->setText(d6.data());
  (date_7.isEmpty() || N.sum_j[6] == 0.0) ? ui->lineEdit_10->setText("0")
                                          : ui->lineEdit_10->setText(d7.data());
  (date_8.isEmpty() || N.sum_j[7] == 0.0) ? ui->lineEdit_11->setText("0")
                                          : ui->lineEdit_11->setText(d8.data());
  (date_9.isEmpty() || N.sum_j[8] == 0.0) ? ui->lineEdit_12->setText("0")
                                          : ui->lineEdit_12->setText(d9.data());
  (date_10.isEmpty() || N.sum_j[9] == 0.0)
      ? ui->lineEdit_13->setText("0")
      : ui->lineEdit_13->setText(d10.data());
}
void depos::on_pushButton_clicked() {
  QString sum_in = ui->lineEdit->text(), procents = ui->lineEdit_3->text(),
          month = ui->lineEdit_2->text();
  QByteArray s = sum_in.toLocal8Bit(), p = procents.toLocal8Bit(),
             m = month.toLocal8Bit();
  char *summ_in = s.data(), *proc = p.data(), *month_in = m.data();
  N.sum = atof(summ_in);
  if (ui->radioButton->isChecked()) {
    N.cap_proc = 1;
  } else {
    N.cap_proc = 0;
  }
  if (sum_in.isEmpty() || N.sum == 0.0) {
    ui->lineEdit->setText("0");
  } else {
    ui->lineEdit->setText(s.data());
  }

  N.procent_st = atof(proc);
  if (procents.isEmpty() || N.procent_st == 0.0) {
    ui->lineEdit_3->setText("0");
  } else {
    ui->lineEdit_3->setText(p.data());
  }

  N.srok = atof(month_in);
  if (month.isEmpty() || N.srok == 0.0) {
    ui->lineEdit_2->setText("0");
  } else {
    ui->lineEdit_2->setText(m.data());
  }

  popDep();
  minusDep();
  //    QString date_1 = ui->lineEdit_4->text(), date_2 =
  //    ui->lineEdit_5->text(), date_3 = ui->lineEdit_6->text(), date_4 =
  //    ui->lineEdit_7->text(), date_5 = ui->lineEdit_8->text(); QByteArray d1 =
  //    date_1.toLocal8Bit(), d2 = date_2.toLocal8Bit(), d3 =
  //    date_3.toLocal8Bit(), d4 = date_4.toLocal8Bit(), d5 =
  //    date_5.toLocal8Bit(); char *date_d_1 = d1.data(), *date_d_2 = d2.data(),
  //    *date_d_3 = d3.data(), *date_d_4 = d4.data(), *date_d_5 = d5.data();
  //    N.sum_j[0] = atof(date_d_1);
  //    N.sum_j[1] = atof(date_d_2);
  //    N.sum_j[2] = atof(date_d_3);
  //    N.sum_j[3] = atof(date_d_4);
  //    N.sum_j[4] = atof(date_d_5);
  ////    if (date_1.isEmpty() || N.sum_j[0] == 0.0) {
  ////        ui->lineEdit_4->setText("0");}
  ////    else {ui->lineEdit_4->setText(d1.data());}
  //    (date_1.isEmpty() || N.sum_j[0] == 0.0)?
  //    ui->lineEdit_4->setText("0"):ui->lineEdit_4->setText(d1.data());
  //     (date_2.isEmpty() || N.sum_j[1] == 0.0)?
  //     ui->lineEdit_5->setText("0"):ui->lineEdit_5->setText(d2.data());
  //     (date_3.isEmpty() || N.sum_j[2] == 0.0)?
  //     ui->lineEdit_6->setText("0"):ui->lineEdit_6->setText(d3.data());
  //      (date_4.isEmpty() || N.sum_j[3] == 0.0)?
  //      ui->lineEdit_7->setText("0"):ui->lineEdit_7->setText(d4.data());
  //       (date_5.isEmpty() || N.sum_j[4] == 0.0)?
  //       ui->lineEdit_8->setText("0"):ui->lineEdit_8->setText(d5.data());
  //    //   (date_6.isEmpty() || N.sum_j[5] == 0.0)?
  //    ui->lineEdit_9->setText("0"):ui->lineEdit_9->setText(d6.data());

  deposid_calc(&N);
  ui->label_13->setText(N.itog_t);
  ui->label_14->setText(N.proc_t);
  ui->label_15->setText(N.sum_nalog_t);

  //     ui->label_16->setText("cap "+N.cap_proc+ "srock " + N.srok + "years");
  printf("капитализация =%f, срок = %f, флаг месяц %d", N.cap_proc, N.srok,
         N.flag_month);
  printf("DATE_2= месяц начисления = %d с суммой %f", N.month_sum_j[0],
         N.sum_j[0]);
  N.proc = 0;
  N.itog = 0;
  N.sum_nalog = 0;
}

void depos::on_comboBox_activated(int index) {
  if (index == 1) {
    N.flag_month = 1;
  }
  if (index == 0) {
    N.flag_month = 0;
  }
}

void depos::on_comboBox_2_activated(int index) {
  if (index == 0) {
    N.period_pl = 0;
  } else if (index == 1) {
    N.period_pl = 3;
  } else if (index == 2) {
    N.period_pl = 6;
  } else if (index == 3) {
    N.period_pl = 1;
  }
}

void depos::on_dateEdit_dateChanged(const QDate &date) {
  N.day_o = date.day();
  N.years_o = date.year();
  N.month_o = date.month();
  printf("DATE %d %d %d", N.day_o, N.month_o, N.years_o);
}

void depos::on_dateEdit_2_dateChanged(const QDate &date1) {
  N.month_sum_j[0] = 0;
  int a = date1.day();
  int b = date1.year();
  int c = date1.month();
  N.month_sum_j[0] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  if (N.day_o >= a) {
    N.month_sum_j[0] = N.month_sum_j[0] + 1;
  } else {
    N.month_sum_j[0] = N.month_sum_j[0] + 2;
  }
}

void depos::on_dateEdit_3_dateChanged(const QDate &date2) {
  N.month_sum_j[1] = 0;
  int a = date2.day();
  int b = date2.year();
  int c = date2.month();
  N.month_sum_j[1] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  if (N.day_o >= a) {
    N.month_sum_j[1] = N.month_sum_j[1] + 1;
  } else {
    N.month_sum_j[1] = N.month_sum_j[1] + 2;
  }
}

void depos::on_dateEdit_4_dateChanged(const QDate &date3) {
  N.month_sum_j[2] = 0;
  int a = date3.day();
  int b = date3.year();
  int c = date3.month();
  N.month_sum_j[2] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  if (N.day_o >= a) {
    N.month_sum_j[2] = N.month_sum_j[2] + 1;
  } else {
    N.month_sum_j[2] = N.month_sum_j[2] + 2;
  }
}

void depos::on_dateEdit_5_dateChanged(const QDate &date4) {
  N.month_sum_j[3] = 0;
  int a = date4.day();
  int b = date4.year();
  int c = date4.month();
  N.month_sum_j[3] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  if (N.day_o >= a) {
    N.month_sum_j[3] = N.month_sum_j[3] + 1;
  } else {
    N.month_sum_j[3] = N.month_sum_j[3] + 2;
  }
}

void depos::on_dateEdit_6_dateChanged(const QDate &date5) {
  N.month_sum_j[4] = 0;
  int a = date5.day();
  int b = date5.year();
  int c = date5.month();
  N.month_sum_j[4] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  if (N.day_o >= a) {
    N.month_sum_j[4] = N.month_sum_j[4] + 1;
  } else {
    N.month_sum_j[4] = N.month_sum_j[4] + 2;
  }
}

void depos::on_dateEdit_7_dateChanged(const QDate &date) {
  N.month_sum_j[5] = 0;
  // int a = date.day();
  int b = date.year();
  int c = date.month();
  N.month_sum_j[5] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
  //         if (N.day_o >= a){N.month_sum_j[5] =N.month_sum_j[5] +1;} else
  //         {N.month_sum_j[5] = N.month_sum_j[5]+2;}
}

void depos::on_dateEdit_8_dateChanged(const QDate &date) {
  N.month_sum_j[6] = 0;
  // int a = date.day();
  int b = date.year();
  int c = date.month();
  N.month_sum_j[6] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
}

void depos::on_dateEdit_9_dateChanged(const QDate &date) {
  N.month_sum_j[7] = 0;
  // int a = date.day();
  int b = date.year();
  int c = date.month();
  N.month_sum_j[7] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
}

void depos::on_dateEdit_10_dateChanged(const QDate &date) {
  N.month_sum_j[8] = 0;
  // int a = date.day();
  int b = date.year();
  int c = date.month();
  N.month_sum_j[8] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
}

void depos::on_dateEdit_11_dateChanged(const QDate &date) {
  N.month_sum_j[9] = 0;
  // int a = date.day();
  int b = date.year();
  int c = date.month();
  N.month_sum_j[9] = (b * 12 + c) - (N.years_o * 12 + N.month_o);
}
