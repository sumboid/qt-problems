#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include "ControllerSin.h"

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    PainterWidget(ControllerSin* controller);
    ~PainterWidget();
    void paint();
    void setPixel(int x, int y, uint color);
    int getWidth();
    int getHeight();
protected:
    virtual void paintEvent(QPaintEvent*);
private:
    ControllerSin* controller;
    QImage image;
};

#endif // PAINTERWIDGET_H
