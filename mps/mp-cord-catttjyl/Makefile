CXX=clang++
CXX_FLAGS=-std=c++20 -g -Iincludes -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec

bin/exec: ./src/driver.cc ./src/cord.cc ./src/cord-utilities.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -f bin/*