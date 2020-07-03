# QQImageProcess
## 简介
自己实现的不依赖于任何第三方库的图像处理库，纯属兴趣，同时为了加深对图像算法的理解。代码并没有做太多优化。

***
## 目录结构
```

├── Resource:资源文件
│   └── Image:示例图像
├── Src:源码文件
│   └── ImageProcess:图像处理模块
│        └── Bmp.h:Bmp图像读写，本图像处理库目前只支持bmp图像的读写(Bmp图像的原理解读见博客:https://blog.csdn.net/qianqing13579/article/details/54316499)
│        └── Edge.h:边缘检测算法，主要包括Sobel和经典的Canny算法(Canny的解读见博客:https://blog.csdn.net/qianqing13579/article/details/51708493)
│        └── Filter.h:滤波算法，主要包括均值滤波、中值滤波、高斯滤波等
│        └── GeometryTransformation.h:几何变换，主要包括仿射变换(原理的解读见博客:https://blog.csdn.net/qianqing13579/article/details/52504089)
│        └── GrayTransformation.h:灰度变换，主要包括图像灰度化算法和直方图均衡化算法(直方图均衡化算法见博客:https://blog.csdn.net/qianqing13579/article/details/52422364)
│        └── Histogram.h:直方图算法，主要包括计算图像的直方图(只支持灰度图)
│        └── Utility.h:常用工具
│   └── Utility:包括通用定义，常用工具
│        └── Alloc.h:内存分配和释放
│        └── BmpDefinition_Linux.h&BmpDefinition_Windows.h:Bmp图的定义
│        └── Mat.h:矩阵类Mat的定义,Mat的实现参考了OpenCV中的实现，使用方法也基本与OpenCV是一样的,具体使用方法可以参考各算法的示例程序
│   └── ImageProcessTest.h:示例程序，包含了各种算法的示例程序，比如边缘检测算法的示例TestEdge()
│   └── main.cpp:main函数
```
***
## 使用说明
### Windows
#### VS
1. 使用VS2013直接打开Windows目录下的VS3013工程
2. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
3. 运行程序，可以在“Windows/VS2013/QQImageProcess/QQImageProcess/”目录下看到结果图像Result.bmp

注：原始工程使用的是VS2013，你也可以采用其他VS版本。
#### QT
1. 使用QT打开QQImageProcess.pro
2. 在工程的根目录中依次创建如下路径"Build/Windows/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.5的32位版本,则Debug版本的构建目录为"Build/Windows/QT/build-QQImageProcess-Desktop_Qt_5_5_1_MSVC2013_32bit-Debug/"
3. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
4. 运行程序，可以在QT的构建目录(Build/Windows/QT/build-QQImageProcess-Desktop_Qt_5_5_1_MSVC2013_32bit-Debug/)中看到结果图像Result.bmp

### Linux
#### QT
1. 使用QT打开QQImageProcess.pro
2. 在工程的根目录中依次创建如下路径"Build/Linux/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.10的64位版本,则Debug版本的构建目录为"Build/Linux/QT/build-QQImageProcess-Desktop_Qt_5_10_0_GCC_64bit-Debug/"
3. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
4. 运行程序，可以在QT的构建目录(Build/Linux/QT/build-QQImageProcess-Desktop_Qt_5_10_0_GCC_64bit-Debug/)中看到结果图像Result.bmp

#### cmake
如果你不喜欢使用IDE或者当前无法使用IDE,你也可以在终端直接使用cmake来编译该工程，该工程提供了一个CMakeLists.txt示例,你可以根据自己的需要修改相应的配置,使用cmake的编译流程与下面的qmake基本类似，可以参考下面的qmake编译流程。

#### qmake
由于QT工程提供了一个.pro文件，所以可以直接使用qmake来编译，具体编译流程如下：
1. 创建构建目录 ./Build/Linux/QT/Release
2. cd ./Build/Linux/QT/Release
3. qmake ../../../../QQImageProcess.pro
4. make -j8
5. ./QQImageProcess
