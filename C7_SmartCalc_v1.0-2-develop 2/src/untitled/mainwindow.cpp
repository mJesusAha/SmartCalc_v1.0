#include "mainwindow.h"

#include <stdlib.h>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushEQ_clicked() {
  QString name = ui->lineEdit->text();
  QByteArray t = name.toLocal8Bit();
  char *str_char = t.data();
  char t1[500];
  h = 0.01;
  xBegin = -3;
  xEnd = 3 + h;
  ui->widget->xAxis->setLabel("x");
  ui->widget->xAxis->setLabel("y");

  QString xminname = ui->lineX_min->text();
  QByteArray x1 = xminname.toLocal8Bit();
  char *str_x1 = x1.data();
  double X1 = myatof(str_x1);
  QString xmaxname = ui->lineX_max->text();
  QByteArray x2 = xmaxname.toLocal8Bit();
  char *str_x2 = x2.data();
  X2 = myatof(str_x2);
  QString yminname = ui->lineY_min->text();
  QByteArray y1 = yminname.toLocal8Bit();
  char *str_y1 = y1.data();
  double Y1 = myatof(str_y1);
  QString ymaxname = ui->lineY_max->text();
  QByteArray y2 = ymaxname.toLocal8Bit();
  char *str_y2 = y2.data();
  double Y2 = myatof(str_y2);
  ui->widget->xAxis->setRange(X1, X2);
  ui->widget->yAxis->setRange(Y1, Y2);
  ui->widget->replot();
  if (xmaxname.isEmpty()) {
    X2 = X1;
  }
  if (name.isEmpty()) {
    ui->label->setText("0");
  } else {
    int error = s21_result(str_char, t1, X1);
    if (error < 0) {
      ui->label->setText("ERROR!");
    } else {
      ui->label->setText(t1);
    }
    double a = X1;
    double b = X2;
    int N = (b - a) / h + 2;
    QVector<double> x(N), y(N);
    int i = 0;
    for (X = a; i < N; X += h) {
      if (X == -INFINITY || X == INFINITY || X == NAN) {
        X = 0;
      }
      x[i] = X;
      str_char = t.data();
      s21_result(str_char, t1, X);

      y[i] = myatof(t1);
      i++;
    }
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph()->setData(x, y);
    ui->widget->xAxis->setLabel("Y");
    ui->widget->xAxis->setLabel("X");
    ui->widget->xAxis->setRange(a, b);
    if (ymaxname.isEmpty() || yminname.isEmpty()) {
      double minY = y[0], maxY = y[0];
      for (int i = 1; i < N; i++) {
        if (y[i] < minY) minY = y[i];
        if (y[i] > maxY) maxY = y[i];
      }
      ui->widget->yAxis->setRange(minY, maxY);
    }
    ui->widget->yAxis->setRange(Y1, Y2);
    ui->widget->replot();
    x.clear();
    y.clear();
    x.squeeze();
    y.squeeze();
  }
}

void MainWindow::on_pushButton_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ".");
}

void MainWindow::on_Button0_2_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void MainWindow::on_Button0_3_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void MainWindow::on_Button0_4_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void MainWindow::on_Button0_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void MainWindow::on_Button0_8_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void MainWindow::on_Button0_5_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void MainWindow::on_Button0_7_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void MainWindow::on_Button0_12_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "~");
}

void MainWindow::on_Button0_30_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "x");
}

void MainWindow::on_Button0_11_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "^");
}

void MainWindow::on_Button0_21_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "(");
}

void MainWindow::on_Button0_19_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + ")");
}

void MainWindow::on_Button0_13_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sin");
}

void MainWindow::on_Button0_15_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "cos");
}

void MainWindow::on_Button0_9_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "tan");
}

void MainWindow::on_Button0_24_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "ln");
}

void MainWindow::on_Button0_17_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "asin");
}

void MainWindow::on_Button0_18_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "acos");
}

void MainWindow::on_Button0_20_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "atan");
}

void MainWindow::on_Button0_23_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "log");
}

void MainWindow::on_Button0_25_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "sqrt");
}

void MainWindow::on_Button0_22_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "mod");
}

void MainWindow::on_Button0_29_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "/");
}

void MainWindow::on_Button0_28_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "*");
}

void MainWindow::on_Button0_27_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "-");
}

void MainWindow::on_Button0_26_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "+");
}

void MainWindow::on_Button0_16_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void MainWindow::on_Button0_10_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void MainWindow::on_Button0_14_clicked() {
  ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void MainWindow::on_Button0_31_clicked() {
  ui->lineEdit->clear();
  ui->label->setText("0");
  x.clear();
  y.clear();
  x.squeeze();
  y.squeeze();
  ui->widget->clearGraphs();
  ui->widget->addGraph();
  ui->widget->replot();
}

void MainWindow::on_pushButton_2_clicked() { credit.show(); }

void MainWindow::on_pushButton_3_clicked() { depos.show(); }
