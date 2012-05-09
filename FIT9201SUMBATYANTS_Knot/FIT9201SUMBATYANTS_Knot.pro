QT       += core gui

TARGET = FIT9201SUMBATYANTS_Knot
TEMPLATE = app


SOURCES += main.cpp\
           PainterWidget.cpp \
           Model.cpp \
           Controller.cpp \
           ViewKnot.cpp

HEADERS  += View.h \
            PainterWidget.h \
            Model.h \
            Controller.h \
            ViewKnot.h \
            Point.h \

FORMS    += MainWindow.ui
