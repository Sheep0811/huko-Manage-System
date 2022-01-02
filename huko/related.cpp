#include "related.h"
#include "ui_related.h"
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
related::related(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::related)
{
    ui->setupUi(this);
    this->setWindowTitle("人口关系信息");
    search();
    showtime();
}

related::~related()
{
    delete ui;
}
void related::showtime()
{
    QDateTime curDateTime=QDateTime::currentDateTime();
    this->ui->date->setText(curDateTime.toString("yyyy-MM-dd"));
}
void related::search()
{
    /*QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    sql1="SELECT Hno as 户籍号,ID as 身份证号,name as 姓名,relat as 户主或与户主关系,indate as 迁入时间,wherein as 迁入地 from relation";

    model1->setQuery(sql1);
    ui->tableView->setModel(model1);*/
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("relation");
    ui->tableView->setModel(model);
    model->select();
    QStringList tables;
    tables << "户籍号" << "身份证号" << "姓名"<< "户主或与户主关系" << "迁入时间" << "迁入地";
    for(int i = 0 ; i < tables.count(); i++)
        model->setHeaderData(i,Qt::Horizontal,tables[i]);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,130);
    ui->tableView->setColumnWidth(4,150);
    ui->tableView->setColumnWidth(5,100);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->hno->setText("");
    this->ui->id->setText("");
    this->ui->relations->setText("");
    this->ui->name->setText("");
    this->ui->date->setText("");
    this->ui->wherein->setText("");
}

void related::on_pushButton_clicked()
{
    close();
    showtime();
}

