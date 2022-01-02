#ifndef ADMINLOG_H
#define ADMINLOG_H

#include <QWidget>
#include "admin.h"
#include"forgetpasssword.h"
#include"tmp.h"
namespace Ui {
class adminlog;

}

class adminlog : public QWidget
{
    Q_OBJECT

public:
    explicit adminlog(QWidget *parent = nullptr);
    ~adminlog();
    QString inputname;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_password_returnPressed();

    void on_lineEdit_name_returnPressed();

    void on_pushButton_3_clicked();


    void on_showpassword_clicked(bool checked);

private:
    Ui::adminlog *ui;
    admin *ad;
    forgetpasssword *fo;
    tmp *tp;
};

#endif // ADMINLOG_H
