#include <QApplication>

#include "View.h"
#include "ViewSin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ViewSin view;
    return a.exec();
}
