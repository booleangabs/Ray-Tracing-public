CXX = g++
CXXFLAGS = -Iinclude

ifndef WINDOWS
	WINDOWS=true
endif

ifeq ($(WINDOWS), true)
	CREATE_BIN = if not exist bin mkdir bin
	CLEAR_BIN = forfiles /P bin /M * /C "cmd /c if @isdir==FALSE del @file"
	EXT = exe
else
	CREATE_BIN = mkdir -p bin
	CLEAR_BIN = rm -rf bin
	EXT = o
endif

all: run_raytracing

bin/%.$(EXT): src/%.cpp
	@$(CREATE_BIN)
	@$(CXX) -c $^ -o $@ $(CXXFLAGS)

##### Main #####

bin/main: src/main.cpp
	@$(CREATE_BIN)
	@$(CXX) $^ -o $@ $(CXXFLAGS)

run_raytracing: bin/main
	@"$(^)"

##### Tests #####

bin/test_point3: test/test_point3.cpp bin/Point3.$(EXT)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_point3: bin/test_point3
	@"$(^)"


##### Cleanup #####

clean:
	@$(CLEAR_BIN)

