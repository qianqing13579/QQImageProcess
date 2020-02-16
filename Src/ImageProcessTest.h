//////////////////////////////////////////////////////////////////////////
// 测试类 ImageProcessTest.h
// 2014年11月13日 星期四，by QQ
//
// Contact://		Telephone:15366105857
//		Email:qianqing13579@163.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////


#ifndef __QQ_IMAGEPROCESS_TEST_H__
#define __QQ_IMAGEPROCESS_TEST_H__

#include "Mat.h"
using namespace QQ;

// 常用示例图像
#ifdef _WIN32
#define LENA_GRAY		"../../../../Resource/Image/Gray/Lena512.bmp"
#define LENA_COLOR		"../../../../Resource/Image/Color/Lena800.bmp"
#define BEAUTY_COLOR	"../../../../Resource/Image/Color/Beauty.bmp"
#define BEAUTY_GRAY		"../../../../Resource/Image/Gray/Beauty.bmp"
#define CAMERA_GRAY		"../../../../Resource/Image/Gray/Camera256.bmp"
#define CAMERA_COLOR	"../../../../Resource/Image/Color/Camera256.bmp"
#else
#define LENA_GRAY		"../../../Resource/Image/Gray/Lena512.bmp"
#define LENA_COLOR		"../../../Resource/Image/Color/Lena800.bmp"
#define BEAUTY_COLOR	"../../../Resource/Image/Color/Beauty.bmp"
#define BEAUTY_GRAY		"../../../Resource/Image/Gray/Beauty.bmp"
#define CAMERA_GRAY		"../../../Resource/Image/Gray/Camera256.bmp"
#define CAMERA_COLOR	"../../../Resource/Image/Color/Camera256.bmp"
#endif

class ImageProcessTest
{
public:
	void TestCreateImage();//测试创建图像
	void TestReadAndWrite();//测试读写
	void TestRotate();//测试旋转
	void TestResize();//测试Resize
	void TestCvtColor();//测试CvtColor
	void TestAssignmentOperator(Mat<uchar> &srcImage);//测试重载赋值操作符
	void TestEqualizeHistogram();//测试直方图均衡化
	void TestMemoryLeak();//测试是否有内存泄露
	void TestFilter();//测试滤波
	void TestMallocAndFree();// 测试内存的分配和释放
	void TestEdge();
};

#endif



