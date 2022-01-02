#include "reason.h"
#include "ui_reason.h"
#include<QSqlQueryModel>
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
#include <QSqlQuery>
#include <qdebug.h>
#include<QDateTime>
#include <QTimer>
#include <QTime>
reason::reason(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reason)
{
    ui->setupUi(this);
    this->setWindowTitle("补充信息");

}

reason::~reason()
{
    delete ui;
}

void reason::set(QString tmp)
{
    hno=tmp;
}

void reason::on_pushButton_clicked()
{
    QString reason=ui->reason_2->toPlainText();
    QString prove=ui->proved->toPlainText();
    QSqlQuery sql1;
    sql1.prepare("update hdis set reason='"+reason+"', prove='"+prove+"' where hno='"+hno+"'");
    sql1.exec();
    QMessageBox::about(this,"提示","删除数据成功!");
    this->close();
}
