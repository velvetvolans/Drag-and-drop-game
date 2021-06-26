#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "subject1.h"
#include "subject2.h"
#include <QPushButton>
#include "gameTable.h"

namespace Ui {
class centralwidget;
}

struct DATA {
    int id;
    int col;
    int row;
    int count;
};

class centralwidget : public QWidget
{
    Q_OBJECT

public:
    explicit centralwidget(QWidget *parent = nullptr);
    ~centralwidget();
    QVector<DATA> getData(); /*метод возвращающий содержимое вектора data*/

    void setData (QVector <DATA> input);/*устанавливает содержимое m_table*/
    void updateData();/*обновляет содержимое вектора data*/
    void clearData();

public slots:
    void addButtonSlot();
    void removeButtonSlot();

private:
    Ui::centralwidget *ui;
    subject1 m_sub1;
    subject1 m_sub2;
    QPushButton m_but;
    QPushButton m_but1;

    gameTable m_table;

    QVector<DATA> data;
};

#endif // CENTRALWIDGET_H
