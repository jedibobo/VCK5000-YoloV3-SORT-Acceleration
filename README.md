# YoloV3-SORT-VCK5000-Acceleration

This a project for Xilinx Global Adaptive Computing Challenge.
This Project aims to add Simple Online and Realtime Tracking to Yolo `Object Detection` Algorithms Series. As previously I have implemented the same software on CPU+GPU(RTX 2080ti) hardware and found `“low GPU occupancy”` on such platform. I want to utilize the power of optimized DPU on FPGA to fully accelerate the system.

## Note

VAI in the following docs refers to Vitis-AI.

## Quick Start

run:

```shell
sh build.sh
```

to get all executables. And they are: `video_test`,`yolov3-demo`,`yolov3-video`,`yolov3-sort`.

`yolov3-sort`is the executable that has full functions including video, detection, tracking

run:

```shell
./yolov3-sort path-to-xmodel
```



## Hardware&Software Setup

refer to [docs/setting-up-vck5000&vitis-ai.md](docs/setting-up-vck5000&vitis-ai.md)

Mind that I use PCIE3.0x4 to connect VCK5000, there will be bandwidth loss, which are showed in the `validation` in setup. 

Besides, I only have one RTX3060 GPU(2080ti is borrowed from a teacher), so I was unable to train and quantize model in Vitis-AI.(I figured out how to train by changing torch build version myself:see [link]()https://blog.csdn.net/qq_44498043/article/details/123617510, even if I rebuild vai_q whl, I still got error, and that finally leads to my give-up.)

## Implementation Process and Details

### xmodel

As stated in UG1354, the process of getting a Yolov3 model is throught the following process:

- train a float model in dk(darknet), caffe etc.
- prune(UG1333-v1.3), quantize and compile(UG1431) it to xmodel
- run on device’s DPUs

Compilation of model utilizes `xir` and arch.json file in `/opt/vitis_ai/compiler/arch/DPUCVDX8H/VCK5000/` in VAI docker.

Or, the same as me, I have to download it from [Vitis-AI/Model-Zoo](https://github.com/Xilinx/Vitis-AI/tree/1.4.1/models/AI-Model-Zoo/model-list). And find what models are supported on VCK5000-es1(mind the git tag: v1.4.1).

I choose [yolov3_voc](https://github.com/Xilinx/Vitis-AI/tree/1.4.1/models/AI-Model-Zoo/model-list/dk_yolov3_voc_416_416_65.42G_1.4) as a detection algorithm.

For those who customize a model, after you change the config file at the beginning of src/yolov3-video.cpp run `./yolov3-video path-to-xmodel`to see whether the xmodel works for the system.

### Simple Online and Realtime Tracking Algorithm

I referred to this [project](https://github.com/edwardnguyen1705/sort_cpp) to finish tracking. It is a tracking method from this [paper](https://arxiv.org/abs/1602.00763). The reason why I choose this algorithm rather than its advanced version “DeepSORT” is that “DeepSORT” requires a “deep association metric” that trained by metric learning, and it is quite hard for my original intention of using Detection and Tracking on RoboMaster Radar station. SORT is feed with Detection BBoxes, returning tracking bboxes using Kalman Filter and Hungarian Algorithm(which you can find in `src` dir.

### Cmake Compilation

There isn’t too much problems here. Only to note that:

- set CPP to c++17 set(CMAKE_CXX_FLAGS "-std=c++17")
- set `-lxnnpp-xnnpp` in g++ command to target_link_libraries(… vitis_ai_library-xnnpp …)

## Performance Comparison to GPU

The experiment results weren‘t rigorous enough，for I do not study on the differences of ACAP and GPUs. They are all my projects at school. The test conditions cannot be controlled exactly the same.

VCK5000 test is carried out using `walking_humans.nv12.1920x1080.h264`file which is generated following [link](https://www.hackster.io/AlbertaBeef/introducing-xilinx-kria-for-vision-ai-applications-819148). And calculate only the inference process of the model. Both model are YoloV3-DarkNet53(VOC), one is from Xilinx/VAI/Model-Zoo, the other is trained on [PaddlePaddle](https://github.com/PaddlePaddle/Paddle) with [PaddleX](https://github.com/PaddlePaddle/PaddleX) and prune it using sensitivity analysis, and inference was tested using the two repos [Paddle-cpp-deploy](https://github.com/jedibobo/Paddle-cpp-deploy) and [Paddle-TRT-TEST](https://github.com/jedibobo/Paddle-TRT-TEST) both using Paddle-TensorRT API to substitute kernels from `paddle.fp32` to `TensorRT FP16`. Since the previous version I used for quantizing Int8 model for Paddle Model loses a lot of accuracy, that FPS result may not be a reasonable one.

Peak Performance: Only inference through put, `test_performace_yolov3` in Vitis-AI-Library/yolov3 for VCK5000 and batch size=8 for GPU in pictures testing.(which is not rigorous for reading imgs takes time)

Average Performance: test_video_yolov3 for VCK5000 and also video input test for GPU.

Utilization： GPU utilization is checked using `nvidia-smi`.

|                                                  | VCK5000-ES1 | RTX2080Ti(FP16) | RTX2080Ti(INT8) |
| ------------------------------------------------ | ----------- | --------------- | --------------- |
| Peak Performance(FPS)                            | 279.765     | 57-63           | 120-125         |
| Average performance inferencing video files(FPS) | 60~         | 40~             | 75~             |
| Utilization(%)                                   | ？          | 18~25           | 20~             |

Note：`?` means I haven’t know the command of it using `xbutil`. But I measured the whole machine’s power draw is about 210 Watt(CPU+VCK) . Considering the power consumption, it has a quite high utilization rate.

## Reference

https://github.com/Xilinx/Vitis-AI/tree/1.4.1

