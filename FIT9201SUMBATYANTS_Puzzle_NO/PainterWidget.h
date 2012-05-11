#pragma once
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include "Controller.h"

class PainterWidget : public QWidget
{
    Q_OBJECT
public:
    PainterWidget(Controller* controller);
    ~PainterWidget();
    void paint();
    void setPixel(int x, int y, unsigned int color);
    void clear();
    int getWidth();
    int getHeight();
    unsigned int getColor(int x, int y);
protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
private:
    Controller* controller;
    QImage image;
};
