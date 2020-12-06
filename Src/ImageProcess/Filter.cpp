#define DLLAPI_EXPORTS

#include "Filter.h"
#include<vector>
#include "Utility.h"
#include "Histogram.h"
#include<math.h>
using namespace std;

namespace QQ
{
static void GetMedianValueAndPixelCountLowerMedian(const Mat<uchar> &image, int &medianValue, int &pixelCountLowerMedian)
{
	//获取直方图
	Mat<int> histogramMat;
	CalculateHistogram(image, histogramMat);

	int *histogram = (int *)histogramMat.data;
	pixelCountLowerMedian = 0;
	int pixelCount = image.cols*image.rows;
	for (int i = 0; i <= 255; ++i)
	{
		//
		pixelCountLowerMedian += histogram[i];
		if (2 * pixelCountLowerMedian>pixelCount)//少用除法(sum>pixelCount/2)
		{
			medianValue = i;
			break;
		}
	}

}

//2015-1-1 20:23:53,by QQ
//使用copyMakeBorder扩充图像边界，处理滤波边界
void Blur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, Size kernelSize)
{
	//新图像的大小
	int width_Dst = srcImage.cols;
	int height_Dst = srcImage.rows;
	dstImage.Create(Size(width_Dst, height_Dst), 1);//如果重新分配，之前的空间会扔掉

	//扩充的大小
	int width_Extend = kernelSize.width >> 1;
	int height_Extend = kernelSize.height >> 1;

	//创建新图像
	Mat<uchar> image_New;
	CopyMakeBorder(srcImage, image_New, height_Extend, height_Extend, width_Extend, width_Extend);

	//新图像参数
	int width_New = image_New.cols;
	int height_New = image_New.rows;
	int widthStep_New = width_New;

	//滑动窗口
	int width_Aperture = kernelSize.width;
	int height_Aperture = kernelSize.height;
	int pixelCount = width_Aperture*height_Aperture;

	//计算需要滤波像素的起点坐标
	int startX = width_Aperture >> 1;
	int startY = height_Aperture >> 1;

	//每列的灰度值和
	int *sum_PerCol = new int[width_New];

	//对新图像做滤波处理
	uchar *row_New = image_New.data + startY*widthStep_New + startX;
	uchar *row_Dst = dstImage.data;//第一行
	uchar *row_Aperture_New = image_New.data;
	for (int y = startY; y <= height_New - startY - 1; ++y)
	{
		//列
		uchar *col_Dst = row_Dst;
		uchar *col_Aperture_New = row_Aperture_New;

		//计算每列height_Aperture个像素的灰度值和
		//第一行，计算所有列的和
		if (y == startY)
		{

			for (int k = 0; k <= width_New - 1; ++k)
			{
				sum_PerCol[k] = 0;
				//每列第一个指针
				uchar *col_PerLine = col_Aperture_New + k;
				for (int t = 0; t <= height_Aperture - 1; ++t)
				{
					sum_PerCol[k] += col_PerLine[0];
					col_PerLine += widthStep_New;//下一行
				}

			}
		}
		else//非第一行
		{
			for (int k = 0; k <= width_New - 1; ++k)
			{
				//每列第一个指针
				uchar *col_ = col_Aperture_New + k;
				sum_PerCol[k] -= col_[0 - widthStep_New];//减上面
				sum_PerCol[k] += col_[0 + (height_Aperture - 1)*widthStep_New];//加下面
			}

		}

		//计算width_Aperture行的列总和
		int sum_Aperture = 0;
		for (int x = startX; x <= width_New - startX - 1; ++x)
		{
			//每行第一个元素，求width_Aperture个列和
			if (x == startX)
			{
				for (int k = 0; k <= width_Aperture - 1; ++k)
				{
					sum_Aperture += sum_PerCol[k];
				}
			}
			else//非第一个元素
			{
				//减去左边
				sum_Aperture -= sum_PerCol[x - startX - 1];

				//加上右边
				sum_Aperture += sum_PerCol[x + startX];
			}

			//求均值
			uchar meanValue = sum_Aperture / pixelCount;
			col_Dst[0] = meanValue;

			//滑动一个像素
			col_Dst++;
			//col_New++;//这里不需要对源图像指针进行滑动
		}

		//下一行
		row_Dst += width_Dst;
		row_Aperture_New += width_New;
	}
}// Blur


