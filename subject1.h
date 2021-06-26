#ifndef SUBJECT1_H
#define SUBJECT1_H

#include <QWidget>
#include <QDrag>

namespace Ui {
class subject1;
}

class subject1 : public QWidget
{
    Q_OBJECT

public:
    explicit subject1(QWidget *parent = nullptr);
    ~subject1();

    void setCounter(int value);//метод установки значения счетчика
    int getCounter();//метод извлечения значения счетчика
    void setId(int data);//метод установки идентификатора/типа

    /*метод извлечения идентификатора/типа
    например нужно для того чтобы получать значение m_id для проверки
    тождественност*/
    int getId();

    void setMimeData(QString data); /*с помощью него помещаем в буфер данные любого типа*/

    void setRowColumn(int row, int col);

    //метод возвращает указатель на объект QDrag, который в дальнейшем будет использоваться в mouseMoveEvent
    QDrag *makeDrad();
protected:
    //Drag
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    Ui::subject1 *ui;
    QPoint m_dragStart;
    QPixmap m_pixmap;
    QString m_mimeData;
    int m_row;
    int m_col;
    int m_id;

};

#endif // SUBJECT1_H
