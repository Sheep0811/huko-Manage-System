#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"adminlog.h"
#include <QMainWindow>
#include "usersearch.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_exit_clicked();
    void on_pushButton_user_clicked();
    void on_pushButton_admin_clicked();

private:
    Ui::MainWindow *ui;
    usersearch *users;
    adminlog *adm;
};
#endif // MAINWINDOW_H
