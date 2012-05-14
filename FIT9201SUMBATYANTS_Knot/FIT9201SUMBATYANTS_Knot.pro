QT       += core gui

TARGET = FIT9201SUMBATYANTS_Knot
TEMPLATE = app


SOURCES += main.cpp\
           PainterWidget.cpp \
           Model.cpp \
           Controller.cpp \
           ViewKnot.cpp \
           Vector.cpp \
           Camera.cpp \
           Line.cpp \
           Bezier.cpp \
           Knot.cpp

HEADERS  += View.h \
            PainterWidget.h \
            Model.h \
            Controller.h \
            ViewKnot.h \
            Point.h \
            Vector.h \
            Camera.h \
            Line.h \
            Bezier.h \
            Knot.h

FORMS    += MainWindow.ui
