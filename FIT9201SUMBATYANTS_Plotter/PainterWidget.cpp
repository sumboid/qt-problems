#include "PainterWidget.h"
#include <QRgb>

#include <iostream>

PainterWidget::PainterWidget(Controller* _controller):
    controller(_controller)
{}

PainterWidget::~PainterWidget()
{
}

void PainterWidget::setPixel(int x, int y, QRgb color)
{
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
    controller->update();
}

void PainterWidget::mouseMoveEvent(QMouseEvent *event)
{
}

void PainterWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        std::cout << "Left" << std::endl;
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
