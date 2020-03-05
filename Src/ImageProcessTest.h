//////////////////////////////////////////////////////////////////////////
// 测试类 ImageProcessTest.h
// 2014-11-13，by QQ
//
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////


#ifndef __QQ_IMAGEPROCESS_TEST_H__
#define __QQ_IMAGEPROCESS_TEST_H__


class ImageProcessTest
{
public:
	void TestCreateImage();//测试创建图像
	void TestReadAndWrite();//测试读写
	void TestRotate();//测试旋转
	void TestResize();//测试Resize
	void TestCvtColor();//测试CvtColor
	void TestEqualizeHistogram();//测试直方图均衡化
	void TestMemoryLeak();//测试是否有内存泄露
	void TestFilter();//测试滤波
	void TestMallocAndFree();// 测试内存的分配和释放
	void TestEdge();
};

#endif



