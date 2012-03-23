#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>

class Controller: public QObject
{
    Q_OBJECT
public:
    virtual ~Controller() {}

public slots:
    virtual void update() = 0;
    virtual void drawFunction() = 0;
    virtual void drawAxis() = 0;
    virtual void clear() = 0;
};
#endif // CONTROLLER_H
