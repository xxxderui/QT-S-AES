#ifndef CHOICE_H
#define CHOICE_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class choice;
}

class choice : public QMainWindow
{
    Q_OBJECT

public:
    explicit choice(QWidget *parent = nullptr);
    ~choice();
    void mousePressEvent(QMouseEvent *event);

private:
    Ui::choice *ui;
};

#endif // CHOICE_H
