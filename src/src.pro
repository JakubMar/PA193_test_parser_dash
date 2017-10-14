CONFIG += c++11     
CONFIG += console  
QMAKE_CXXFLAGS += -std=c++11

TARGET = parser
TEMPLATE = app

include(src.pri)

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug/src
} else {
    DESTDIR = ../build/release/src
}

OBJECTS_DIR = $$DESTDIR/.obj
