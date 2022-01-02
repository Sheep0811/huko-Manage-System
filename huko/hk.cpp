#include "hk.h"
#include "ui_hk.h"
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
#include<QSqlTableModel>
#include<QKeyEvent>
hk::hk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::hk)
{
    ui->setupUi(this);
    this->setWindowTitle("户籍信息");
    search();
    showtime();
}

hk::~hk()
{
    delete ui;
}

void hk::showtime()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    this->ui->date->setText(curDateTime.toString("yyyy-MM-dd"));
}

void hk::search()
{
    /*QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    sql1="SELECT Hno as 户籍号,Hname as 户主,ID as 户主身份证,Adr as 所在地,regdate as 登记日期 FROM hk";
    model1->setQuery(sql1);
    ui->tableView->setModel(model1);*/
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("hk");
    ui->tableView->setModel(model);
    model->select();
    QStringList tables;
    tables << "户籍号" << "户主" << "户主身份证"<< "所在地" << "登记日期";
    for(int i = 0 ; i < tables.count(); i++)
        model->setHeaderData(i,Qt::Horizontal,tables[i]);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,70);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,150);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
}

void hk::on_pushButton_clicked()
{
    close();
}

void hk::on_pushButtoninsert_clicked()
{
    QString hno=this->ui->hno->text();
    QString name=this->ui->hname->text();
    QString id=this->ui->id->text();
    QString adr=this->ui->addr->text();
    QString date=this->ui->date->text();
    if(hno!=NULL && id!=NULL && name!=NULL && adr!=NULL && date!=NULL)
    {
        QSqlQuery sql1;
        sql1.exec("INSERT INTO hk values('"+hno+"','"+name+"','"+id+"','"+adr+"','"+date+"')");
        if(sql1.isActive())
        {
            QMessageBox::about(NULL,"提示","添加成功");
            search();
        }
        else
        {
            QMessageBox::about(this,"提示","错误：\n"+sql1.lastError().text());
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","信息不全");
    }
}

void hk::on_pushButtondelete_clicked()
{
        QString id;
        int rowToDel;
        QMap<int, int> rowMap;

        QAbstractItemModel *model = ui->tableView->model();
        QItemSelectionModel *selections = ui->tableView->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        foreach (QModelIndex index, selected)
        {

            rowMap.insert(index.row(), 0);
        }

        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            QModelIndex index=model->index(rowToDel,0);//rowNum,columnNum为行列号
            id=index.sibling(rowToDel,0).data().toString();
            QSqlQuery query;
            QString cmd;
            //qDebug()<<id;
            cmd =QString("delete from hk where hno = %1").arg(id);

            QMessageBox change;
            change.setText("确定删除?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Cancel);
            if(change.exec()==QMessageBox::Yes)
            {
                     query.exec(cmd);
               if(!query.isActive())
               {
                QMessageBox::about(this,"提示","删除数据失败!"+query.lastError().text());
                }
            else
            {
                  re=new reason;
                  re->set(id);
                    re->show();
                   search();
                   this->ui->hno->setText("");
                   this->ui->id->setText("");
                   this->ui->hname->setText("");
                   this->ui->addr->setText("");
                   this->ui->date->setText("");
            }
            }
        }
}

void hk::on_tableView_pressed(const QModelIndex &index)
{
    int num=index.row();
    QAbstractItemModel *model = ui->tableView->model();
    //QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndex index1=model->index(num,0,QModelIndex());
    QString str1= index1.data().toString();
    this->ui->hno->setText(str1);
    index1=model->index(num,1,QModelIndex());
    str1= index1.data().toString();
    this->ui->hname->setText(str1);
    index1=model->index(num,2,QModelIndex());
    str1= index1.data().toString();
    this->ui->id->setText(str1);
    index1=model->index(num,3,QModelIndex());
    str1= index1.data().toString();
    this->ui->addr->setText(str1);
    index1=model->index(num,4,QModelIndex());
    QDateTime timme= index1.data().toDateTime();
    str1= timme.toString("yyyy-MM-dd");
    this->ui->date->setText(str1);
}

void hk::on_pushButtonsearch_clicked()
{
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString hno=this->ui->hno->text()==NULL?" like '%' " :" = '"+this->ui->hno->text()+"'";
    QString name="like '%"+ ui->hname->text()+"%'";
    QString id=this->ui->id->text()==NULL?" like '%' " :" = '"+this->ui->id->text()+"'";
    QString adr="like '%"+ ui->addr->text()+"%'";
    QString date="like '"+ ui->date->text()+"%'";
    QString sql1;
    sql1="SELECT Hno as 户籍号,Hname as 户主,ID as 户主身份证,Adr as 所在地,regdate as 登记日期 FROM hk where hno "+hno+" and id "+id+" and regdate "+date+" and Adr "+adr+" and hname "+name+" ";
    //qDebug()<<sql1;
    model2->setQuery(sql1);
    ui->tableView->setModel(model2);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,70);
    ui->tableView->setColumnWidth(2,90);
    ui->tableView->setColumnWidth(3,150);
    ui->tableView->setColumnWidth(4,150);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    if(model2->rowCount()>0)
    {
        QMessageBox::about(NULL,"提示","查询成功");
    }
    else
    {
        QMessageBox::about(NULL,"提示","没有查询到信息");
    }
}

void hk::on_pushButton_2_clicked()
{
    search();
    this->ui->hno->setText("");
    this->ui->id->setText("");
    this->ui->hname->setText("");
    this->ui->addr->setText("");
    this->ui->date->setText("");
}

void hk::on_pushButtonchange_clicked()
{
    QString hno=this->ui->hno->text();
    QString name=this->ui->hname->text();
    QString id=this->ui->id->text();
    QString adr=this->ui->addr->text();
    QString date=this->ui->date->text();
    QSqlQuery sql1;
    sql1.prepare("update hk set Adr='"+adr+"' where hno='"+hno+"' ");
    QMessageBox change;
    change.setText("确定更改?");
    change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    change.setDefaultButton(QMessageBox::Cancel);
    if(change.exec()==QMessageBox::Yes)
    {
        if(sql1.exec())
        {
            QMessageBox::about(NULL,"提示","更改成功");
            search();
        }
        else
        {
            QMessageBox::about(NULL,"错误","更改失败");
        }
    }
}

void hk::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        search();
        this->ui->hno->setText("");
        this->ui->id->setText("");
        this->ui->hname->setText("");
        this->ui->addr->setText("");
        this->ui->date->setText("");
    }
}
