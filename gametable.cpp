#include "gametable.h"
#include <QDebug>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "subject1.h"

gameTable::gameTable()
{
    setAcceptDrops(true);
    //setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
}
void gameTable::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"Mouse clicked";
    QWidget::mouseReleaseEvent(e);
}

void gameTable::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Mouse clicked";
    QWidget::keyPressEvent(event);
}

void gameTable::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse clicked";
    QWidget::mouseDoubleClickEvent(event);
}

void gameTable::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"DragEnterEvent";
    if (event->mimeData()->hasFormat("aplication/subject") ||
            event->mimeData()->hasFormat("aplication/subjectTable") )
    {
        event->acceptProposedAction();
        qDebug()<<"event->acceptProposedAction()";
    }
    else
    {
        event->ignore();
        qDebug()<<"event->ignore()";
    }
}

void gameTable::dropEvent(QDropEvent *event)
{
    qDebug()<<"DropEvent";
    QModelIndex indexCur = indexAt(event->pos());
    if (!indexCur.isValid())
        return;
    qDebug()<<"row to= "<<indexCur.row()<< "col to= "<<indexCur.column();

    if (event->mimeData()->hasFormat("aplication/subject"))
    {
        QByteArray data = event->mimeData()->data("aplication/subject");
        QDataStream in(&data, QIODevice::ReadOnly);
        int row;
        int col;
        int id;
        in >> row >> col>>id;
        qDebug()<<"row from = "<< row << "col from = "<<col <<"id from" <<id;
        handleRightSubject(indexCur, id);
    }

    if (event->mimeData()->hasFormat("aplication/subjectTable"))
    {
        QByteArray data = event->mimeData()->data("aplication/subjectTable");
        QDataStream in(&data, QIODevice::ReadOnly);
        int row;
        int col;
        int id;
        in >> row >> col>>id;

        qDebug()<<"row from = "<< row << "col from = "<<col <<"id from" <<id;

        handlSubjectTable(indexCur.row(), indexCur.column(), row, col);
    }
}

void gameTable::handleRightSubject(QModelIndex indexCur, int id)
{

    auto ptr = cellWidget(indexCur.row(),indexCur.column());
    if (ptr != nullptr)
    {
        qDebug()<<"Widget already used";
        auto sub = static_cast<subject1*>(ptr);
        int cur = sub->getCounter();
        int curId = sub->getId();
        if (curId != id)
            return;
        cur++;
        if(cur>5)
            sub->setCounter(5);
        else
            sub->setCounter(cur);
        if (cellWidget(indexCur.row(),indexCur.column()) != nullptr)
        {
           return;
        }
    }
    qDebug()<<"new Widget";
    subject1 *sub = new subject1();
    sub->setCounter(1);
    sub->setRowColumn(indexCur.row(),indexCur.column());
    sub->setMimeData("aplication/subjectTable");
    sub->setId(id);
    //sub->setPixMap("C:/QtTask/task/gameA572/pict1.jpg");
    setCellWidget(indexCur.row(),indexCur.column(),sub);
    qDebug()<<"widget added";
}

void gameTable::handlSubjectTable(int rowTo, int colTo, int rowFrom, int colFrom)
{

    auto ptrFrom = cellWidget(rowFrom, colFrom);
    if (ptrFrom == nullptr)
    {
        qDebug()<<"error";
    }
    auto subFrom = static_cast<subject1*>(ptrFrom);
    int counterFrom = subFrom->getCounter();
    //int idFrom = subFrom->getId();

    auto ptr = cellWidget(rowTo, colTo);


    if (ptr != nullptr)
    {
        qDebug()<<"Widget already used";

        auto subTo = static_cast<subject1*>(ptr);

        if(subFrom->getId()==subTo->getId())
        {
            /*проверка не копируем ли мы объект в сам себя*/
            if(rowFrom == rowTo && colFrom == colTo)
                return;
            int counterTo = subTo->getCounter();
            /*проверка на то чтобы в ячейке лежало не больше пяти элементов*/
            if((counterFrom + counterTo)>5)
            {
                subTo->setCounter(5);
                subFrom->setCounter(counterFrom + counterTo-5);
            }
            else
            {
                subTo->setCounter(counterFrom + counterTo);
                removeCellWidget(rowFrom, colFrom);
            }
        }
    /* int counterTo = subTo->getCounter();
       int idTo = subTo->getId();
       if (idTo != idFrom)
            return;
       removeCellWidget(rowFrom, colFrom);
       subTo->setCounter(counterFrom + counterTo);
       */
    }

    else
    {
        qDebug()<<"new Widget";
        subject1 *sub = new subject1();
        sub->setCounter(counterFrom);
        sub->setRowColumn(rowTo, colTo);
        sub->setMimeData("aplication/subjectTable");
         sub->setId(subFrom->getId());
        //sub->setPixMap("C:/QtTask/task/gameA572/pict1.jpg");
        setCellWidget(rowTo, colTo,sub);
        removeCellWidget(rowFrom, colFrom);
    }
}

void gameTable::insertObj(int row, int col, int count, int id)
{
    subject1 *sub = new subject1();
    sub->setCounter(count);
    sub->setRowColumn(row,col);
    sub->setMimeData("aplication/subjectTable");
    sub->setId(id);
    //sub->setPixMap("C:/QtTask/task/gameA572/pict1.jpg");
    setCellWidget(row,col,sub);
}
