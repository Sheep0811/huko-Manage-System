#include "adminlog.h"
#include "ui_adminlog.h"
#include "tmp.h"
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
#include<QSettings>
adminlog::adminlog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminlog)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    QSettings setting("config.ini",QSettings::IniFormat);
    QString account = setting.value("section/account").toString();
    QString password = setting.value("section/password").toString();
    ui->lineEdit_name->setText(account);
    ui->lineEdit_password->setText(password);

}

adminlog::~adminlog()
{
    delete ui;
}

void adminlog::on_pushButton_2_clicked()
{
    close();
}

void adminlog::on_pushButton_clicked()
{
    QString inputname=ui->lineEdit_name->text();
    QString inputpassword=ui->lineEdit_password->text();
    QSqlQueryModel *model1=new QSqlQueryModel;
    //QSqlQueryModel *model2=new QSqlQueryModel;
    QString sql1="SELECT * FROM operator WHERE username='"+inputname+"'";
    model1->setQuery(sql1);
    if(model1->rowCount()>0)
    {
        QSqlQuery sql2;
        sql2.exec("SELECT password FROM operator WHERE username='"+inputname+"'");
        if(sql2.next()&&sql2.value(0).toString()==inputpassword)
        {
            if(ui->remember->isChecked())
            {
                QSettings setting("config.ini", QSettings::IniFormat);//配置文件在工程目录下
                //把用户账号密码写到配置文件中：
                setting.beginGroup("section");//节开始
                setting.setValue("account", inputname);
                setting.setValue("password", inputpassword);
                setting.endGroup();//结束
            }
            ad=new admin;
            ad->username=inputname;
            ad->init();
            ad->show();
            this->close();
           }
        else
        {
            QMessageBox::about(NULL,"错误","密码不正确");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","管理员账号不存在！");
    }
}

void adminlog::on_lineEdit_password_returnPressed()
{
    on_pushButton_clicked();
}

void adminlog::on_lineEdit_name_returnPressed()
{
    on_pushButton_clicked();
}

void adminlog::on_pushButton_3_clicked()
{
    fo=new forgetpasssword();
    //QPoint globalPos = this->mapToGlobal(QPoint(0, 0));
    //fo->move(globalPos.x(), globalPos.y());
    fo->show();
}


void adminlog::on_showpassword_clicked(bool checked)
{
    if(checked)
     ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    else
     ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}
