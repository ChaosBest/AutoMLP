# AutoMLP


Transfer Pytorch model aonto C/C++ kernels, and then FPGA implementation. 

More details and experiment data could be found in our paper "AutoMLP: A Framework for the Acceleration of Multi-Layer Perceptron Models on FPGAs for Real-Time ...". And if you any question or want some adjustment from this work, it will become our pleasure and please don't hesitate to contact us.  

C. Chen, B. da Silva*, C. Yang, C. Ma, J. Li* and C. Liu*, "AutoMLP: A Framework for the Acceleration of Multi-Layer Perceptron Models on FPGAs for Real-Time Atrial Fibrillation Disease Detection," in IEEE Transactions on Biomedical Circuits and Systems, vol. 17, no. 6, pp. 1371-1386, Dec. 2023, doi: 10.1109/TBCAS.2023.3299084. 

Including:

    Pytorch model to C/C++

    Bit-widths simulation and profing
    
    Parallel strategies for FPGA accelerated MLP.

![flow](https://user-images.githubusercontent.com/107203941/204804467-9ea575c1-6449-4d55-ba14-d254c32c531b.png)


Just in case it is not user-friendly enough. We are doing some updates for this toolchain. You can contact us and ask for it. We are happy to provide it and make it helpful.  

## Steps:
1. generate model by its topology
2. train model on Pytorch 
3. read model and generate C/C++ kernel
4. implement model onto a FPGA

## Updata list:

2022-11-17 support more activation function in the framework and toolchain. 

2022-11-18 support MLP model Generatr for training.

2023 use script to enclose codes. 

2024-01-17 A new script to generate. (I found the old version depend on dir. I want to make it easy.)

2024-06-17 Accept and include more test from one contributor. Thanks ^_^

![image](https://github.com/ChaosBest/AutoMLP/assets/107203941/0faa6279-4ffc-4404-9b20-77c18fb34fbd)


Python, C/C++, HLS, Vivado



### Chinese introduction/中文简介：

将MLP模型自动转换为C/C++代码，以及FPGA的设计与部署。包括一系列编译工具，仿真，性能分析工具和自动的并行设计工具

### Spanish introduction /西班牙语简介

Una cadena de herramientas para transferir el modelo MLP de Pytoch a C/C++ y a la implantación de FPGA de forma automática。

### French introduction

Transfert du modèle Pytorch vers des noyaux C/C++, puis implémentation FPGA.
