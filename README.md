# **Ray Tracing**
Ray tracing project for Undergraduate Computer Graphics course at CIn-UFPE (IF680)

---

# 1. Running instructions
Execute all of the following commands in the project root directory!!!

## 1.1 - Running the ray tracer
### Linux
```
make WINDOWS=false
```

### Windows
```
make
```

## 1.2 - Running tests
### Linux
```
make run_tests CAM_MODE=0 IMAGE_PATH=data_output/encoded_coords.ppm WINDOWS=false
```
or
```
make run_tests CAM_MODE=1 IMAGE_PATH=data_output/encoded_rays.ppm WINDOWS=false
```
or
```
make run_tests CAM_MODE=2 IMAGE_PATH=data_output/final_result.ppm WINDOWS=false
```

### Windows
```
make run_tests CAM_MODE=0 IMAGE_PATH=data_output/encoded_coords.ppm
```
or
```
make run_tests CAM_MODE=1 IMAGE_PATH=data_output/encoded_rays.ppm 
```
or
```
make run_tests CAM_MODE=2 IMAGE_PATH=data_output/final_result.ppm
```

## 1.3 - Clean up
### Linux
```
make clean WINDOWS=false
```

### Windows
```
make clean
```