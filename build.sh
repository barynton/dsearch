#!/bin/bash
build_type=Debug
if [ $1 != "" ] ; then
    build_type=$1
fi
build_dir=build_$build_type
mkdir -p $build_dir
cd $build_dir
conan install .. --profile=default --build=missing
cd ../
cmake . -B ./$build_dir
cmake --build $build_dir -j 4