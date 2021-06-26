#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "centralwidget.h"

/* библиотеки для работы с БД*/
#include"QSqlDatabase"
#include"QSqlDriver"
#include"QSqlQuery"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase db;/*объект для работы с БД*/

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
/*метод инициализирующий m_widget*/
    bool create();
public slots:
    void saveTable();/*слот (функция обработки) сохранения состояния игровой таблицы*/
    void loadTable();/*слот (функция обработки) загрузки состояния игровой таблицы*/


private:
    Ui::MainWindow *ui;
    centralwidget *m_widget;
};
#endif // MAINWINDOW_H
