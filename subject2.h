#ifndef SUBJECT2_H
#define SUBJECT2_H

#include <QWidget>

namespace Ui {
class subject2;
}

class subject2 : public QWidget
{
    Q_OBJECT

public:
    explicit subject2(QWidget *parent = nullptr);
    ~subject2();

private:
    Ui::subject2 *ui;
};

#endif // SUBJECT2_H
