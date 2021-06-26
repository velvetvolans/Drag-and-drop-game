#include "subject1.h"
#include "ui_subject1.h"
#include <QPixmap>
#include <QVariant>
#include <QDebug>
#include <QMouseEvent>
#include <QMimeData>
#include <QPainter>

subject1::subject1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::subject1)
{
    ui->setupUi(this);


    setMaximumSize(500,500);
    //setCounter(0);
    setRowColumn(-1,-1);
}

subject1::~subject1()
{
    delete ui;
}

void subject1::setCounter(int value)
{
    QVariant var(value);
    ui->counter->setText(var.toString());
}

int subject1::getCounter()
{
    QVariant var(ui->counter->text());
    return var.toInt();
}

void subject1::setMimeData(QString data)
{
    m_mimeData = data;
}

void subject1::setRowColumn(int row, int col)
{
    m_row = row;
    m_col = col;
}

void subject1::setId(int data)
{
    m_id = data;
    if (m_id ==0 )
        m_pixmap.load("C:/QtTask/task/gameA572/pict1.jpg");
    else if (m_id ==1)
        m_pixmap.load("C:/QtTask/task/gameA572/pict2.jpg");
    else
        m_pixmap.load("");

}

int subject1::getId()
{
    return m_id;
}

QDrag *subject1::makeDrad()
{
    QDrag *drag = new QDrag(this);
    QByteArray itemData;
    QDataStream stream(&itemData, QIODevice::WriteOnly);
    stream << m_row<<m_col<<m_id;
    QMimeData *mimeData = new QMimeData; /*размещение данных различных типов при drag*/
    mimeData->setData(m_mimeData,itemData);
    drag->setMimeData(mimeData);
    drag->setPixmap(m_pixmap.scaled(size(),Qt::KeepAspectRatio) );
    return drag;
}

void subject1::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"MousePressEvent";
    /*запоминаем откуда начали тащить объект*/
    m_dragStart = event->pos();
    QWidget::mousePressEvent(event);
}

void subject1::mouseMoveEvent(QMouseEvent *event)
{
    qDebug()<<"MouseMoveEvent";
    if ((event->buttons() & Qt::LeftButton)
            && QApplication::startDragDistance() <= (event->pos() - m_dragStart ).manhattanLength())
             makeDrad()->exec(Qt::MoveAction);
    QWidget::mouseMoveEvent(event);
}

void subject1::paintEvent(QPaintEvent *event)
{
    qDebug()<<"paintEvent";
    QPainter painter(this);
    if (!m_pixmap.isNull()){

    QSize widgetSize = size();
    QPixmap scaledPixmap = m_pixmap.scaled(widgetSize,Qt::KeepAspectRatio);
    QPoint center((widgetSize.width() - scaledPixmap.width())/2,
                  (widgetSize.height() - scaledPixmap.height())/2);
    painter.drawPixmap(center,scaledPixmap);
    }
    QWidget::paintEvent(event);
}

void subject1::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"Mouse clicked";
    QWidget::mouseReleaseEvent(e);
}

void subject1::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Mouse clicked";
    QWidget::keyPressEvent(event);
}

void subject1::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse clicked";
    QWidget::mouseDoubleClickEvent(event);
}
