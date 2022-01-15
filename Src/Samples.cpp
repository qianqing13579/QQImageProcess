#include"Samples.h"
#include<stdio.h>
#include<time.h>
#include<utility>
#include"Bmp.h"
#include"Edge.h"
#include"Filter.h"
#include"Mat.h"
#include"GeometryTransformation.h"
#include"GrayTransformation.h"
#include"Histogram.h"
#include"Utility.h"

using namespace QQ;
using namespace std;

// 图像路径
#define LENA_GRAY		"../../../../Resource/Image/Gray/Lena512.bmp"
#define LENA_COLOR		"../../../../Resource/Image/Color/Lena800.bmp"
#define BEAUTY_COLOR	"../../../../Resource/Image/Color/Beauty.bmp"
#define BEAUTY_GRAY		"../../../../Resource/Image/Gray/Beauty.bmp"
#define CAMERA_GRAY		"../../../../Resource/Image/Gray/Camera256.bmp"
#define CAMERA_COLOR	"../../../../Resource/Image/Color/Camera256.bmp"

#define NUM_LOOP 100

void Samples::CreateImage()
{
	// 建立一个空图像
	Mat<uchar> srcImage(512,512,3,QQ::Scalar(0,0,255));
	
	// 设置图像值
	srcImage.SetTo(Scalar(255,0,0));

	// 保存图像
    WriteBmp("Result.bmp", srcImage);

}

void Samples::ReadAndWrite()
{
	// 读取图像
    Mat<uchar> srcImage;
	ReadBmp(LENA_COLOR, srcImage);
	
	// 将第100行设置为0
	for (int i = 0; i <= srcImage.cols - 1; ++i)
	{
		srcImage.At<Vec3b>(100, i) = Vec3b(255,255,255);
	}
	
	// 保存图像
    WriteBmp("Result.bmp", srcImage);
	
}
void Samples::Rotate()//旋转
{
	// 读取图像
	Mat<uchar> srcImage;
	ReadBmp(BEAUTY_COLOR, srcImage);

    // 旋转
	Mat<uchar> dstImage;
    // Rotate(srcImage, Point(srcImage.cols/2,srcImage.rows/2), 90, 1,Size(srcImage.rows, srcImage.cols), dstImage);
	// Rotate90(srcImage, dstImage);
	Rotate180(srcImage, dstImage); 
	// Rotate270(srcImage, dstImage); 
	// VerticalFlip(srcImage, dstImage);
	// HorizontalFlip(srcImage, dstImage);

    // 保存图像
	WriteBmp("Result.bmp", dstImage);
}

void Samples::CvtColor()//CvtColor
{
	// 读取图像
	Mat<uchar> srcImage;
	ReadBmp(LENA_COLOR, srcImage);

	// 灰度化
	Mat<uchar> dstImage;
	RGB2Gray(srcImage,dstImage);

	// 保存图像
    WriteBmp("Result.bmp",dstImage);


}

void Samples::EqualizeHistogram()
{
	// 读取图像
	Mat<uchar> srcImage;
    ReadBmp(BEAUTY_GRAY,srcImage);

	// 直方图均衡化
	Mat<uchar> dstImage;
    QQ::EqualizeHistogram(srcImage,dstImage);

	// 保存图像
    WriteBmp("Result.bmp",dstImage);
}

void Samples::Filter()
{
	// 读取图像
	Mat<uchar> srcImage;
	ReadBmp(LENA_GRAY,srcImage);

	// 均值滤波
	/*Mat<float> kernel(5, 5, 1);
	int kernelSize = kernel.cols;
	for (int y = 0; y <= kernelSize-1; ++y)
	{
		for (int x = 0; x <= kernelSize - 1; ++x)
			kernel.At<float>(y, x) = 1.0/(kernelSize*kernelSize);
	}*/

	// Sobel边缘检测
	Mat<float> kernel(3, 3, 1);
	kernel.At<float>(0, 0) = -1;
	kernel.At<float>(0, 1) = -2;
	kernel.At<float>(0, 2) = -1;
	kernel.At<float>(1, 0) = 0;
	kernel.At<float>(1, 1) = 0;
	kernel.At<float>(1, 2) = 0;
	kernel.At<float>(2, 0) = 1;
	kernel.At<float>(2, 1) = 2;
	kernel.At<float>(2, 2) = 1;
	
	Mat<uchar> dstImage;
	//Blur(srcImage, dstImage, Size(13, 13));
	Convolution(srcImage, kernel, dstImage); 
	//MedianBlur(srcImage, dstImage, 5); 
	//GaussianBlur(srcImage, dstImage, 0.84089642);

	// 保存图像
	WriteBmp("Result.bmp", dstImage);
}

void Samples::Edge()
{
	// 读取图像
	Mat<uchar> srcImage;
	ReadBmp(LENA_GRAY, srcImage);

	// Canny边缘检测
    Mat<uchar> dstImage;
    Canny(srcImage, dstImage, 50, 150);

	// 保存图像
    WriteBmp("Result.bmp", dstImage);

}

void Samples::TestCopyAssignment()
{
	// 拷贝赋值
	{
		printf("============test copy assignment============\n");
		QQ::Mat<uchar> a(512,512,3);
		QQ::Mat<uchar> b(512,512,3);
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u,count:%d\n",b.refCount,*(b.refCount));
		a=b;
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u\n",b.refCount);
	}
	// 移动赋值
	{
		printf("============test move assignment============\n");
		QQ::Mat<uchar> a(512,512,3);
		QQ::Mat<uchar> b(512,512,3);
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u,count:%d\n",b.refCount,*(b.refCount));
		a=std::move(b);
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u\n",b.refCount);
	}
	// 自赋值
	{
		printf("============test self assignment============\n");
		QQ::Mat<uchar> a(512,512,3);
		QQ::Mat<uchar> b(512,512,3);
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u,count:%d\n",b.refCount,*(b.refCount));
		a=a;
		printf("a: address:%u,count:%d\n",a.refCount,*(a.refCount));
		printf("b: address:%u\n",b.refCount);
	}
}

