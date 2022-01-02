#ifndef HK_H
#define HK_H

#include <QWidget>
#include<reason.h>
namespace Ui {
class hk;
}

class hk : public QWidget
{
    Q_OBJECT

public:
    explicit hk(QWidget *parent = nullptr);
    ~hk();

private slots:
    void on_pushButton_clicked();
    void showtime();

    void on_pushButtoninsert_clicked();

    void on_pushButtondelete_clicked();

    void on_tableView_pressed(const QModelIndex &index);

    void on_pushButtonsearch_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonchange_clicked();

private:
    Ui::hk *ui;
    void search();
    reason *re;
    void keyPressEvent(QKeyEvent *event);
};

#endif // HK_H
