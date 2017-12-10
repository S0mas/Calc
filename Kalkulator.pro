QT += core
QT -= gui

CONFIG += c++17

TARGET = Kalkulator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    IExpressionTree.cpp \
    ExpressionTree.cpp \
    CommandValidator.cpp \
    RandomNodeGenerator.cpp \
    KnownOperators.cpp \
    GeneticAlgorithm.cpp \
    RandomTreeGenerator.cpp

HEADERS += \
    ExpressionTree.h \
    ExpressionNode.h \
    Helper.h \
    IExpressionTree.h \
    CommandValidator.h \
    Logger.h \
    ErrorsMsg.h \
    RandomNodeGenerator.h \
    KnownOperators.h \
    GeneticAlgorithm.h \
    RandomTreeGenerator.h
