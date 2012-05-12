#pragma once
#include <QObject>
#include <QTimer>
#include <QTime>
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
    void setBlend(int);
    void setFilter(int);
    void init();
    void setStep(int);
    void nextStep();
    void getInfo(int, int);
    void resize(int);

private:
    Model* model;
    QTimer timer;
    int step;
    QTime lastTime;

};
