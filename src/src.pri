INCLUDEPATH += ../src/include/ ../src/include/third/ ../src/include/third/crypto

HEADERS += $$files(../src/include/*.h) \
           $$files(../src/include/third/*.h) \
           $$files(../src/include/third/crypto/*.h) \

SOURCES += $$files(../src/sources/*.cpp) \
	   $$files(../src/sources/third/*.cpp) \
	   $$files(../src/sources/third/*.c)

