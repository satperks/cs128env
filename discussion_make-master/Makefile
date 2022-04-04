INCLUDES=-I src/ -I includes/
CXXFLAGS=-std=c++20 -stdlib=libc++ -lc++abi -g -O0 -Wall -Wextra -Werror -pedantic $(INCLUDES)
CXX=clang++

exec: bin/main.out
	$<

test: bin/tests.out
	$<

clean:
	rm -f bin/*

bin/main.out: src/main.cc src/point.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

bin/tests.out: tests/tests.cc src/point.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

compile_commands.json: Makefile
	$(CXX) -MJ $@ $(CXXFLAGS) tests/tests.cc src/point.cc -o bin/tests.out
	# $(CXX) -MJ $@ $(CXXFLAGS) src/main.cc -o bin/main.out

src/%.cc: includes/%.h
	touch $@

.DEFAULT_GOAL := test
.PHONY: test clean exec