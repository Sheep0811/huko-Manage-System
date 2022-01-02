#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTextStream>
#include <stdio.h>
#include<QSqlQuery>
#include<qtextcodec.h>
void createConnection();
int main(int argc, char *argv[])
{
    createConnection();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
void createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("hukou");
    db.setUserName("root");
    db.setPassword("110811");
    bool ok = db.open();
    if (ok)
    {
        qDebug() << "连接成功" ;
    }
    else
    {
         qDebug()<<"error open database because"<<db.lastError().text();
    }
}

