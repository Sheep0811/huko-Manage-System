#include "usersearch.h"
#include "ui_usersearch.h"
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
#include<QSqlQuery>
#include<qdebug.h>

usersearch::usersearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::usersearch)
{
    ui->setupUi(this);
    this->setWindowTitle("用户查询");
}

usersearch::~usersearch()
{
    delete ui;
}

void usersearch::on_pushButton_search_clicked()
{
    QString sql1,sql2,sql3;
    QString inputid=ui->lineEdit_id->text();
    sql1="SELECT Hno as 户籍号,Hname as 户主,ID as 户主身份证,Adr as 所在地,regdate as 登记日期 FROM hk WHERE Hno IN (SELECT Hno FROM relation WHERE relation.ID='"+inputid+"')";
    sql2="SELECT person.ID as 身份证号,person.name as 姓名,relat as 户主或与户主关系,Sex as 性别,year(NOW())-year(birthdata) as 年龄,liveplace as 现居地,indate as 迁入时间 FROM relation,person WHERE relation.ID=person.ID AND Hno=(SELECT Hno FROM relation WHERE relation.ID='"+inputid+"')";
    sql3="SELECT ID as 身份证号,name as 姓名,sex as 性别,nation as 民族,province as 祖籍,birthdata as 出生日,birthplace as 出生地,liveplace as 现居地,education as 学历 from person where id='"+inputid+"';";
    QSqlQueryModel *modell=new QSqlQueryModel;
    QSqlQueryModel *model=new QSqlQueryModel;
    modell->setQuery(sql1);
    model->setQuery(sql3);
    ui->person->setModel(model);
    ui->person->setColumnWidth(0,90);
    ui->person->setColumnWidth(1,70);
    ui->person->setColumnWidth(2,50);
    ui->person->setColumnWidth(3,70);
    ui->person->setColumnWidth(4,70);
    ui->person->setColumnWidth(5,150);
    ui->person->setColumnWidth(6,70);
    ui->person->setColumnWidth(7,70);
    ui->person->setColumnWidth(8,70);
    ui->person->setAlternatingRowColors(true); // 隔行变色
    ui->person->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->person->setStyleSheet("QHeaderView::section{background:white;color: black;}");

        QSqlQueryModel *modell2=new QSqlQueryModel;
        modell2->setQuery(sql2);
        ui->tableView->setModel(modell);
        ui->tableView->setColumnWidth(0,70);
        ui->tableView->setColumnWidth(1,70);
        ui->tableView->setColumnWidth(2,90);
        ui->tableView->setColumnWidth(3,150);
        ui->tableView->setColumnWidth(4,150);
        ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
        ui->tableView_2->setModel(modell2);
        ui->tableView_2->setAlternatingRowColors(true); // 隔行变色
        ui->tableView_2->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
        ui->tableView_2->setStyleSheet("QHeaderView::section{background:white;color: black;}");//
        ui->tableView_2->setModel(modell2);
        ui->tableView_2->setColumnWidth(0,90);
        ui->tableView_2->setColumnWidth(1,70);
        ui->tableView_2->setColumnWidth(2,130);
        ui->tableView_2->setColumnWidth(3,70);
        ui->tableView_2->setColumnWidth(4,70);
        ui->tableView_2->setColumnWidth(5,70);
        ui->tableView_2->setColumnWidth(6,150);
        if(model->rowCount()==0)
        {
            QMessageBox::about(NULL,"错误","个人信息不存在");
        }
       else
        {
            if(modell->rowCount()==0)
                QMessageBox::about(NULL,"提示","没有查询到户籍信息");
            else
                QMessageBox::about(NULL,"提示","查询成功！");
        }
}

void usersearch::on_pushButton_exit_clicked()
{
    close();
}

void usersearch::on_lineEdit_id_returnPressed()
{
    on_pushButton_search_clicked();
}
