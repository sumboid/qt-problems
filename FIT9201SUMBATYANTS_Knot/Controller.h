#pragma once
#include <QObject>
#include "Model.h"
#include "View.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(View* view);
    ~Controller();

public slots:
    void update();
    void resize();

private:
    Model* model;
};
