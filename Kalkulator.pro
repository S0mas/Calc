QT += core
QT -= gui

CONFIG += c++11

TARGET = Kalkulator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    IExpressionTree.cpp

HEADERS += \
    ExpressionTree.h \
    ExpressionNode.h \
    Helper.h \
    IExpressionTree.h
