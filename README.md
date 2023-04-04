# **Ray Tracing**
Ray tracing project for Undergraduate Computer Graphics course at CIn-UFPE (IF680)

---

# Running
Execute all make commands in the project root directory

## Main
```
make 
```

## Tests
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

* Note that currently CAM_MODE=2 outputs an empty image

### Clean up
```
make clean
```