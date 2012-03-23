#ifndef CONTROLLERSIN_H
#define CONTROLLERSIN_H

#include <QObject>
#include "ModelSin.h"
#include "View.h"

class ControllerSin : public QObject
{
    Q_OBJECT
public:
    ControllerSin(View* view);
    ~ControllerSin();

public slots:
    void update();
    void drawFunction();
    void drawAxis();
    void clear();

private:
    ModelSin* model;

};

#endif // CONTROLLERSIN_H
