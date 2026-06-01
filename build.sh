#!/bin/bash
set -e

SYS_DLL="/c/Windows/System32/opengl32.dll"
DEF_FILE="src/exports.def"
OUT_DLL="build/opengl32.dll"

echo "[1/4] Generating DEF file..."
mkdir -p src
echo "LIBRARY opengl32.dll" > $DEF_FILE
echo "EXPORTS" >> $DEF_FILE

objdump -p "$SYS_DLL" | grep -E "\[\s*[0-9]+\]" | awk '{print $NF}' | while read func; do
    if [ "$func" == "glDrawElements" ]; then
        echo "    glDrawElements = my_glDrawElements" >> $DEF_FILE
    elif [ "$func" == "glDrawRangeElements" ]; then
        echo "    glDrawRangeElements = my_glDrawRangeElements" >> $DEF_FILE
    elif [ "$func" == "glDrawArrays" ]; then
        echo "    glDrawArrays = my_glDrawArrays" >> $DEF_FILE
    elif [ "$func" == "wglGetProcAddress" ]; then
        echo "    wglGetProcAddress = my_wglGetProcAddress" >> $DEF_FILE
    else
        echo "    $func = C:/Windows/System32/opengl32.$func" >> $DEF_FILE
    fi
done

echo "[2/4] Compiling..."
mkdir -p build
CXXFLAGS="-std=c++17 -O2 -DWIN32_LEAN_AND_MEAN -Wno-attributes"
g++ -c src/gl_proxy.cpp -o build/gl_proxy.o $CXXFLAGS
g++ -c src/main.cpp -o build/main.o $CXXFLAGS
g++ -c src/overlay.cpp -o build/overlay.o $CXXFLAGS

echo "[3/4] Linking..."
g++ -shared -o $OUT_DLL \
    build/main.o build/gl_proxy.o build/overlay.o \
    $DEF_FILE \
    -static -static-libgcc -static-libstdc++ \
    -lgdi32 -luser32 \
    -Wl,--kill-at

echo "Done!"