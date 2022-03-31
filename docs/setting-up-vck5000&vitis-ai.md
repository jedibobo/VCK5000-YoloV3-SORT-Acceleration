# setting-up-vck5000&vitis-ai

## build Vitis AI gpu docker image

This is quite a long time and hard work for those who cannot pass wall. So I make a github repo to help with this problem. Using the files that I give in [VAI-dockersetup](https://github.com/jedibobo/VAI-dockersetup), it will save you a lot of time.

After generating the docker image, run:

```shell
./docker_run.sh xilinx/vitis-ai-gpu:latest
```

to get into the container.

## Setting up VCK5000 and its environment

Following the instruction in [link](https://github.com/Xilinx/Vitis-AI/tree/v1.4.1/setup/vck5000). You must remember that: **ES1 card and PROD card is quite different**, and ES1 must use Vitis-AI tag1.4.1 to run codes. **Everything code or example you are reading, you must change it to tag1.4.1.**

There is also a system requirement in Setting up **VCK5000**, as stated in UG1414 and UG1354. I will give my software and hardware for this project:

### Hardware

- CPU: AMD R7 5800X
- GPU: Colorful IGame RTX3060(since Vitis 2.0, it supports RTX30 series, so its more recommended to use RTX20,10 series cards which have architecture earlier than `Ampere`)
- Mother Board：MSI Mortar B550m( it supports headless boot, quite useful)
- Power: Seasonic Gold 850W**(RTX3060 170w+ AMD 140w+ VCK5000 225W)**, no enough power ma result in system instability.

### Software

- system: Ubuntu 18.04 :kernel 5.4.0-94(104)
- CUDA 11.5(outside docker), since I have RTX3060

## Validate

run

```shell
/opt/xilinx/xrt/bin/xbutil --validate --verbose --device 00.04.00.1
```

## Environment Setup

whether you are in docker container or not, just run:

```
cd /workspace/setup/vck5000
source ./setup.sh
```