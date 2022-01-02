#include "person.h"
#include "ui_person.h"
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
person::person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::person)
{
    ui->setupUi(this);
        this->setWindowTitle("个人信息");
    search();
    showtime();
}

person::~person()
{
    delete ui;
}

void person::showtime()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    this->ui->birth->setText(curDateTime.toString("yyyy-MM-dd"));
}

void person::search()
{
    /*QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    sql1="SELECT ID as 身份证号,name as 姓名,sex as 性别,nation as 民族,province as 祖籍,birthdata as 出生日,birthplace as 出生地,liveplace as 现居地,education as 学历 from person;";
    model1->setQuery(sql1);
    //person->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model1);*/
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("person");
    ui->tableView->setModel(model);
    model->select();
    QStringList tables;
    tables << "身份证号" << "姓名" << "性别"<< "民族" << "祖籍" << "出生日"<< "出生地" << "现居地" << "学历";
    for(int i = 0 ; i < tables.count(); i++)
        model->setHeaderData(i,Qt::Horizontal,tables[i]);
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

void person::on_pushButtonexit_clicked()
{
    close();
}

void person::on_pushButton_search_clicked()
{
    search();
    this->ui->id->setText("");
    this->ui->sex->setCurrentIndex(0);
    this->ui->xingming->setText("");
    this->ui->minzu->setText("");
    this->ui->zuji->setText("");
    this->ui->bornplace->setText("");
    this->ui->liveplace->setText("");
    this->ui->xueli->setText("");
    this->ui->birth->setText("");
}

void person::on_pushButtoninsert_clicked()
{
    QString id=ui->id->text();
    QString xingming=ui->xingming->text();
    QString xingbie=ui->sex->currentText();
    QString minzu=ui->minzu->text();
    QString zuji=ui->zuji->text();
    QString birth=ui->birth->text();
    QString bornplace=ui->bornplace->text();
    QString liveplace=ui->liveplace->text();
    QString xueli=ui->xueli->text();
    if(id!=NULL && xingming!=NULL && xingbie!=NULL && minzu!=NULL
            && zuji!=NULL && birth!=NULL && bornplace!=NULL
            && liveplace!=NULL && xueli!=NULL)
    {
        QSqlQuery sql1;
        sql1.prepare("INSERT INTO person values('"+id+"','"+xingming+"','"+xingbie+"','"+minzu+"','"+zuji+"','"+birth+"','"+bornplace+"','"+liveplace+"','"+xueli+"')");
        if(sql1.exec())
        {
            QMessageBox::about(NULL,"提示","添加成功");
            search();
        }
        else
        {
            QMessageBox::about(NULL,"提示","个人信息已存在");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","信息不全");
    }
}

void person::on_pushButtondelete_clicked()
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
            QMessageBox change;
            change.setText("确定删除?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Cancel);
            if(change.exec()==QMessageBox::Yes)
            {
            cmd =QString("delete from person where id = %1").arg(id);
            query.exec(cmd);
            if(!query.isActive())
            {
                QMessageBox::about(this,"提示","删除数据失败!");
            }
            else
            {
                    QMessageBox::about(this,"提示","删除数据成功!");
                   search();
            }
            }

        }
}

void person::on_pushButtonchange_clicked()
{
    QString id=ui->id->text();
    QString xingming=ui->xingming->text();
    QString xingbie=ui->sex->currentText();
    QString minzu=ui->minzu->text();
    QString zuji=ui->zuji->text();
    QString birth=ui->birth->text();
    QString bornplace=ui->bornplace->text();
    QString liveplace=ui->liveplace->text();
    QString xueli=ui->xueli->text();
    QSqlQuery sql1;
    sql1.prepare("update person set name='"+xingming+"',sex='"+xingbie+"',nation='"+minzu+"',province='"+zuji+"',birthdata='"+birth+"',birthplace='"+bornplace+"',liveplace='"+liveplace+"',education='"+xueli+"' where id = '"+id+"'");
    if(id!=NULL && xingming!=NULL && xingbie!=NULL && minzu!=NULL
            && zuji!=NULL && birth!=NULL && bornplace!=NULL
            && liveplace!=NULL && xueli!=NULL)
    {if(sql1.exec())
    {
        QMessageBox::about(NULL,"提示","更改成功");
        search();
    }
        else
        {
          QMessageBox::about(NULL,"错误","身份证号不存在");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","请填写完整信息");
    }
}

void person::on_tableView_clicked(const QModelIndex &index)
{
    int num=index.row();
    QAbstractItemModel *model = ui->tableView->model();
    //QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndex index1=model->index(num,0,QModelIndex());
    QString str1= index1.data().toString();
    this->ui->id->setText(str1);
    index1=model->index(num,1,QModelIndex());
    str1= index1.data().toString();
    this->ui->xingming->setText(str1);
    index1=model->index(num,2,QModelIndex());
    str1= index1.data().toString();
    this->ui->sex->setCurrentText(str1);
    index1=model->index(num,3,QModelIndex());
    str1= index1.data().toString();
    this->ui->minzu->setText(str1);
    index1=model->index(num,4,QModelIndex());
    str1= index1.data().toString();
    this->ui->zuji->setText(str1);
    index1=model->index(num,5,QModelIndex());
    QDateTime timme= index1.data().toDateTime();
    str1= timme.toString("yyyy-MM-dd");
    this->ui->birth->setText(str1);

    index1=model->index(num,6,QModelIndex());
    str1= index1.data().toString();
    this->ui->bornplace->setText(str1);

    index1=model->index(num,7,QModelIndex());
    str1= index1.data().toString();
    this->ui->liveplace->setText(str1);

    index1=model->index(num,8,QModelIndex());
    str1= index1.data().toString();
    this->ui->xueli->setText(str1);
}

void person::on_pushButtonsearch_clicked()
{
    QSqlQueryModel *model2=new QSqlQueryModel;

    QString id=ui->id->text()==NULL?" like '%' " :" = '"+ui->id->text()+"'";
    QString xingming="like '%"+ui->xingming->text()+"%'";;
    QString xingbie=ui->sex->currentText()==NULL?" like '%' " :" = '"+ ui->sex->currentText() +"'";
    QString minzu=ui->minzu->text()==NULL?" like '%' " :" = '"+ui->minzu->text() +"'";
    QString zuji=ui->zuji->text()==NULL?" like '%' " :" = '"+ui->zuji->text()+"'";

    QString birth="like '"+ ui->birth->text()+"%'";

    QString bornplace=ui->bornplace->text()==NULL?" like '%' " :" = '"+ui->bornplace->text() +"'";
    QString liveplace=ui->liveplace->text()==NULL?" like '%' " :" = '"+ ui->liveplace->text()+"'";
    QString xueli=ui->xueli->text()==NULL?" like '%' " :" = '"+ ui->xueli->text()+"'";
    QString sql1;
    sql1="SELECT ID as 身份证号,name as 姓名,sex as 性别,nation as 民族,province as 祖籍,birthdata as 出生日,birthplace as 出生地,liveplace as 现居地,education as 学历 from person where id "+id+" and sex "+xingbie+" and name "+xingming+" and nation "+minzu+" and province "+zuji+" and birthdata "+birth+" and birthplace "+bornplace+" and  liveplace "+liveplace+" and Education "+xueli+" ";
    model2->setQuery(sql1);
    //qDebug()<<sql1;
    ui->tableView->setModel(model2);
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
    if(model2->rowCount()>0)
    {
        QMessageBox::about(NULL,"提示","查询成功");
    }
    else
    {
        QMessageBox::about(NULL,"提示","没有查询到信息");
    }
}

void person::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        search();
        this->ui->id->setText("");
        this->ui->sex->setCurrentIndex(0);
        this->ui->xingming->setText("");
        this->ui->minzu->setText("");
        this->ui->zuji->setText("");
        this->ui->bornplace->setText("");
        this->ui->liveplace->setText("");
        this->ui->xueli->setText("");
        this->ui->birth->setText("");
    }
}
