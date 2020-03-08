# QQImageProcess
## 简介
自己实现的不依赖于任何第三方库的图像处理库，纯属兴趣，最初的想法很简单，只是为了加深对图像算法的理解。代码并没有做太多优化。

## 使用说明
### Windows
#### VS
1. 使用VS2013直接打开Windows目录下的VS3013工程
2. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
3. 运行程序，可以在“Windows/VS2013/QQImageProcess/QQImageProcess/”目录下看到结果图像Result.bmp

注：原始工程使用的是VS2013，如果你使用的是其他版本的VS，需要修改相关的配置。
#### QT
1. 使用QT打开QQImageProcess.pro
2. 在工程的根目录中依次创建如下路径"Build/Windows/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.5的32位版本,则Debug版本的构建目录为"Build/Windows/QT/build-QQImageProcess-Desktop_Qt_5_5_1_MSVC2013_32bit-Debug/"
3. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
4. 运行程序，可以在QT的构建目录中看到结果图像Result.bmp

### Linux
#### QT
1. 使用QT打开QQImageProcess.pro
2. 在工程的根目录中依次创建如下路径"Build/Linux/QT/"，并该将目录设置为QT的构建目录(注意，不能随便改动构建目录，否则工程无法正常运行)，比如使用QT5.10的64位版本,则Debug版本的构建目录为"Build/Linux/QT/build-QQImageProcess-Desktop_Qt_5_10_0_GCC_64bit-Debug/"
3. 在main函数中选择ImageProcessTest类中的一个测试用例，比如TestFilter()
4. 运行程序，可以在QT的构建目录中看到结果图像Result.bmp

#### 直接使用CMake
如果你不喜欢使用IDE或者当前无法使用IDE,你也可以在终端直接使用cmake来编译该工程，该工程提供了一个CMakeLists.txt示例,你可以根据自己的需要修改相应的配置。
