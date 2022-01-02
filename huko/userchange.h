#ifndef USERCHANGE_H
#define USERCHANGE_H

#include <QWidget>

namespace Ui {
class userchange;
}

class userchange : public QWidget
{
    Q_OBJECT

public:
    explicit userchange(QWidget *parent = nullptr);
    ~userchange();

private slots:
    void on_pushButtoninsert_clicked();

    void on_pushButtondelete_clicked();

    void on_pushButtonchange_clicked();

    void on_pushButtonsearch_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_pressed(const QModelIndex &index);



private:
    Ui::userchange *ui;
    void search();
    void keyPressEvent(QKeyEvent * event);
};

#endif // USERCHANGE_H
