#ifndef FIGURE_2_H
#define FIGURE_2_H

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
class figure_2;
}

class figure_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit figure_2(QWidget *parent = nullptr);
    ~figure_2();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::figure_2 *ui;
};

#endif // FIGURE_2_H