//2015-4-22 19:51:29,by QQ
void MedianBlur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, int width_Aperture)
{
	
	int width_Dst = srcImage.cols;
	int height_Dst = srcImage.rows;
	dstImage.Create(Size(width_Dst, height_Dst), 1);//如果重新分配，之前的空间会扔掉
	//dstImage.setTo(Scalar(0));//置为0

	//滑动窗口
	int pixelCount = width_Aperture*width_Aperture;//窗口内像素总个数
	Mat<uchar> image_Aperture(width_Aperture, width_Aperture, 1);//滑动窗口图像
	int thresholdValue = pixelCount / 2 + 1;//step1.设置阈值(步骤参考：图像的高效编程要点之四)

	//计算起点坐标
	int startX = width_Aperture / 2;
	int startY = width_Aperture / 2;

	int height_Extend = startY;
	int width_Extend = startX;
	Mat<uchar> image_New;
	CopyMakeBorder(srcImage, image_New, height_Extend, height_Extend, width_Extend, width_Extend);//默认采用BORDER_REFLECT
	int height_New = image_New.rows;
	int width_New = image_New.cols;
	//第一行
	//这里需要设置3个指针,一起滑动
	//1.源图像中被处理的像素 
	//2.目标图像被处理的像素 
	//3.源图像滑动窗口
	uchar *row_New = image_New.data + startY*width_New + startX;//新图像
	uchar *row_Dst = dstImage.data;//目标图像
	uchar *row_Aperture_New = image_New.data;//源图像中的滑动窗口

	for (int y = startY; y <= height_New - startY - 1; ++y)
	{
		//列
		uchar *col_New = row_New;
		uchar *col_Dst = row_Dst;
		uchar *col_Aperture_New = row_Aperture_New;//操作整个滑动窗口

		///////////////////////////////对滑动窗口操作///////////////////////////////////////////
		//计算每行第一个滑动窗口直方图
		//提取滑动窗口图像
		uchar *row_Aperture = image_Aperture.data;//滑动窗口图像
		uchar *row_Aperture_New_2 = col_Aperture_New;
		for (int k = 0; k <= width_Aperture - 1; ++k)
		{
			//列
			uchar *col_ApertureImage = row_Aperture;
			uchar *col_Aperture_New_2 = row_Aperture_New_2;

			for (int w = 0; w <= width_Aperture - 1; ++w)
			{
				//处理每个像素
				col_ApertureImage[0] = col_Aperture_New_2[0];

				//下一个像素
				col_ApertureImage++;
				col_Aperture_New_2++;
			}

			//下一行
			row_Aperture += width_Aperture;
			row_Aperture_New_2 += width_New;
		}

		//step 2.确定中值，并记录亮度<=中值的像素点个数
		//求直方图
		Mat<int> histogramMat;
		CalculateHistogram(image_Aperture, histogramMat);

		//求亮度中值和<=中值的像素点个数
		int medianValue, pixelCountLowerMedian;
		GetMedianValueAndPixelCountLowerMedian(image_Aperture, medianValue, pixelCountLowerMedian);
		//////////////////////////////滑动窗口操作结束////////////////////////////////////////////

		//滤波
		col_Dst[0] = (uchar)medianValue;
		int *histogram = (int *)histogramMat.data;

		//滑动一个像素(三个指针在一起移动)
		col_Dst++;
		col_New++;
		col_Aperture_New++;
		for (int x = startX + 1; x <= width_New - startX - 1; ++x)//从每行第二个滤波像素开始
		{
			//////////////////////////////////维持滑动窗口直方图////////////////////////////////////////
			//step 3.去掉左侧
			uchar *col_Left = col_Aperture_New - 1;
			for (int k = 0; k <= width_Aperture - 1; ++k)
			{
				int gray = col_Left[0];
				histogram[gray] -= 1;
				if (gray <= medianValue)
				{
					pixelCountLowerMedian--;
				}
				col_Left += width_New;
			}

			//step 4.增加右侧
			uchar *col_Right = col_Aperture_New + width_Aperture - 1;
			for (int k = 0; k <= width_Aperture - 1; ++k)
			{
				int gray = col_Right[0];
				histogram[gray] += 1;
				if (gray <= medianValue)
				{
					pixelCountLowerMedian++;
				}
				col_Right += width_New;
			}

			//搜索新的中值
			if (pixelCountLowerMedian>thresholdValue)//step 6.
			{
				while (1)
				{
					pixelCountLowerMedian -= histogram[medianValue];
					medianValue--;
					if (pixelCountLowerMedian <= thresholdValue)
					{
						break;
					}
				}

			}
			else
			{
				while (pixelCountLowerMedian<thresholdValue)//step 5
				{
					medianValue++;
					pixelCountLowerMedian += histogram[medianValue];

				}

			}

			//滤波
			col_Dst[0] = (uchar)medianValue;

			//滑动一个像素
			col_New++;
			col_Dst++;
			col_Aperture_New++;
		}//end of x

		//下一行
		row_New += width_New;
		row_Dst += width_Dst;
		row_Aperture_New += width_New;
	}//end of y

}// MedianBlur

