# AutoMLP


Transfer Pytorch model aonto C/C++ kernels, and then FPGA implementation. 

More details and experiment data could be found in our paper "to be added". And if you any question or want some adjustment from this work, it will become our pleasure and please don't hesitate to contact us.  

Including:

    Pytorch model to C/C++

    Bit-widths simulation and profing
    
    Parallel strategies for FPGA accelerated MLP.

![flow](https://user-images.githubusercontent.com/107203941/204804467-9ea575c1-6449-4d55-ba14-d254c32c531b.png)


## Steps:
1. generate model by its topology
2. train model on Pytorch 
3. read model and generate C/C++ kernel
4. implement model onto a FPGA

## Updata list:

2022-11-17 support more activation function in the framework and toolchain. 

2022-11-18 support MLP model Generatr for training.


Python, C/C++, HLS, Vivado

sequenceDiagram
    Features ->> HNN: Features explanation
    Features ->> HNN: HNN architectures
    Note left of HNN: Index: <br/>ROC, <br/>Acc, <br/>Time, <br/>Power, <br/> ...
   
    Note right of HNN: FPGA: <br/> Micro-Architecture<br/>Latency <br/>Power <br/> Compare with CPUs, <br/> ...
    Note left of Features: CPU: <br/>Information Entropy, <br/>RR Interval, <br/>Features Describtions


### Chinese introduction/中文简介：

将MLP模型自动转换为C/C++代码，以及FPGA的设计与部署。包括一系列编译工具，仿真，性能分析工具和自动的并行设计工具

### Spanish introduction /西班牙语简介

Una cadena de herramientas para transferir el modelo MLP de Pytoch a C/C++ y a la implantación de FPGA de forma automática。

### French introduction

Transfert du modèle Pytorch vers des noyaux C/C++, puis implémentation FPGA.
