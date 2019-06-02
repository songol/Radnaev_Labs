#ifndef QPAINTERWID_H
#define QPAINTERWID_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>


class qpainterwid : public QWidget
{
    Q_OBJECT

public:
    qpainterwid(QWidget *parent = 0);
    ~qpainterwid();
private:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTERWID_H
