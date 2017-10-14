CONFIG += c++11     
CONFIG += console  
CONFIG += testcase   
QMAKE_CXXFLAGS += -std=c++11

TARGET = tests
TEMPLATE = app
INCLUDEPATH += ../src/include/ ../src/include/third/ ../src/include/third/crypto

#These 2 lines should work :(
#LIBS += ../build/release/src/.obj/*.o
#LIBS -= -L/../build/release/src/.obj/ -lmain.o

#LIBS += ../build/release/src/.obj/aes_helper.o  \
LIBS += ../build/release/src/.obj/cubehash.o    \
        ../build/release/src/.obj/jh.o          \
        ../build/release/src/.obj/skein.o       \
        ../build/release/src/.obj/blake.o       \
        ../build/release/src/.obj/echo.o        \
        ../build/release/src/.obj/keccak.o      \
        ../build/release/src/.obj/shavite.o     \
        ../build/release/src/.obj/uint256.o     \
        ../build/release/src/.obj/bmw.o         \
        ../build/release/src/.obj/groestl.o     \
        ../build/release/src/.obj/luffa.o       \
        ../build/release/src/.obj/simd.o        \
        ../build/release/src/.obj/utilstrencodings.o

SOURCES += main.cpp
HEADERS += catch.hpp

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug/tests
} else {
    DESTDIR = ../build/release/tests
}

OBJECTS_DIR = $$DESTDIR/.obj
