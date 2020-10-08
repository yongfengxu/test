#!/bin/bash

git clone https://github.com/llvm/llvm-project.git

cd llvm-project
mkdir build
cd build

cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/home/elmpprv/projs -DCMAKE_C_COMPILER=/home/elmpprv/projs/bin/gcc -DCMAKE_CXX_COMPILER=/home/elmpprv/projs/bin/g++ -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=On ../llvm

make -j4

make install
