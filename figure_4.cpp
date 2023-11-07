#include "figure_4.h"
#include "ui_figure_4.h"

figure_4::figure_4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::figure_4)
{
    ui->setupUi(this);
}

figure_4::~figure_4()
{
    delete ui;
}
