#include "PainterWidget.h"
#include <iostream>
namespace
{
    const unsigned int BGCOLOR = 0x242424;
}

PainterWidget::PainterWidget(ControllerSin* _controller):
    controller(_controller)
{}

PainterWidget::~PainterWidget()
{
}

void PainterWidget::setPixel(int x, int y, uint color)
{
    image.setPixel(x, y, color);
}

void PainterWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    image = QImage(this->size(), QImage::Format_RGB888);
    image.fill(BGCOLOR);
    controller->update();
    painter.drawImage(0, 0, image);
}

void PainterWidget::paint()
{
    update();
}

int PainterWidget::getWidth()
{
    return (this->size()).height();
}

int PainterWidget::getHeight()
{
    return (this->size()).width();
}
