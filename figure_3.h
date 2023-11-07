#ifndef FIGURE_3_H
#define FIGURE_3_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <QString>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <sstream>
#include <iterator>
#include <string>
#include <QMouseEvent>
#include <bitset>

namespace Ui {
class figure_3;
}

class figure_3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit figure_3(QWidget *parent = nullptr);
    ~figure_3();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::figure_3 *ui;
};

#endif // FIGURE_3_H
