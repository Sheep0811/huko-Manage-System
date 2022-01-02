#ifndef FORGETPASSSWORD_H
#define FORGETPASSSWORD_H

#include <QWidget>

namespace Ui {
class forgetpasssword;
}

class forgetpasssword : public QWidget
{
    Q_OBJECT

public:
    explicit forgetpasssword(QWidget *parent = nullptr);
    ~forgetpasssword();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_ok_clicked();

private:
    Ui::forgetpasssword *ui;
};

#endif // FORGETPASSSWORD_H
