CC=clang++

all: Task.so

Task.cpp
	$(CC) `llvm-config-6.0 --cflags --libs` -std=c++14 -lclang  -shared  $^ -o $@

run: test_a_tester.c
	clang -cc1 -load ./Task.so -plugin print-fns $^
