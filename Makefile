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

SRCS := bin/Point3.cpp bin/Vec3.cpp bin/Ray.cpp \
		bin/Color.cpp bin/Image.cpp
OBJS := $(patsubst %.cpp,%.$(EXT),$(SRCS))

# $(info    OBJS are $(OBJS))

ifndef IMAGE_PATH
	IMAGE_PATH=data_output/image.ppm
endif

all: run_raytracing

bin/%.$(EXT): src/%.cpp
	@$(CREATE_BIN)
	@$(CXX) -c $^ -o $@ $(CXXFLAGS)

##### Main #####

bin/main: src/main.cpp $(OBJS)
	@$(CREATE_BIN)
	@$(CXX) $^ -o $@ $(CXXFLAGS)

run_raytracing: bin/main
	@"$(^)"

##### Tests #####

bin/test_point3: test/test_point3.cpp bin/Point3.$(EXT)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_point3: bin/test_point3
	@"$(^)"

bin/test_vec3: test/test_vec3.cpp bin/Point3.$(EXT) bin/Vec3.$(EXT)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_vec3: bin/test_vec3
	@"$(^)"

bin/test_ray: test/test_ray.cpp bin/Point3.$(EXT) bin/Vec3.$(EXT) bin/Ray.$(EXT)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_ray: bin/test_ray
	@"$(^)"

bin/test_image: test/test_image.cpp bin/Color.$(EXT) bin/Image.$(EXT)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_image: bin/test_image
	@"$(^)" $(IMAGE_PATH)


run_tests: run_test_point3 run_test_vec3 run_test_ray run_test_image

##### Cleanup #####

clean:
	@$(CLEAR_BIN)


.PHONY: all clean