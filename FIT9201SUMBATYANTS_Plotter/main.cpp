#include <QApplication>

#include "ViewPlotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewPlotter view;
    return a.exec();
}
