#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <QTableWidget>

class gameTable : public QTableWidget
{
public:
    gameTable();

    void insertObj(int row,int col, int count,int  id);//метод помещающий объект в указанную ячейку
protected:
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void dragEnterEvent (QDragEnterEvent* event) override;
    virtual void dropEvent (QDropEvent* event) override;

private:
    void handleRightSubject(QModelIndex indexCur, int id);
    void handlSubjectTable(int rowTo, int colTo, int rowFrom, int colFrom);
};

#endif // GAMETABLE_H
