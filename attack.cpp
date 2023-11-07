#include "attack.h"
#include "ui_attack.h"

attack::attack(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::attack)
{
    ui->setupUi(this);
}

attack::~attack()
{
    delete ui;
}
