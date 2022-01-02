#include "admin.h"
#include "ui_admin.h"
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
admin::admin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin)
{
    ui->setupUi(this);
    this->setWindowTitle("管理员");
    showtime();
    QTimer *timer_calendar;//用来显示当前日期的定时器
    timer_calendar = new QTimer(this);//new一个QTimer对象
    connect(timer_calendar,SIGNAL(timeout()),this,SLOT(showtime()));//连接槽函数
    timer_calendar->start(1000);//每一秒溢出一次进入槽函数
}

admin::~admin()
{
    delete ui;
}

void admin::init()
{
    ui->lineEidt->setText(username);
}

void admin::showtime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    this->ui->label_time->setText(str);
}

void admin::on_pushButton_clicked()
{
    QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    if(ui->comboBox->currentText()=="户籍信息")
    {
        sql1="SELECT Hno as 户籍号,Hname as 户主,ID as 户主身份证,Adr as 所在地,regdate as 登记日期 FROM hk";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,70);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,90);
        ui->tableView->setColumnWidth(3,150);
        ui->tableView->setColumnWidth(4,150);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    }
    else if(ui->comboBox->currentText()=="人口关系")
    {
        sql1="SELECT Hno as 户籍号,ID as 身份证号,name as 姓名,relat as 户主或与户主关系,indate as 迁入时间,wherein as 迁入地 from relation";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,70);
        ui->tableView->setColumnWidth(1,90);
        ui->tableView->setColumnWidth(2,70);
        ui->tableView->setColumnWidth(3,130);
        ui->tableView->setColumnWidth(4,150);
        ui->tableView->setColumnWidth(5,100);
            ui->tableView->setAlternatingRowColors(true); // 隔行变色
            ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
            ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
        }
    else if(ui->comboBox->currentText()=="个人信息")
    {
        sql1="SELECT ID as 身份证号,name as 姓名,sex as 性别,nation as 民族,province as 祖籍,birthdata as 出生日,birthplace as 出生地,liveplace as 现居地,education as 学历 from person;";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,90);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,50);
        ui->tableView->setColumnWidth(3,70);
        ui->tableView->setColumnWidth(4,70);
        ui->tableView->setColumnWidth(5,150);
        ui->tableView->setColumnWidth(6,70);
        ui->tableView->setColumnWidth(7,70);
        ui->tableView->setColumnWidth(8,70);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
        //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    else if(ui->comboBox->currentText()=="户籍迁出记录")
    {
        sql1="SELECT Hno as 户籍号,Hname as 户主,outdata as 迁出日期,originadr as 迁出地,outadress as 迁入地 from hout;";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,70);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,150);
        ui->tableView->setColumnWidth(3,150);
        ui->tableView->setColumnWidth(4,150);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    }
    else if(ui->comboBox->currentText()=="人口迁出记录")
    {
        sql1="SELECT ID as 身份证号,name as 姓名,outHno as 迁出户籍号,inHno as 迁入户籍号,outdata as 迁出日期 from perout;";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,90);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,100);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,150);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    }
    else if(ui->comboBox->currentText()=="户籍注销记录")
    {
        sql1="SELECT Hno as 户籍号,name as 姓名,disdata as 注销日期,reason as 注销原因,prove as 注销证明 from hdis;";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,70);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,130);
        ui->tableView->setColumnWidth(3,100);
        ui->tableView->setColumnWidth(4,100);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    }
    else
    {
        sql1="SELECT username as 管理员用户名,password as 密码,phone as 手机号 from operator;";
        model1->setQuery(sql1);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,100);
        ui->tableView->setColumnWidth(2,100);
        ui->tableView->setModel(model1);
        ui->tableView->setAlternatingRowColors(true); // 隔行变色
        ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    }
}


void admin::on_pushButton_nohukou_clicked()
{
    QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    sql1="SELECT * FROM 无户籍居民;";
    model1->setQuery(sql1);
    ui->tableView->setModel(model1);
    ui->tableView->setColumnWidth(0,90);
    ui->tableView->setColumnWidth(1,70);
    ui->tableView->setColumnWidth(2,50);
    ui->tableView->setColumnWidth(3,70);
    ui->tableView->setColumnWidth(4,70);
    ui->tableView->setColumnWidth(5,150);
    ui->tableView->setColumnWidth(6,70);
    ui->tableView->setColumnWidth(7,70);
    ui->tableView->setColumnWidth(8,70);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
}

void admin::on_pushButton_admin_clicked()
{
    us = new userchange;
    us->show();
}

void admin::on_pushButton_relat_clicked()
{
    re=new related;
    re->show();
}

void admin::on_pushButton_2_clicked()
{
    close();
}

void admin::on_pushButton_per_clicked()
{
    per=new person;
    per->show();
}

void admin::on_pushButton_hukou_clicked()
{
    huk= new hk;
    huk->show();
}

void admin::on_pushButton_order_clicked()
{
    QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    if(ui->order->currentText()=="降序")
    {
            sql1="SELECT * FROM hkpersonage ORDER BY 年龄 DESC;";
            model1->setQuery(sql1);
            ui->tableView->setModel(model1);
            ui->tableView->setColumnWidth(0,90);
            ui->tableView->setColumnWidth(1,90);
            ui->tableView->setColumnWidth(2,90);
            ui->tableView->setColumnWidth(3,90);
            ui->tableView->setColumnWidth(4,90);
    }
    else
    {
        sql1="SELECT * FROM hkpersonage ORDER BY 年龄 ;";
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        ui->tableView->setColumnWidth(0,90);
        ui->tableView->setColumnWidth(1,90);
        ui->tableView->setColumnWidth(2,90);
        ui->tableView->setColumnWidth(3,90);
        ui->tableView->setColumnWidth(4,90);
    }
}
