#include "PainterWidget.h"
#include <QRgb>

#include <iostream>



PainterWidget::PainterWidget(Controller* _controller):
    controller(_controller), track(false), lastx(-1), lasty(-1)
{
    setFocusPolicy(Qt::StrongFocus);
}


PainterWidget::~PainterWidget()
{
}

void PainterWidget::setPixel(int x, int y, QRgb color)
{
    if(image.width() > x && image.height() > y && x >= 0 && y >= 0)
        image.setPixel(x, y, color);
}

void PainterWidget::clear()
{
    image.fill(Qt::white);
    update();
}

void PainterWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.drawImage(0, 0, image);
}

void PainterWidget::resizeEvent(QResizeEvent*)
{
    image = QImage(this->size(), QImage::Format_RGB888);
    clear();
    controller->resize();
    controller->update();
}

void PainterWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Up:
            controller->rotate(UP);
            break;
        case Qt::Key_Down:
            controller->rotate(DOWN);
            break;
        case Qt::Key_Left:
            controller->rotate(LEFT);
            break;
        case Qt::Key_Right:
            controller->rotate(RIGHT);
            break;
        case Qt::Key_H:
            controller->translate(LEFT);
            break;
        case Qt::Key_W:
            controller->translate(UP);
            break;
        case Qt::Key_S:
            controller->translate(DOWN);
            break;
        case Qt::Key_L:
            controller->translate(RIGHT);
            break;
        case Qt::Key_PageUp:
            controller->scale(true);
            break;
        case Qt::Key_PageDown:
            controller->scale(false);
            break;
        case Qt::Key_Escape:
            controller->reset();
            break;
        case Qt::Key_Space:
            track = track ? false : true;
            lastx = -1; lasty = -1;
            setMouseTracking(track);
            break;
        default:
            return;
    }
    controller->update();
}

void PainterWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(lastx == -1 || lasty == -1)
    {
        lastx = event->x();
        lasty = event->y();
    }
    else
    {
        lastx > event->x() ? controller->rotate(RIGHT) : controller->rotate(LEFT);
        lasty > event->y() ? controller->rotate(DOWN) : controller->rotate(UP);
        lastx = event->x();
        lasty = event->y();
        controller->update();
    }
}


void PainterWidget::paint()
{
    update();
}

int PainterWidget::getWidth()
{
    return size().height();
}

int PainterWidget::getHeight()
{
    return size().width();
}

unsigned int PainterWidget::getColor(int x, int y)
{
    return image.pixel(x, y);
}
