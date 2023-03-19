INCLUDES = include/

CXX = g++
CXXFLAGS = std=c++20 -Iinclude

ifndef WINDOWS
	WINDOWS=true
endif

ifeq ($(WINDOWS), true)
	create_bin = if not exist bin mkdir bin
	clear_bin = forfiles /P bin /M * /C "cmd /c if @isdir==FALSE del @file"
else
	create_bin = mkdir -p bin
	clear_bin = rm -rf bin
endif

all: run_raytracing

bin/%: src/%.cpp
	@$(create_bin)
	@$(CXX) $^ -o $@

run_raytracing: bin/main
	@$(create_bin)
	@$^

clean:
	@$(clear_bin)

