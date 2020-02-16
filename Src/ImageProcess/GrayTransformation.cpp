#define DLLAPI_EXPORTS

#include "GrayTransformation.h"
#include"Histogram.h"

namespace QQ
{

void RGB2Gray(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	// 参数检查，内存分配
	assert(srcImage.numberOfChannels == 3 && "srcImage.numberOfChannels==3");
	dstImage.Create(srcImage.rows,srcImage.cols,1);
	

	//构建查找表
	int LUTR[256],LUTG[256],LUTB[256];
	for (int i=0;i<=255;++i)
	{
		LUTR[i]=0.299*(i<<16);
		LUTG[i]=0.587*(i<<16);
		LUTB[i]=0.114*(i<<16);
	}

	//利用查找表灰度化
	int pixelCount=srcImage.rows*srcImage.cols;
	uchar *dataOfSrc=srcImage.data;
	uchar *dataOfDst=dstImage.data;
	for (int i = 0; i <= pixelCount - 1; ++i, dataOfSrc += 3, ++dataOfDst)
	{

		int b = LUTB[dataOfSrc[0]];
		int g = LUTG[dataOfSrc[1]];
		int r = LUTR[dataOfSrc[2]];
		dataOfDst[0] = (b + g + r) >> 16;
	}
}

int ComputeMeanGray(const Mat<uchar> &srcImage)
{
	// 参数检查
	assert(srcImage.numberOfChannels == 1 && "srcImage.numberOfChannels==1");

	uchar *data = srcImage.data;
	int numberOfPixels = srcImage.rows*srcImage.cols;
	int sum = 0;
	for (int i = 0; i <= numberOfPixels - 1; ++i)
		sum += data[i];

	return sum / numberOfPixels;
}

void EqualizeHistogram(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	dstImage.Create(srcImage.rows, srcImage.cols, 1);

	// 求灰度直方图
	Mat<int> historgam;
	CalculateHistogram(srcImage, historgam);

	// 求累计分布直方图，将累计直方图作为灰度变换函数(LUT)
	int *dataOfHistogram = (int *)historgam.data;
	int LUT[256];
	LUT[0] = 0;
	int sum = dataOfHistogram[0];
	int pixelCount = srcImage.rows*srcImage.cols;
	for (int i = 1; i <= 255; ++i)
	{
		sum += dataOfHistogram[i];
		LUT[i] = 255 * sum / pixelCount;//累加概率
	}


	// 灰度变换
	uchar *dataOfSrc = srcImage.data;
	uchar *dataOfDst = dstImage.data;
	for (int i = 0; i <= pixelCount - 1; ++i)
	{
		int gray = dataOfSrc[i];
		dataOfDst[i] = LUT[gray];
	}

}


}//namespace QQ
