Here is the new version of C generate in 2024-01-17.

In the generated file, I use the AXI protocol for data transfer. You can find more information about the AXI protocol in the [AXI4 documentation](https://pp4fpgas.readthedocs.io/en/latest/axi4.html).

With this C/C++ file, it will be easy to generate HLS IP.


## How to use
To use this code, follow these steps:

1. Following the [PyTorch](https://pytorch.org/get-started/locally/) official website to install PyTorch.
2. Modify the `block_C_gen_v2.py` file according to the parameters of the model being trained.
3. Run the python script, `python3 block_C_gen_v2.py`, to generate the C generated file.
4. We provide the test code `test_AutoMLP.cpp` and test data `data.hpp` for quick testing. Use the `make` command to compile and run.
---
1. 根据[PyTorch](https://pytorch.org/get-started/locally/)的官网的要求安装。
2. 根据所训练的模型的参数，修改`block_C_gen_v2.py`文件。
3. 运行python脚本，`python3 block_C_gen_v2.py`，生成C generated file.
4. 我们提供测试代码`test_AutoMLP.cpp`和测试数据`data.hpp`，方便快速测试，使用`make`命令编译运行