// 2016-10-4,by QQ
void GaussianBlur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double sigma)
{

	// compute the size of gaussian kernel
	int kSize = (int)(sigma * 3) << 1 + 1;// must be odd

	double coefficient = -1 / (2 * sigma*sigma);
	double coefficient2 = -1 * coefficient / PI;

	// the center of gaussian kernel
	int x0 = (kSize - 1) >> 1;
	int y0 = (kSize - 1) >> 1;

	// compute gaussian kernel
	Mat<float> gaussianKernel(kSize, kSize, 1);
	float *rowOfKernel = (float *)gaussianKernel.data;
	double sum = 0;// for normalization
	for (int y = 0; y <= kSize - 1; ++y, rowOfKernel += kSize)
	{
		float *colOfKernel = rowOfKernel;
		for (int x = 0; x <= kSize - 1; ++x, ++colOfKernel)
		{
			double distance = (x - x0)*(x - x0) + (y - y0)*(y - y0);
			colOfKernel[0] = coefficient2*exp(coefficient*(distance));
			sum += colOfKernel[0];
		}

	}

	// normalize the gaussian kernel
	int numberOfPixels = kSize*kSize;
	float *dataOfKernel = (float *)gaussianKernel.data;
	for (int i = 0; i <= numberOfPixels - 1; ++i)
	{
		dataOfKernel[i] /= sum;
	}

	// 做卷积运算,就是Library_OpenCV中的Convolution
	// Convolution(srcImage, gaussianKernel,dstImage);

}// GaussianBlur

Mat<float> GetGaborKernel(Size ksize, double sigma, double theta, double lambd, double gamma, double psi)
{
	double sigma_x = sigma;
	double sigma_y = sigma / gamma;
	int nstds = 3;
	int xmin, xmax, ymin, ymax;
	double c = cos(theta), s = sin(theta);

	if (ksize.width > 0)
		xmax = ksize.width / 2;
	else
		xmax = MAX(fabs(nstds*sigma_x*c), fabs(nstds*sigma_y*s));

	if (ksize.height > 0)
		ymax = ksize.height / 2;
	else
		ymax = MAX(fabs(nstds*sigma_x*s), fabs(nstds*sigma_y*c));

	xmin = -xmax;
	ymin = -ymax;


	Mat<float> kernel(ymax - ymin + 1, xmax - xmin + 1,1);
	double scale = 1;
	double ex = -0.5 / (sigma_x*sigma_x);
	double ey = -0.5 / (sigma_y*sigma_y);
	double cscale = PI * 2 / lambd;

	for (int y = ymin; y <= ymax; y++)
	for (int x = xmin; x <= xmax; x++)
	{
		double xr = x*c + y*s;
		double yr = -x*s + y*c;

		double v = scale*exp(ex*xr*xr + ey*yr*yr)*cos(cscale*xr + psi);
		kernel.At<float>(ymax - y, xmax - x) = (float)v;
	}

	return kernel;

}
// 卷积运算,Kernel正方形卷积核且边长为奇数
void Convolution(const Mat<uchar> &srcImage, const Mat<float> &kernel, Mat<uchar> &dstImage)
{
	// 目标图像大小
	int stride = 1;// 默认滑动窗口步长为1
	int kernelSize = kernel.rows;
	int widthOfDst = (srcImage.cols + kernelSize - 1 - kernelSize) / stride + 1;
	int heightOfDst = (srcImage.rows + kernelSize - 1 - kernelSize) / stride + 1;
	dstImage.Create(heightOfDst, widthOfDst, 1);

	// 扩充原图
	Mat<uchar> extendedImage;
	CopyMakeBorder(srcImage, extendedImage, kernelSize / 2, kernelSize / 2, kernelSize / 2, kernelSize / 2);

	// 构建滑动窗口像素查找表,计算滑动窗口中每个像素在图像中相对于滑动窗口指针偏移
	std::vector<int> pixelOffset;
	pixelOffset.resize(kernelSize*kernelSize);
	memset(&pixelOffset[0], 0, pixelOffset.size()*sizeof(int));
	int index = 0;
	for (int y = 0; y < kernelSize; ++y)
	{
		int yOffset = y*extendedImage.cols;
		for (int x = 0; x < kernelSize; ++x)
		{
			// 计算每个像素的偏移
			pixelOffset[index++] = yOffset + x;
		}
	}

	// 计算卷积
	uchar *rowOfDst = dstImage.data;
	for (int y = 0; y <= heightOfDst - 1; ++y, rowOfDst += widthOfDst)
	{
		uchar *colOfDst = rowOfDst;

		// 滑动窗口(第一个元素)在y方向上的偏移
		int offsetOfY = y*stride;

		for (int x = 0; x <= widthOfDst - 1; ++x, ++colOfDst)
		{
			// 计算滑动窗口在图像中的偏移,并转化为指向该滑动窗口的指针
			int offsetOfX = x*stride;
			uchar *dataOfROI = extendedImage.data + offsetOfY*extendedImage.cols + offsetOfX;

			// 卷积核
			float *dataOfKernel = (float *)kernel.data;
			float sum = 0;
			for (int i = 0; i < pixelOffset.size(); ++i)
			{
				sum += (dataOfROI[pixelOffset[i]] * dataOfKernel[i]);
			}

			// 卷积结果赋值为结果图像,注意溢出的处理！
			colOfDst[0] = SATURATE((int)sum);
		}
	}
}

















}//end of namespace QQ


