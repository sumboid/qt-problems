#pragma once
#include <QObject>
#include "Model.h"
#include "View.h"
#include "Camera.h"

enum Direction {LEFT, RIGHT, UP, DOWN};
class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(View* view);
    ~Controller();

public slots:
    void update();
    void resize();
public:
    void rotate(Direction);
    void translate(Direction);
    void reset();

private:
    Model* model;
    Camera* camera;
};
