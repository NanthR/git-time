#!/bin/bash
mapfile -t cpp < <( git ls-files | grep -E "*.cpp" )
for i in "${cpp[@]}"; do
	clang-format $i > temp
	[ ! -z "`diff $i temp`" ] && echo "$i is not formatted" && rm temp && exit 1
done

mapfile -t cmake < <( git ls-files | grep CMakeLists.txt )
for i in "${cmake[@]}"; do
	cmake-format $i > temp
	[ ! -z "`diff $i temp`" ]  && echo "$i is not formatted" && rm temp && exit 1
done
rm temp
