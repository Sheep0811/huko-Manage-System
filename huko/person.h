#ifndef PERSON_H
#define PERSON_H

#include <QWidget>

namespace Ui {
class person;
}

class person : public QWidget
{
    Q_OBJECT

public:
    explicit person(QWidget *parent = nullptr);
    ~person();

private slots:
    void on_pushButtonexit_clicked();

    void on_pushButton_search_clicked();

    void on_pushButtoninsert_clicked();

    void on_pushButtondelete_clicked();
    void showtime();
    void on_pushButtonchange_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButtonsearch_clicked();

private:
    Ui::person *ui;
    void search();
    void keyPressEvent(QKeyEvent *event);
};

#endif // PERSON_H
