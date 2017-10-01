QT += core
QT -= gui  
QT += network

CONFIG += c++11     
CONFIG += console  
CONFIG += testcase   
QMAKE_CXXFLAGS += -std=c++11

TARGET = tests
TEMPLATE = app

SOURCES += main.cpp
HEADERS += catch.hpp

