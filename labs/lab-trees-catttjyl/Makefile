CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cc includes/binary_search_tree.hpp includes/tree_node.hpp
	${CXX} ${CXX_FLAGS} src/main.cc -o bin/exec

bin/tests: tests/tests.cc includes/binary_search_tree.hpp includes/tree_node.hpp
	${CXX} ${CXX_FLAGS} tests/tests.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*
