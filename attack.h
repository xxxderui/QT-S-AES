#ifndef ATTACK_H
#define ATTACK_H

#include <QMainWindow>

namespace Ui {
class attack;
}

class attack : public QMainWindow
{
    Q_OBJECT

public:
    explicit attack(QWidget *parent = nullptr);
    ~attack();

private:
    Ui::attack *ui;
};

#endif // ATTACK_H
