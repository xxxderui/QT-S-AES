#ifndef ATTACK_H
#define ATTACK_H

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
class attack;
}

class attack : public QMainWindow
{
    Q_OBJECT

public:
    explicit attack(QWidget *parent = nullptr);
    ~attack();
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::attack *ui;
};

#endif // ATTACK_H
