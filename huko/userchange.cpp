#include "userchange.h"
#include "ui_userchange.h"
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
#include <QDebug>
#include<QSqlTableModel>
#include<QKeyEvent>
userchange::userchange(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userchange)
{
    ui->setupUi(this);
        this->setWindowTitle("管理员信息");
    search();
}

userchange::~userchange()
{
    delete ui;
}
void userchange::search()
{
    /*QSqlQueryModel *model1=new QSqlQueryModel;
    QString sql1;
    sql1="SELECT username as 管理员用户名,password as 密码,phone as 手机号 from operator;";
    model1->setQuery(sql1);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);

    ui->tableView->setColumnWidth(2,100);
    ui->tableView->setModel(model1);
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
    */
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("operator");
    ui->tableView->setModel(model);
    model->select();
    QStringList tables;
    tables << "管理员用户名" << "密码" << "手机号";
    for(int i = 0 ; i < tables.count(); i++)
        model->setHeaderData(i,Qt::Horizontal,tables[i]);//设置显示框表头显示
    //model->setSort(0,Qt::AscendingOrder);//设置按照第0列升序排序，DescendingOrder降序
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置单元格不可编辑
    ui->tableView->horizontalHeader()->setStretchLastSection(true);//设置最后一列填充后面表格
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,100);//设置列宽
    ui->tableView->setColumnWidth(2,100);//设置列宽
    ui->tableView->setAlternatingRowColors(true); // 隔行变色
    ui->tableView->setPalette(QPalette(Qt::lightGray)); // 设置隔行变色的颜色  gray灰色
    ui->tableView->setStyleSheet("QHeaderView::section{background:white;color: black;}");
}
void userchange::on_pushButtoninsert_clicked()
{
     QSqlQuery sql1,sql2;
     sql2.prepare("select count(*) from operator where username=?");
     sql2.addBindValue(this->ui->lineEdituser->text());
     sql2.exec();
     sql1.prepare("insert into operator values(?,?,?)");
     sql1.addBindValue(this->ui->lineEdituser->text());
     sql1.addBindValue(this->ui->lineEditpass->text());
     sql1.addBindValue(this->ui->lineEditphone->text());
     if(sql2.next()&&sql2.value(0)>0)
     {
        QMessageBox::about(NULL,"错误","用户名已被使用");
     }
     else
     {
         if(this->ui->lineEditpass->text()!=NULL)
         {
             sql1.exec();
             QMessageBox::about(NULL,"提示","添加成功");
         }
         else if(this->ui->lineEdituser->text()!=NULL)
         {
            QMessageBox::about(NULL,"错误","密码不可为空");
         }
     }
     search();
}

void userchange::on_pushButtondelete_clicked()
{
    QString username=this->ui->lineEdituser->text();
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
            QMessageBox change;
            change.setText("确定删除?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Cancel);
            if(change.exec()==QMessageBox::Yes)
            {
                QSqlQuery sql1("delete from operator where username='"+username+"'");
                QMessageBox::about(NULL,"提示","删除成功");
                search();
                this->ui->lineEditpass->setText("");
                this->ui->lineEdituser->setText("");
                this->ui->lineEditphone->setText("");
            }
        }
}

void userchange::on_pushButtonchange_clicked()
{
    QString username=this->ui->lineEdituser->text();
    QString password=this->ui->lineEditpass->text();
    QString phone=this->ui->lineEditphone->text();
    if(username!=NULL && password!=NULL)
    {
        QSqlQuery sql1("select count(*) from operator where username='"+username+"'");
        sql1.exec();
        if(sql1.next()&&sql1.value(0)!=0)
        {
            QMessageBox change;
            change.setText("确定更改?");
            change.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
            change.setDefaultButton(QMessageBox::Cancel);
            if(change.exec()==QMessageBox::Yes)
            {
                QSqlQuery sql1("update operator set password='"+password+"',phone='"+phone+"' where username='"+username+"'");
                QMessageBox::about(NULL,"提示","更改成功");
                search();
            }
        }
        else
        {
            QMessageBox::about(NULL,"错误","用户名不存在");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","用户名和密码不能为空");
    }
}

void userchange::on_pushButtonsearch_clicked()
{
    QString username=this->ui->lineEdituser->text();
    QString phone=this->ui->lineEditphone->text();
    if(username!=NULL && phone!=NULL)
    {
        QString sql1="SELECT username as 管理员用户名,password as 密码,phone as 手机号 from operator where username='"+username+"' and phone='"+phone+"' ";
        QSqlQueryModel *model1=new QSqlQueryModel;
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        if(model1->rowCount()==0)
        {
            QMessageBox::about(NULL,"错误","没有查询到信息");
        }
        else
        {
            QMessageBox::about(NULL,"提示","查询成功");
        }
    }
    else if(username!=NULL)
    {
        QString sql1="SELECT username as 管理员用户名,password as 密码,phone as 手机号 from operator where username='"+username+"' ";
        QSqlQueryModel *model1=new QSqlQueryModel;
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        if(model1->rowCount()==0)
        {
            QMessageBox::about(NULL,"错误","没有查询到信息");
        }
        else
        {
            QMessageBox::about(NULL,"提示","查询成功");
        }
    }
    else if(phone!=NULL)
    {
        QString sql1="SELECT username as 管理员用户名,password as 密码,phone as 手机号 from operator where phone='"+phone+"' ";
        QSqlQueryModel *model1=new QSqlQueryModel;
        model1->setQuery(sql1);
        ui->tableView->setModel(model1);
        if(model1->rowCount()==0)
        {
            QMessageBox::about(NULL,"错误","没有查询到信息");
        }
        else
        {
            QMessageBox::about(NULL,"提示","查询成功");
        }
    }
    else
    {
        QMessageBox::about(NULL,"错误","用户名或电话不能为空");
    }
}

void userchange::on_pushButton_clicked()
{
    close();
}

void userchange::on_pushButton_2_clicked()
{
    search();
    this->ui->lineEdituser->setText("");
        this->ui->lineEditpass->setText("");
        this->ui->lineEditphone->setText("");
}

void userchange::on_tableView_pressed(const QModelIndex &index)
{
    int num=index.row();
    QAbstractItemModel *model = ui->tableView->model();
    //QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndex index1=model->index(num,0,QModelIndex());
    QString str1= index1.data().toString();
    this->ui->lineEdituser->setText(str1);

    index1=model->index(num,1,QModelIndex());
    str1= index1.data().toString();
    this->ui->lineEditpass->setText(str1);

    index1=model->index(num,2,QModelIndex());
    str1= index1.data().toString();
    this->ui->lineEditphone->setText(str1);
}

void userchange::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        search();
        this->ui->lineEdituser->setText("");
        this->ui->lineEditpass->setText("");
        this->ui->lineEditphone->setText("");
    }
}

