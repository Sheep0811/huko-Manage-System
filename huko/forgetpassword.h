#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>

namespace Ui {
class forgetpassword;
}

class forgetpassword : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpassword(QWidget *parent = nullptr);
    ~forgetpassword();

private slots:
    void on_pushButton_quit_clicked();

private:
    Ui::forgetpassword *ui;
};

#endif // FORGETPASSWORD_H
