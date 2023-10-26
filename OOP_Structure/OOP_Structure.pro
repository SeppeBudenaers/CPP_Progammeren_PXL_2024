TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        chesspiece.cpp \
        king.cpp \
        main.cpp \
        pawn.cpp

HEADERS += \
    chesspiece.h \
    king.h \
    pawn.h
