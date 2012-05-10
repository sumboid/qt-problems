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
    void setBlend(const int);
    void setFilter(const int);
    void init();
    void setStep(const int);
    void nextStep();
    void getInfo(const int, const int);

private:
    Model* model;
    QTimer timer;
    int step;

};
