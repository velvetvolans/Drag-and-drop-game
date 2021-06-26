#include "subject2.h"
#include "ui_subject2.h"
#include <QPixmap>

subject2::subject2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subject2)
{
    ui->setupUi(this);
    QPixmap pix;
    pix.load("C:/QtTask/task/gameA572/pict2.jpg");
    ui->label->setPixmap(pix);
     setMaximumSize(500,500);
}

subject2::~subject2()
{
    delete ui;
}
