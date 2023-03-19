INCLUDES = include/

CXX = g++
CXXFLAGS = std=c++20 -Iinclude

all: run_raytracing

bin/main: src/main.cpp
	@$(CXX) $^ -o $@

run_raytracing: bin/main
	@$^

