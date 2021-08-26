说明：

该软件包为`Arm-2D`在`RT-Thread`上的移植，原始仓库位于https://github.com/ARM-software/EndpointAI

关于该图形库的设计理念和使用说明请移步阅读原仓库或本软件包中`documents`文件夹中的相关文件。

需要注意的是该图形库依赖新版本的`CMSIS`和`CMSIS-DSP`；当使用gcc编译工具时，需要选择高版本。

上面处理完后，需要根据实际情况完成LCD驱动的编写，并提供一个基本的显示函数就能使用本软件包了。

~~~c
int32_t GLCD_DrawBitmap (uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const uint8_t *bitmap);
~~~

使用：

在`env`工具或者`studio`添加本软件包，路径为`packages\system\Arm-2D`.

根据配置选项可以选择是否使能抗锯齿选项，同是提供了两个基础的例子。配置好后编译在shell中输入`arm_2d_basic`或者`arm_2d_complex`就能看到显示的两个例子。



对于没有硬件或者学习目的的小伙伴，可以使用`RT-Studio`中内置的`QEMU`仿真出一块`STM32F429`开发板来使用。





