#include"ImageProcessTest.h"
#include"Bmp.h"
#include"Edge.h"
#include"Filter.h"
#include"GeometryTransformation.h"
#include"GrayTransformation.h"
#include"Histogram.h"
#include<time.h>
using namespace QQ;
using namespace std;

void ImageProcessTest::TestCreateImage()//测试创建图像
{
	Mat<uchar> srcImage(512,512,3,QQ::Scalar(0,0,255));//建立一个空图像
	
	////设置图像值
	srcImage.SetTo(Scalar(255,0,0));
	//srcImage.SetTo(Scalar(255, 255, 255, 0));

	WriteBmp("D:/1.bmp", srcImage);

}

void ImageProcessTest::TestReadAndWrite()
{
//	//读取
//	Mat<uchar> srcImage;//建立一个空图像
//	ReadBmp(LENA_COLOR, srcImage);
//	
//	//// 将第100行设置为0
//	for (int i = 0; i <= srcImage.cols - 1; ++i)
//	{
//		srcImage.At<Vec3b>(100, i) = Vec3b(255,255,255);
//	}
//
//	// 扩充边界
//	/*Image dstImage;
//	CopyMakeBorder(srcImage, dstImage, 2, 2, 2, 2);
//*/
//	//保存
//	WriteBmp("D:/1.bmp", srcImage);


	//读取
	Mat<uchar> srcImage;//建立一个空图像
    ReadBmp(LENA_GRAY, srcImage);

	//// 将第100行设置为0
	for (int i = 0; i <= srcImage.cols - 1; ++i)
	{
		srcImage.At<uchar>(100, i) = 255;
	}

	// 扩充边界
	/*Image dstImage;
	CopyMakeBorder(srcImage, dstImage, 2, 2, 2, 2);
	*/
	//保存
	WriteBmp("Result.bmp", srcImage);

	
}
void ImageProcessTest::TestRotate()//测试旋转
{
	Mat<uchar> srcImage;
	ReadBmp(BEAUTY_COLOR, srcImage);

	Mat<uchar> dstImage;
	double time1=clock();
	Rotate(srcImage, Point(0,0), 30, 1,Size(srcImage.rows, srcImage.cols), dstImage); // 16
	//Rotate270(srcImage, dstImage); // 7ms
	//VerticalFlip(srcImage, dstImage);
	double time2=clock();
	printf("rotate time:%f\n", (time2 - time1));
	WriteBmp("Result.bmp", dstImage);
}
void ImageProcessTest::TestResize()
{
	////使用OpenCV测试Resize时间
	//clock_t time1,time2;

	//Image srcImage;
	//ReadBmp((string(COLOR)+"Road.bmp").c_str(),srcImage);

}

void ImageProcessTest::TestCvtColor()//测试CvtColor
{
	
	Mat<uchar> srcImage;
	ReadBmp(LENA_COLOR, srcImage);
	double sum=0;
	Mat<uchar> dstImage;
	for (int i=1;i<=16;++i)
	{
		clock_t time1=clock();
		RGB2Gray(srcImage,dstImage);
		clock_t time2=clock();
		sum+=(time2-time1);

	}
	printf("CvtColor:%f ms\n",sum/16);
	WriteBmp("D:/1.bmp",dstImage);


}
void ImageProcessTest::TestAssignmentOperator(Mat<uchar> &srcImage)//测试重载赋值操作符
{
	//当函数返回的时候，srcImage引用计数也变成0了，这个时候，就要释放空间了
	//赋值
	Mat<uchar> dstImage,dstImage2;
	dstImage2=dstImage=srcImage;

}
void ImageProcessTest::TestEqualizeHistogram()//测试直方图均衡化
{
	//测试直方图
	Mat<uchar> srcImage;
	ReadBmp("D:/Image/Gray/White.bmp",srcImage);

	//计算直方图
	Mat<int> histogram;
	CalculateHistogram(srcImage, histogram);
	
	//输出直方图
	int *dataOfHistogram =(int *)histogram.data;
	for (int i=0;i<=255;++i)
	{
		printf("%d\n", dataOfHistogram[i]);
	}

	////直方图均衡化C++版
	Mat<uchar> dstImage;
	EqualizeHistogram(srcImage,dstImage);
	WriteBmp("D:/Equalize.bmp",dstImage);
}

void ImageProcessTest::TestMemoryLeak()//测试是否有内存泄露
{
	while (true)
	{
		Mat<uchar> srcImage;
		ReadBmp(LENA_COLOR, srcImage);
		printf("%d\n", srcImage.cols);
	}
	
}

void ImageProcessTest::TestSmooth()//测试滤波
{
	//测试均值滤波
	Mat<uchar> srcImage;
	ReadBmp(LENA_GRAY,srcImage);

	Mat<float> kernel(5, 5, 1);
	int kernelSize = kernel.cols;

	// 均值滤波的时候，如果窗口过大，会出现精度下降，这个时候就需要一定的数据处理了
	for (int y = 0; y <= kernelSize-1; ++y)
	{
		for (int x = 0; x <= kernelSize - 1; ++x)
			kernel.At<float>(y, x) = 1.0/(kernelSize*kernelSize);
	}
	
	Mat<uchar> dstImage;
	clock_t t1;
	clock_t t2;
	int sum=0;
	for (int i=1;i<=16;i++)
	{
		t1=clock();

		// 对于滤波，还是使用Blur
		//Blur(srcImage, dstImage, Size(13, 13));// 3*3：2ms，5*5：2ms，基本不随卷积核大小发生变化
		//Convolution(srcImage, kernel, dstImage); // 3*3:7ms,5*5:51ms
		//MedianBlur(srcImage, dstImage, 5); // 3*3:9ms,5*5:12ms
		GaussianBlur(srcImage, dstImage, 0.84089642);
		t2=clock();
		sum+=(t2-t1);
	}
	printf("My Blur time:%d ms\n",sum>>4);
	WriteBmp("D:/Blur.bmp", dstImage);

}

// 2016-5-30 15:07:08，by QQ
// 测试内存的分配和释放
void ImageProcessTest::TestMallocAndFree()
{
	//BYTE *data = (BYTE *)AlignedMalloc(100, 16);

	//// 往内存写数据
	//for (int i = 0; i <= 99; ++i)
	//{
	//	data[i] = 255;
	//}

	//// 输出分配的100个数据
	//// 往内存写数据
	//for (int i = 0; i <= 99; ++i)
	//{
	//	printf("%d\n", data[i]);
	//}

	//AlignedFree(data);
	//getchar();



}

void ImageProcessTest::TestEdge()
{
	Mat<uchar> srcImage;
	ReadBmp(LENA_GRAY, srcImage);

	//Mat<uchar> dstImage;
	//Sobel(srcImage, dstImage);
	//Canny(srcImage, dstImage, 50, 150);
	//WriteBmp("D:/Edge.bmp", dstImage);

	Mat<int> dstImage;
	ComputeIntegralImage(srcImage, dstImage);
	printf("%d\n", dstImage.At<int>(dstImage.rows - 1, dstImage.cols - 1));

	

}

