CXX=clang++-10
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -pedantic -Iincludes

exec: bin/exec

bin/exec: ./src/driver.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean

clean:
		rm -f bin/* obj/*