#! /usr/bin/env bash
path=$1
compile="g++-8 -I draw_queue -std=gnu++14 -pthread -DHELTHAZAR -O2 -Wl,-stack_size -Wl,40000000 -o test/solve $path"
if ! $compile 2> compile.out; then
    echo [1m[31mCompilation Error[0m
    cat compile.out
    rm compile.out
    exit
fi
rm compile.out
cd test
gtime -o my_time -f "(%es)" ./solve > teximages/test.tex
echo [1m[32mAccepted[0m `cat my_time`
if [ "$#" == 2 ]; then
	cat teximages/test.tex
fi
rm solve
rm my_time
cd ..
