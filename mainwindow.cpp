#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "centralwidget.h"
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_widget = nullptr;
    connect(ui->save,SIGNAL(triggered()),this,SLOT(saveTable()));
    connect(ui->load,SIGNAL(triggered()),this,SLOT(loadTable()));

   /*Подключаем базу данных*/
   db = QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("C:/QtTask/database.db3");
   db.open();

}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::create()
{
    if(m_widget == nullptr){
        m_widget = new centralwidget();
    }
    setCentralWidget(m_widget);
    return true;
}

void MainWindow::saveTable()
{
/*
    qDebug()<<"Save Table";
    QString fileName = QFileDialog::getSaveFileName(this,
                                                   "Save data to file",
                                                    "A572.txt",
                                                    "(*.txt)");

    if(fileName.isEmpty())
        return;
    qDebug()<<"fileName"<<fileName;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream <<1<<";" << 2<<";" <<3<<" \n";
        stream <<3<<";" << 2<<";" <<1;

        file.close();

    }
    else
     qDebug()<<"Can not open file"<<fileName;
*/
    this->m_widget->updateData();

    QVector<DATA> saveData = this->m_widget->getData();

    QString tmp_s;

    QSqlQuery clearTable;
    clearTable.exec("DELETE FROM saves");

    for(int i=0;i<saveData.count();i++)
    {

        QSqlQuery query;
        /*стока в которой будет формироваться запрос для добавления данных в таблицу saves*/
        QString queryStr;

        /*формирование запроса
        указывается что запрос будет содержать вставку в записи в таблицу
        указывается список атрибутов которые будут записываться в таблицу*/

        queryStr = "INSERT INTO \"saves\" (\"row\", \"col\", \"count\", \"id\") VALUES ('";
        /*номер строки преобразовывается в тип данных "строка"*/
        tmp_s.setNum(saveData[i].row);
        /*полученная строка добавляется в запрос*/
        queryStr+=tmp_s;
        queryStr+="', '";
        tmp_s.setNum(saveData[i].col);
        queryStr+=tmp_s;
        queryStr+="', '";
        tmp_s.setNum(saveData[i].count);
        queryStr+=tmp_s;
        queryStr+="', '";
        tmp_s.setNum(saveData[i].id);
        queryStr+=tmp_s;
        /*завершение формирвоание запроса*/
        queryStr+="');";
        query.exec(queryStr); /*выполнение запроса*/
    }
}

void MainWindow::loadTable()
{
    this->m_widget->clearData();
    /*данные сохраняются в таблице
    this->m_widget->updateData();
    данные извлекаются из таблицы
    QVector<DATA> isData = this->m_widget->getData();
    проверка на наличие данных
    if(!isData.empty())
        если данные есть, вектор не пустой - загрузка не нужна и метод loadTable завершает работу
        return;
*/
    QVector<DATA> insertData;

    QString tmp_s;
    bool ok;

    QSqlQuery getSubject;
    getSubject.exec("select id,col,row,count FROM saves");

    while (getSubject.next())
    {
        DATA newData;
        newData.id= getSubject.value(0).toInt(&ok); /*В ok возвращается результат преобразования id в число*/
        newData.col= getSubject.value(1).toInt(&ok);
        newData.row= getSubject.value(2).toInt(&ok);
        newData.count= getSubject.value(3).toInt(&ok);

        insertData.append(newData);
    }

    this->m_widget->setData(insertData);


    /*
    qDebug()<<"laod Table";
    QString fileName = QFileDialog::getOpenFileName(this,
                                                   "Open data to file",
                                                    "(.txt)");
    if(fileName.isEmpty())
        return;
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly)){

        while (!file.atEnd()) {
            QString line = QString::fromUtf8(file.readLine());
            qDebug()<<"line"<<line;
            QStringList tokens = line.split(";");
            qDebug() << "tokens="<<tokens;
        }
    }*/
}

