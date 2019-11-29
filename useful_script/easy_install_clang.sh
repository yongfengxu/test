#!/bin/bash

mkdir -p ~/llvm
cd ~/llvm

wget http://llvm.org/releases/9.0.0/llvm-9.0.0.src.tar.xz

wget http://llvm.org/releases/9.0.0/cfe-9.0.0.src.tar.xz

wget http://llvm.org/releases/9.0.0/clang-tools-extra-9.0.0.src.tar.xz

wget http://llvm.org/releases/9.0.0/compiler-rt-9.0.0.src.tar.xz

tar xf llvm-9.0.0.src.tar.xz

tar xf cfe-9.0.0.src.tar.xz

tar xf clang-tools-extra-9.0.0.src.tar.xz

tar xf compiler-rt-9.0.0.src.tar.xz

mv cfe-9.0.0.src clang
mv clang/ llvm-9.0.0.src/tools

mv clang-tools-extra-9.0.0.src extra
mv extra/ llvm-9.0.0.src/tools/clang/

mv compiler-rt-9.0.0.src compiler-rt
mv compiler-rt llvm-9.0.0.src/projects/


mkdir -p ~/llvm/llvm-build
cd ~/llvm/llvm-build
cmake -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=/home/elmpprv/projs -DCMAKE_C_COMPILER=/home/elmpprv/projs/bin/gcc -DCMAKE_CXX_COMPILER=/home/elmpprv/projs/bin/g++ -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=On ../llvm-9.0.0.src/

make -j4
