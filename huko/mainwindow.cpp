#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlQueryModel>
#include<QDebug>
#include<QMessageBox>
#include"adminlog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("2019065725杨洋");
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}

void MainWindow::on_pushButton_user_clicked()
{
    users=new usersearch();
    users->show();
}

void MainWindow::on_pushButton_admin_clicked()
{
    adm=new adminlog();
    adm->show();
}
