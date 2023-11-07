#ifndef FIGURE_4_H
#define FIGURE_4_H

#include <QMainWindow>

namespace Ui {
class figure_4;
}

class figure_4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit figure_4(QWidget *parent = nullptr);
    ~figure_4();

private:
    Ui::figure_4 *ui;
};

#endif // FIGURE_4_H
