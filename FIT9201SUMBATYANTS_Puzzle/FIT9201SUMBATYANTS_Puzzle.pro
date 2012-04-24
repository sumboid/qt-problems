QT       += core gui

TARGET = FIT9201SUMBATYANTS_Puzzle
TEMPLATE = app


SOURCES += main.cpp\
           MainWindow.cpp \
           PainterWidget.cpp \
           Model.cpp \
           Controller.cpp \
           ViewPuzzle.cpp \
           Triangle.cpp

HEADERS  += MainWindow.h \
            View.h \
            PainterWidget.h \
            Model.h \
            Controller.h \
            ViewPuzzle.h \
            Triangle.h \
            Point.h \
            Filter.h

FORMS    += MainWindow.ui

OTHER_FILES +=

RESOURCES += resources.qrc