void related::on_pushButtoninsert_clicked()
{
    QString hhno=this->ui->hno->text();
    QString iid=this->ui->id->text();
    QString rrelat=this->ui->relations->text();
    QString nname=this->ui->name->text();
    QString ddate=this->ui->date->text();
    QString wwherein=this->ui->wherein->text();
    if(hhno!=NULL && iid!=NULL && rrelat!=NULL && nname!=NULL)
    {
        QSqlQuery sql1;
        sql1.prepare("INSERT INTO relation values('"+hhno+"','"+iid+"','"+nname+"','"+rrelat+"','"+ddate+"','"+wwherein+"')");
        if(sql1.exec())
        {
            QMessageBox::about(NULL,"提示","添加成功");
            search();
        }
        else
        {
            QMessageBox::about(NULL,"提示","个人信息不存在或已添加");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","信息不全");
    }
}

void related::on_pushButtondelete_clicked()
{
    QString id;
        int rowToDel;
        QMap<int, int> rowMap;

        QAbstractItemModel *model = ui->tableView->model();
        QItemSelectionModel *selections = ui->tableView->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        foreach (QModelIndex index, selected)
        {

            rowMap.insert(index.row(), 1);
        }

        QMapIterator<int, int> rowMapIterator(rowMap);
        rowMapIterator.toBack();
        while (rowMapIterator.hasPrevious())
        {
            rowMapIterator.previous();
            rowToDel = rowMapIterator.key();
            QModelIndex index=model->index(rowToDel,1);//rowNum,columnNum为行列号
            id=index.sibling(rowToDel,1).data().toString();
            QSqlQuery query;
            QString cmd;
            //qDebug()<<id;
            cmd =QString("delete from relation where id = %1").arg(id);
            QMessageBox change;
            change.setText("确定删除?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Cancel);
            if(change.exec()==QMessageBox::Yes)
            {
            query.exec(cmd);
            if(!query.isActive())
            {
                QMessageBox::about(this,"错误","删除数据失败!\n"+query.lastError().text());
            }
            else
            {
                    QMessageBox::about(this,"提示","删除数据成功!");
                   search();
            }    

        }

}
}

void related::on_pushButton_2_clicked()
{
    search();
}

void related::on_pushButtonchange_clicked()
{
    QString hhno=this->ui->hno->text();
    QString iid=this->ui->id->text();
    QString rrelat=this->ui->relations->text();
    QString nname=this->ui->name->text();
    QString ddate=this->ui->date->text();
    QString wwherein=this->ui->wherein->text();
        QString id;
            int rowToDel;
            QMap<int, int> rowMap;

            QAbstractItemModel *model = ui->tableView->model();
            QItemSelectionModel *selections = ui->tableView->selectionModel();
            QModelIndexList selected = selections->selectedIndexes();
            foreach (QModelIndex index, selected)
            {

                rowMap.insert(index.row(), 1);
            }

            QMapIterator<int, int> rowMapIterator(rowMap);
            rowMapIterator.toBack();
            while (rowMapIterator.hasPrevious())
            {
                rowMapIterator.previous();
                rowToDel = rowMapIterator.key();
                QModelIndex index=model->index(rowToDel,1);//rowNum,columnNum为行列号
                id=index.sibling(rowToDel,1).data().toString();
                QSqlQuery query,query1,query2,query3,query4;
                QString cmd;
                //qDebug()<<id;
                if(hhno!=NULL)
                {cmd =QString("update relation set hno='"+hhno+"' where id = %1").arg(iid);
                query.exec(cmd);}
                if(nname!=NULL)
                {cmd =QString("update relation set name='"+nname+"' where id = %1").arg(iid);
                query4.exec(cmd);}
                if(rrelat!=NULL)
                {cmd =QString("update relation set relat='"+rrelat+"' where id = %1").arg(iid);
                query1.exec(cmd);}
                if(ddate!=NULL)
                {cmd =QString("update relation set indate='"+ddate+"' where id = %1").arg(iid);
                query2.exec(cmd);}
                cmd =QString("update relation set wherein='"+wwherein+"' where id = %1").arg(iid);
                query3.exec(cmd);
                if(!query4.isActive())
                {
                    QMessageBox::about(this,"错误","更新数据失败!\n"+query4.lastError().text());
                }
                else
                {
                        QMessageBox::about(this,"提示","更新数据成功!");
                       search();
                }

            }
}

void related::on_pushButtonsearch_clicked()
{
    QSqlQueryModel *model2=new QSqlQueryModel;
    QString hhno=this->ui->hno->text()==NULL?" like '%' " :" = '"+this->ui->hno->text()+"'";
    QString iid=this->ui->id->text()==NULL?" like '%' " :" = '"+this->ui->id->text()+"'";
    QString rrelat=this->ui->relations->text()==NULL?" like '%' " : " = '" + this->ui->relations->text()+"'";
    QString nname=this->ui->name->text()==NULL?" like '%' " : " = '"+this->ui->name->text()+"'";
    QString ddate=this->ui->date->text()==NULL?" like '%' " : " = '"+ this->ui->date->text()+"'";
    QString wwherein=this->ui->wherein->text()==NULL?" like '%' " : " = '"+this->ui->wherein->text()+"'";
    QString sql1;
    if(wwherein==" like '%' ")
    sql1="SELECT Hno as 户籍号,ID as 身份证号,name as 姓名,relat as 户主或与户主关系,indate as 迁入时间,wherein as 迁入地 from relation where hno "+hhno+" and id "+iid+" and relat "+rrelat+" and indate "+ddate+"";
    else
    sql1="SELECT Hno as 户籍号,ID as 身份证号,name as 姓名,relat as 户主或与户主关系,indate as 迁入时间,wherein as 迁入地 from relation where hno "+hhno+" and id "+iid+" and relat "+rrelat+" and indate "+ddate+" and wherein "+wwherein+" ";
    //qDebug()<<sql1;
    model2->setQuery(sql1);
    ui->tableView->setModel(model2);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,90);
    ui->tableView->setColumnWidth(2,70);
    ui->tableView->setColumnWidth(3,130);
    ui->tableView->setColumnWidth(4,150);
    ui->tableView->setColumnWidth(5,100);
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

void related::on_tableView_pressed(const QModelIndex &index)
{
    int num=index.row();
    QAbstractItemModel *model = ui->tableView->model();
    //QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndex index1=model->index(num,0,QModelIndex());
    QString str1= index1.data().toString();
    this->ui->hno->setText(str1);

    index1=model->index(num,1,QModelIndex());
    str1= index1.data().toString();
    this->ui->id->setText(str1);

    index1=model->index(num,2,QModelIndex());
    str1= index1.data().toString();
    this->ui->name->setText(str1);

    index1=model->index(num,3,QModelIndex());
    str1= index1.data().toString();
    this->ui->relations->setText(str1);

    index1=model->index(num,4,QModelIndex());
    QDateTime timme= index1.data().toDateTime();
    str1= timme.toString("yyyy-MM-dd");
    this->ui->date->setText(str1);

    index1=model->index(num,5,QModelIndex());
    str1= index1.data().toString();
    this->ui->wherein->setText(str1);
}

void related::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        search();
    }
}
