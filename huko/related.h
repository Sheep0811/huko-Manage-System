#ifndef RELATED_H
#define RELATED_H

#include <QWidget>

namespace Ui {
class related;
}

class related : public QWidget
{
    Q_OBJECT

public:
    explicit related(QWidget *parent = nullptr);
    ~related();
private slots:
    void on_pushButton_clicked();

    void on_pushButtoninsert_clicked();
    void showtime();
    void on_pushButtondelete_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonchange_clicked();

    void on_pushButtonsearch_clicked();

    void on_tableView_pressed(const QModelIndex &index);

private:
    Ui::related *ui;
        void search();
        void keyPressEvent(QKeyEvent * event);

};

#endif // RELATED_H
