#ifndef VIEW_H
#define VIEW_H

#include <QtGui/QApplication>

class View
{
public:
    virtual ~View() {}

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual void paint() = 0;

    virtual void setPixel(int x, int y, uint color) = 0;
};

#endif // VIEW_H
