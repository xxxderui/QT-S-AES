#ifndef FIGURE_4_H
#define FIGURE_4_H

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
class figure_4;
}

class figure_4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit figure_4(QWidget *parent = nullptr);
    ~figure_4();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::figure_4 *ui;
};

#endif // FIGURE_4_H
