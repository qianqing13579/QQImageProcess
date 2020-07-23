# 设置cmake的最低版本
cmake_minimum_required(VERSION 2.9)

# 设置项目名
project(QQImageProcess)

# 设置编译器
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++11)
set(CMAKE_BUILD_TYPE release)

# 添加预定义宏
#add_definitions(-DDEBUG)

# 添加头文件路径
set(INCLUDE_PATH    ${CMAKE_CURRENT_SOURCE_DIR}/Src/
                    ${CMAKE_CURRENT_SOURCE_DIR}/Src/Utility/ 
                    ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/)
include_directories(${INCLUDE_PATH})

# 添加源文件
set(SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/Bmp.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/Edge.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/Filter.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/GeometryTransformation.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/GrayTransformation.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/Histogram.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcess/Utility.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/Utility/Alloc.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/ImageProcessTest.cpp
                ${CMAKE_CURRENT_SOURCE_DIR}/Src/main.cpp)

# 添加可执行目标
add_executable(QQImageProcess ${SOURCE_FILES})
