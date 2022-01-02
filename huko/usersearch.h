#ifndef USERSEARCH_H
#define USERSEARCH_H

#include <QWidget>

namespace Ui {
class usersearch;
}

class usersearch : public QWidget
{
    Q_OBJECT

public:
    explicit usersearch(QWidget *parent = nullptr);
    ~usersearch();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_exit_clicked();

    void on_lineEdit_id_returnPressed();

private:
    Ui::usersearch *ui;
    QString inputid;
};

#endif // USERSEARCH_H
