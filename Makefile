CXX = g++
CXXFLAGS = -std=c++20 -Iinclude

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

OBJS := bin/Point3.$(EXT) bin/Vec3.$(EXT) bin/Ray.$(EXT) \
		bin/Color.$(EXT) bin/Image.$(EXT) bin/Cam.$(EXT) \
		bin/Material.$(EXT) bin/HitRecord.$(EXT) \
		bin/Scene.$(EXT) bin/Plane.$(EXT) bin/Sphere.$(EXT) \
		bin/Mesh.$(EXT) bin/Light.$(EXT) bin/Triangle.$(EXT)

# $(info    OBJS are $(OBJS))

ifndef INPUT_PATH
	INPUT_PATH=data_input/input.txt
endif

ifndef IMAGE_PATH
	IMAGE_PATH=data_output/image.ppm
endif

# cam mode 0 -> Encode x and y coordinates
# cam mode 1 -> Encode ray directions
# cam mode 2 -> Actual camera
ifndef CAM_MODE
	CAM_MODE=0
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
	@"$(^)" $(INPUT_PATH) $(IMAGE_PATH)

##### Tests #####

bin/test_point3: test/test_point3.cpp bin/Point3.$(EXT) bin/Vec3.$(EXT)
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
	@"$(^)"

bin/test_cam: test/test_cam.cpp $(OBJS)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_cam: bin/test_cam
	@"$(^)" $(IMAGE_PATH) $(CAM_MODE)

bin/test_scene: test/test_scene.cpp $(OBJS)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_scene: bin/test_scene
	@"$(^)"

bin/test_sphere: test/test_sphere.cpp $(OBJS)
	@$(CXX) $^ $(CXXFLAGS) -o $@ 

run_test_sphere: bin/test_sphere
	@"$(^)"


run_tests: run_test_point3 run_test_vec3 run_test_ray run_test_image \
			run_test_cam run_test_scene run_test_sphere

##### Cleanup #####

clean:
	@$(CLEAR_BIN)


.PHONY: all clean