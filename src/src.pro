CONFIG += c++11
CONFIG += console  
QMAKE_CXXFLAGS += -std=c++11

TARGET = parser
TEMPLATE = app

INCLUDEPATH += include/ include/third/ include/third/crypto include/Exceptions/

HEADERS += $$files(include/*.h) \
           $$files(include/third/*.h) \
           $$files(include/third/*.hpp) \
           $$files(include/third/crypto/*.h) \
           $$files(include/Exceptions/*.h) \
             include/osx/endian.h \

SOURCES += $$files(sources/*.cpp) \
           $$files(sources/third/*.cpp) \
           $$files(sources/third/*.c) \

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug/src
} else {
    DESTDIR = ../build/release/src
}

OBJECTS_DIR = $$DESTDIR/.obj
