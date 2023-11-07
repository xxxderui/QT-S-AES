#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "choice.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        if(e->x()>710&&e->x()<710+100&&e->y()>130&&e->y()<130+60){
            this->close();
            choice *f=new choice();
            f->show();
        }
        if(e->x()>710&&e->x()<710+100&&e->y()>390&&e->y()<390+60){
            this->close();
        }
    }
}

