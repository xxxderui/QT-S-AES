#ifndef FIGURE_H
#define FIGURE_H

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
class figure;
}

class figure : public QMainWindow
{
    Q_OBJECT

public:
    explicit figure(QWidget *parent = nullptr);
    ~figure();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::figure *ui;
};

#endif // FIGURE_H
