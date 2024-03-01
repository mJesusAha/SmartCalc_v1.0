#ifndef DEPOS_H
#define DEPOS_H

#include <QWidget>
extern "C" {
#include "../credits.h"
#include "../deposid.h"
}
namespace Ui {
class depos;
}

class depos : public QWidget {
  Q_OBJECT

 public:
  explicit depos(QWidget *parent = nullptr);
  ~depos();
  // void on_dateEdit_dateChanged(const QDate &date);
 private slots:
  void on_pushButton_clicked();

  void on_comboBox_activated(int index);

  void on_comboBox_2_activated(int index);

  //    void on_dateEdit_dateChanged(const QDate &date);

  void popDep();
  void minusDep();
  void on_dateEdit_dateChanged(const QDate &date);

  void on_dateEdit_2_dateChanged(const QDate &date);

  void on_dateEdit_3_dateChanged(const QDate &date);

  void on_dateEdit_4_dateChanged(const QDate &date);

  void on_dateEdit_5_dateChanged(const QDate &date);

  void on_dateEdit_6_dateChanged(const QDate &date);

  void on_dateEdit_7_dateChanged(const QDate &date);

  void on_dateEdit_8_dateChanged(const QDate &date);

  void on_dateEdit_9_dateChanged(const QDate &date);

  void on_dateEdit_10_dateChanged(const QDate &date);

  void on_dateEdit_11_dateChanged(const QDate &date);

 private:
  Ui::depos *ui;
  deposid N;
};

#endif  // DEPOS_H
