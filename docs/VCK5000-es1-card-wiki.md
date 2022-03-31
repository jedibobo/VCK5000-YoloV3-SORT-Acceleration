## VCK5000-es1 card wiki

## First of all

I must say that Xilinx didn’t show its generousity when I received a Enginnering Sample(ES) card, and they release Vitis AI 2.0 which only supports Production(PROD) card. Since I only have RTX3060, I was unable to Train and Quantize models, and deploy it on VCK5000. There are also voices on Hackster.io mentioning this problem. The answer given officially is “There is no work around for ES card to use VAI2.0”. [link](https://www.hackster.io/contests/xilinxadaptivecomputing2021/discussion/posts/9235#challengeNav)

Apart from its multi-version problems, VCK5000 is also a great and revolutional card for me. It is the first time for me, an under-graduate, to use ACAP devices. Thanks for this oppotunity.

## VCK5000 full names and its meaning(also about DPU)

PROD refers to `Production Silicon`.

ES refers to `Engineering Sample`.

VCK5000 and its DPU are tightly related, and the name of DPU and VCK5000 that you may find in the document are as follows:

### 1.DPUCVDX8H is always the same

In UG1414(2021,when `VAI2.0` is not released), we have `DPUCVDX8H_ISA1_F2W2 (VCK5000)`.

In UG1414(2022) `DPUCVDX8H_ISA1 (VCK5000)` and `8PE` doesn't have depthwise-conv2d engine.

So, VCK5000-DWC means DPU supports Depthwise-Conv2d

## 2.something about **n**PE

I found it in Vitis-AI 2.0 repo, [link](https://github.com/Xilinx/Vitis-AI/tree/master/dsa/DPUCVDX8H-XO). That’s where Xilinx tells us about the different design in hardware about DPUCVDX8H, for they have different `.xclbin` and different resources uage.