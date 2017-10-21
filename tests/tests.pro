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

#Don't know why this file is not generated/needed
#LIBS += ../build/release/src/.obj/aes_helper.o


SOURCES += main.cpp
HEADERS += catch.hpp

CONFIG(debug, debug|release) {
    DESTDIR = ../build/debug/tests
LIBS +=     ../build/debug/src/.obj/cubehash.o    \
            ../build/debug/src/.obj/jh.o          \
            ../build/debug/src/.obj/skein.o       \
            ../build/debug/src/.obj/blake.o       \
            ../build/debug/src/.obj/echo.o        \
            ../build/debug/src/.obj/keccak.o      \
            ../build/debug/src/.obj/shavite.o     \
            ../build/debug/src/.obj/uint256.o     \
            ../build/debug/src/.obj/bmw.o         \
            ../build/debug/src/.obj/groestl.o     \
            ../build/debug/src/.obj/luffa.o       \
            ../build/debug/src/.obj/simd.o        \
            ../build/debug/src/.obj/utilstrencodings.o \
            ../build/debug/src/.obj/block.o       \
            ../build/debug/src/.obj/blockchain.o  \
            ../build/debug/src/.obj/transaction.o \
            ../build/debug/src/.obj/txin.o        \
            ../build/debug/src/.obj/txout.o


} else {
    DESTDIR = ../build/release/tests
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
            ../build/release/src/.obj/utilstrencodings.o \
            ../build/release/src/.obj/block.o       \
            ../build/release/src/.obj/blockchain.o  \
            ../build/release/src/.obj/transaction.o \
            ../build/release/src/.obj/txin.o        \
            ../build/release/src/.obj/txout.o
}

OBJECTS_DIR = $$DESTDIR/.obj
