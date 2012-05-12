#include "PainterWidget.h"
#include <QRgb>

PainterWidget::PainterWidget(Controller* _controller):
    controller(_controller)
{
    setMouseTracking(true);
}


PainterWidget::~PainterWidget()
{
}

void PainterWidget::setPixel(int x, int y, QRgb color)
{
    if(image.width() > x && image.height() > y)
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
    controller->getInfo(event->x(), event->y());
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
    if(image.width() > x && image.height() > y && x >= 0 && y >= 0)
        return image.pixel(x, y);
    else
        return 0x0;
}
