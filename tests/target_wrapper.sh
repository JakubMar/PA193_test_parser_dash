#!/bin/sh
DYLD_FRAMEWORK_PATH=/Users/bencikpeter/Qt5.9.2/5.9.2/clang_64/lib${DYLD_FRAMEWORK_PATH:+:$DYLD_FRAMEWORK_PATH}
export DYLD_FRAMEWORK_PATH
QT_PLUGIN_PATH=/Users/bencikpeter/Qt5.9.2/5.9.2/clang_64/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec "$@"
