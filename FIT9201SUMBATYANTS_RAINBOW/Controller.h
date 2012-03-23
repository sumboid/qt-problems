#pragma once
#include <QObject>
#include <QTimer>
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
    void start();
    void stop();
    void clear();
    void setWidth(const int);
    void setHeight(const int);
    void setSpeed(const int);

private:
    Model* model;
    QTimer timer;

};
