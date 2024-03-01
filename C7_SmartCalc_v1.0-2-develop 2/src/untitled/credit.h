#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>
extern "C" {
#include "../credits.h"
}
namespace Ui {
class credit;
}

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_comboBox_activated(int index);

  void on_pushButton_clicked();

 private:
  Ui::credit *ui;
  cred N;
};

#endif  // CREDIT_H
