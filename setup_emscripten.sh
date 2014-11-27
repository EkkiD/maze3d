#!/bin/bash
mkdir -p embuild && \
ln -sf CMakeLists_emcc.txt CMakeLists.txt && \
cd embuild && \
emcmake cmake ../ && \
cd ../ && \
cp test.html embuild/

