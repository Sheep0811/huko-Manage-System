#include "forgetpasssword.h"
#include "ui_forgetpasssword.h"
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
forgetpasssword::forgetpasssword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpasssword)
{
    ui->setupUi(this);
    this->setWindowTitle("忘记密码");
}

forgetpasssword::~forgetpasssword()
{
    delete ui;
}

void forgetpasssword::on_pushButton_clicked()
{
    close();
}

void forgetpasssword::on_pushButton_ok_clicked()
{
    QString inputname=ui->lineEdit_name->text();
    QString inputphone=ui->lineEdit_phone->text();
    QString inputpass=ui->lineEdit_pass->text();
    QSqlQueryModel *model1=new QSqlQueryModel;
    //QSqlQueryModel *model2=new QSqlQueryModel;
    QString sql1="SELECT * FROM operator WHERE username='"+inputname+"'";
    model1->setQuery(sql1);
    if(model1->rowCount()>0)
    {
        QSqlQuery sql2;
        sql2.exec("SELECT phone FROM operator WHERE phone='"+inputphone+"'");
        if(sql2.next()&&sql2.value(0).toString()==inputphone)
        {
            QMessageBox change;
            change.setText("确定修改?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Yes);
            if(change.exec()==QMessageBox::Yes)
            {
                QSqlQuery sql3("update operator set password='"+inputpass+"' where username='"+inputname+"'");
                QMessageBox::about(NULL,"提示","更改成功！");
            }

            this->close();
        }
        else
        {
            QMessageBox::about(NULL,"错误","手机号不正确");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","管理员账号不存在！");
    }
}
