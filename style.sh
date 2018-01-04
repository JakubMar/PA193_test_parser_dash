#!/bin/sh

which astyle
if [ $? -eq 1 ]; then
        echo "astyle is not installed"
        exit 1
fi

astyle --style=allman tests/main.cpp src/include/*.h src/include/Exceptions/*.h src/sources/*.cpp -H -n
