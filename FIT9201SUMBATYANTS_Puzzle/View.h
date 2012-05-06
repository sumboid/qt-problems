#ifndef VIEW_H
#define VIEW_H

class View
{
public:
    virtual ~View() {}

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;
    virtual void paint() = 0;
    virtual void clear() = 0;
    virtual void setPixel(int x, int y, unsigned int color) = 0;
    virtual void invertButton(bool state) = 0;
    virtual unsigned int getColor(int x, int y) = 0;
    virtual void setDial(const int) = 0;
};

#endif // VIEW_H
