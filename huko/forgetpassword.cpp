#include "forgetpassword.h"
#include "ui_forgetpassword.h"

forgetpassword::forgetpassword(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forgetpassword)
{
    ui->setupUi(this);
}

forgetpassword::~forgetpassword()
{
    delete ui;
}

void forgetpassword::on_pushButton_quit_clicked()
{
    close();
}
