#include "credit.h"

#include "ui_credit.h"
credit::credit(QWidget *parent) : QWidget(parent), ui(new Ui::credit) {
  ui->setupUi(this);
  //    cred N;
}

credit::~credit() { delete ui; }

void credit::on_comboBox_activated(int index) {
  //    cred N;
  // N.type = 1;
  if (index == 1) {
    N.type = 1;
  }
  if (index == 0) {
    N.type = 0;
    //    }else
    //    if(index == 0) {
    //        N.type = 1;
  }
}

void credit::on_pushButton_clicked() {
  QString sum_in = ui->lineEdit->text(), procents = ui->lineEdit_2->text(),
          month = ui->lineEdit_3->text();
  QByteArray s = sum_in.toLocal8Bit(), p = procents.toLocal8Bit(),
             m = month.toLocal8Bit();

  //    if (sum_in.isEmpty()) {
  //        ui->lineEdit->setText("0");}
  //    } else {
  char *summ_in = s.data(), *proc = p.data(), *month_in = m.data();
  N.sum = atof(summ_in);
  if (sum_in.isEmpty() || N.sum <= 0.0) {
    N.sum = 0;
    ui->lineEdit->setText("0");
  } else {
    ui->lineEdit->setText(s.data());
  }
  //    }
  //        char *proc = p.data();
  N.procent = atof(proc);
  if (procents.isEmpty() || N.procent <= 0.0) {
    N.procent = 0.01;
    ui->lineEdit_2->setText("0.01");
  } else {
    ui->lineEdit_2->setText(p.data());
  }
  //    } else {
  //        char *proc = p.data();
  //        N.procent = atof(proc);
  //    }
  //    char *month_in = m.data();
  N.years = atof(month_in);
  if (month.isEmpty() || N.years <= 0.0) {
    N.years = 1;
    ui->lineEdit_3->setText("1");
  } else {
    ui->lineEdit_3->setText(m.data());
  }
  creds(&N);
  if (sum_in.isEmpty() || procents.isEmpty() || month.isEmpty()) {
    ui->label_12->setText("0");
    ui->label_11->setText("0");
    ui->label_10->setText("0");
    ui->label_9->setText("0");
  } else {
    ui->label_12->setText(N.all_t);
    ui->label_11->setText(N.perepl_t);
    ui->label_10->setText(N.sum_pl_last_t);
    ui->label_9->setText(N.sum_pl_firsth_t);
  }

  //    printf("|%f|", N.sum_pl_last);
  //    printf("|%f|", N.perepl);
}
