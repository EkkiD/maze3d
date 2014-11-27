#!/bin/bash
mkdir -p build && \
ln -sf CMakeLists_desktop.txt CMakeLists.txt && \
cd build && \
cmake ../
