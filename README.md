# QQImageProcess
## 简介
自己实现的不依赖于任何第三方库的图像处理库，包括图像的读写都是自己实现的。这个图像处理库从研究生期间就开始写了，当初只是用来学习图像处理这门课程的，一开始只是实现课堂上学习的一些简单的图像算法，后来慢慢觉得图像处理挺有意思的，这个工程就一直保留了下来。从最初的Bmp图像的读写，到参考OpenCV的Mat设计写了一个简单的Mat类型，再到后来实现一些基础的图像处理算法(比如直方图均衡化，Canny边缘检测，图像的旋转等)，自己在实现的过程中对图像的理解也越来越深刻了，时至今日，过了很多年了，自己依然在从事图像相关的工作，虽然现在大家都用深度学习了，这些low level的图像处理算法很少有人关注了，但是理解这些算法对于一个专业的计算机视觉算法工程师来说是非常重要的。

为了保证可读性，加上自己能力也有限，代码并没有做太多优化，本项目中的代码并没有什么实际的应用价值，开源这个项目只是希望自己的这些工作能够帮助更多初学者更好的理解low level图像算法，哪怕只有一位读者因为我的工作对图像产生了兴趣，我的目的就达到了。

## 目录结构
```

├── Resource:资源文件
│   └── Image:示例图像
├── Src:源码文件
│   └── ImageProcess:图像处理模块
│        └── Bmp.h:Bmp图像读写，本图像处理库目前只支持bmp图像的读写(Bmp图像的原理解读见博客:https://blog.csdn.net/qianqing13579/article/details/54316499)
│        └── Edge.h:边缘检测算法，主要包括Sobel和经典的Canny算法(Canny算法原理解读见博客:https://blog.csdn.net/qianqing13579/article/details/51708493)
│        └── Filter.h:滤波算法，主要包括均值滤波、中值滤波、高斯滤波等
│        └── GeometryTransformation.h:几何变换，主要包括仿射变换(图像旋转原理的解读见博客:https://blog.csdn.net/qianqing13579/article/details/52504089)
│        └── GrayTransformation.h:灰度变换，主要包括图像灰度化算法和直方图均衡化算法(直方图均衡化算法原理的解读见博客:https://blog.csdn.net/qianqing13579/article/details/52422364)
│        └── Histogram.h:直方图算法，主要包括计算图像的直方图(只支持灰度图)
│        └── Utility.h:常用工具
│   └── Utility:包括通用定义，常用工具
│        └── Alloc.h:内存分配和释放
│        └── BmpDefinition_Linux.h&BmpDefinition_Windows.h:Bmp图的定义
│        └── Mat.h:矩阵类Mat的定义,Mat的实现参考了OpenCV中的实现，使用方法也基本与OpenCV是一样的,具体使用方法可以参考各算法的示例程序
│   └── Samples.h:示例程序，包含了各种算法的示例程序
│   └── main.cpp:main函数
```
## 使用说明

本工程提供了多种编译方式, 包括了Windows下的QT和VS,Linux下的QT和cmake等方式,你可以选择一种最适合你的方式。

### Windows
#### VS
1. 使用VS2013打开Windows目录下的VS3013工程
2. 在main函数中选择Samples类中的一个示例，比如Filter()，运行程序，可以在“Windows/VS2013/QQImageProcess/QQImageProcess/”目录下看到结果图像Result.bmp

注：原始工程使用的是VS2013，你也可以采用其他VS版本。
#### QT
1. 使用QTCreator打开QQImageProcess.pro
2. 创建如下路径"Build/Windows/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.5的32位版本,则Debug版本的构建目录为"Build/Windows/QT/build-QQImageProcess-Desktop_Qt_5_5_1_MSVC2013_32bit-Debug/"
3. 在main函数中选择Samples类中的一个示例，比如Filter()，运行程序，可以在QT的构建目录(Build/Windows/QT/build-QQImageProcess-Desktop_Qt_5_5_1_MSVC2013_32bit-Debug/)中看到结果图像Result.bmp

### Linux
#### QT
1. 使用QTCreator打开QQImageProcess.pro
2. 创建如下路径"Build/Linux/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.10的64位版本,则Debug版本的构建目录为"Build/Linux/QT/build-QQImageProcess-Desktop_Qt_5_10_0_GCC_64bit-Debug/"
3. 在main函数中选择Samples类中的一个示例，比如Filter()，运行程序，可以在QT的构建目录(Build/Linux/QT/build-QQImageProcess-Desktop_Qt_5_10_0_GCC_64bit-Debug/)中看到结果图像Result.bmp

#### cmake
当前目录为项目根目录
```
mkdir -p ./Build/Linux/cmake/Release
cd ./Build/Linux/cmake/Release
cmake ../../../../
make -j8
./QQImageProcess
```
