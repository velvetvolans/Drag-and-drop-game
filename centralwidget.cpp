#include "centralwidget.h"
#include "ui_centralwidget.h"
#include "subject1.h"
#include "subject2.h"
#include <QDebug>

centralwidget::centralwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::centralwidget)
{
    ui->setupUi(this);
    m_table.setRowCount(3);
    m_table.setColumnCount(3);
    m_table.setColumnWidth(0,100);
    m_table.setColumnWidth(1,100);
    m_table.setColumnWidth(2,100);
    m_table.setRowHeight(0,100);
    m_table.setRowHeight(1,100);
    m_table.setRowHeight(2,100);

    ui->horizontalLayout_2->addWidget(&m_table);

    m_sub1.setMimeData("aplication/subject");
    m_sub1.setId(0);
    m_sub1.setMinimumSize(100,100);
    ui->verticalLayout->addWidget(&m_sub1);

    m_sub2.setMimeData("aplication/subject");
    m_sub2.setId(1);    
    m_sub2.setMinimumSize(100,100);
    ui->verticalLayout->addWidget(&m_sub2);

/*
    m_but.setText("Add button");
    ui->verticalLayout->addWidget(&m_but);
    connect(&m_but,SIGNAL(clicked()),this,SLOT(addButtonSlot()));

    m_but1.setText("Remove button");
    ui->verticalLayout->addWidget(&m_but1);
    connect(&m_but1,SIGNAL(clicked()),this,SLOT(removeButtonSlot()));
*/
}

centralwidget::~centralwidget()
{
    delete ui;
}

QVector<DATA> centralwidget::getData()
{
 //   QVector<DATA> data;
    return data;
}

void centralwidget::updateData()/*(QVector<DATA> data)*/
{
    data.clear();
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            DATA newDATA;
            auto ptrFrom = this->m_table.cellWidget(i, j);
            if (ptrFrom == nullptr)
                continue;
            auto subFrom = static_cast<subject1*>(ptrFrom);
            newDATA.count = subFrom->getCounter();
            newDATA.id = subFrom->getId();
            newDATA.col=j;
            newDATA.row=i;
            this->data.append(newDATA);
        }
}

void centralwidget::clearData()
{
    this->data.clear();
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
        {
            auto ptrFrom = this->m_table.cellWidget(i, j);
            if (ptrFrom == nullptr)
                continue;
            else
            {
                delete ptrFrom;
            }
        }
}

void centralwidget::addButtonSlot()
{
  auto ptr = m_table.cellWidget(0,0);
  if (ptr == nullptr) {
     qDebug()<<"no widget";
     subject1 *subjInTable = new subject1();
     subjInTable->setCounter(1);
     m_table.setCellWidget(0,0,subjInTable);
  } else {
     qDebug()<<"yes widget";
     auto sub = static_cast<subject1*>(ptr);
     int cur = sub->getCounter();
     cur++;
     sub->setCounter(cur);
  }
/*
  qDebug()<<"AddButtonSlot";
  int cur = m_sub1.getCounter();
  qDebug()<<"cur"<<cur;
    cur++;
  qDebug()<<"after cur"<<cur;
  m_sub1.setCounter(cur);
  cur = m_sub1.getCounter();
  qDebug()<<"done cur"<<cur;
 */
}

void centralwidget::removeButtonSlot()
{
    qDebug()<<"AddButtonSlot";
    int cur = m_sub1.getCounter();
    qDebug()<<"cur"<<cur;
    cur--;
    qDebug()<<"after cur"<<cur;
    m_sub1.setCounter(cur);
    cur = m_sub1.getCounter();
    qDebug()<<"done cur"<<cur;
}

void centralwidget::setData(QVector<DATA> input)
{
    for(int i=0;i<input.count();i++)
    {
        /*handlSubjectTable(int rowTo, int colTo, int rowFrom, int colFrom)*/
        this->m_table.insertObj(input[i].row,input[i].col,input[i].count,input[i].id);
    }
}
