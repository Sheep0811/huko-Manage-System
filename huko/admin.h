#ifndef ADMIN_H
#define ADMIN_H

#include <QWidget>
#include"userchange.h"
#include"related.h"
#include"person.h"
#include"hk.h"
namespace Ui {
class admin;
}

class admin : public QWidget
{
    Q_OBJECT

public:
    explicit admin(QWidget *parent = nullptr);
    ~admin();
    void init();
    QString username;

private slots:
    void showtime();
    void on_pushButton_clicked();

    void on_pushButton_nohukou_clicked();

    void on_pushButton_admin_clicked();

    void on_pushButton_relat_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_per_clicked();

    void on_pushButton_hukou_clicked();

    void on_pushButton_order_clicked();

private:
    Ui::admin *ui;
    userchange *us;
    related *re;
    person *per;
    hk *huk;
};

#endif // ADMIN_H
