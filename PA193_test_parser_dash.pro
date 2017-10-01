TEMPLATE = subdirs

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SUBDIRS += \
    src \
    tests  \

src.subdir  = src
tests.subdir  = tests
