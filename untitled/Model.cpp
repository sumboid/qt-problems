#include <QPixmap>
#include <QResource>
#include <math.h>
#include <stdlib.h>
#include "Model.h"

#include <iostream>

Model::Model(View* _view): view(_view), angle(0)
{
}

Model::~Model()
{}

void Model::draw() const
{
    QPixmap image(":/puzzle.png");
    QImage img = image.toImage();
    int width = view->getWidth();
    int height = view->getHeight();

    view->clear();
    for(int i = 0; i < img.width(); i++)
        for(int k = 0; k < img.height(); k++)
        {
            int x = static_cast<int>(cos(angle) * static_cast<double>(i) - sin(angle) * static_cast<double>(k));
            int y = static_cast<int>(sin(angle) * static_cast<double>(i) + cos(angle) * static_cast<double>(k));
            x += width / 2 - cos(angle) * img.width() / 2 + sin(angle) * img.height() / 2;
            y += height / 2 - sin(angle) * img.height() / 2 - cos(angle) * img.width() / 2;
            view->setPixel(x, y, img.pixel(i, k));
        }

    view->paint();
}

void Model::setAngle(const double _angle)
{
    angle = _angle;
}

void Model::invertButton(bool state)
{
    view->invertButton(state);
}
