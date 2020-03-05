#define DLLAPI_EXPORTS

#include "Utility.h"
#include <string.h>

namespace QQ
{
	void CopyMakeBorder(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, int top, int bottom, int left, int right)
	{
		// 参数检查，内存分配
		int newCols = srcImage.cols + left + right;
		int newRows = srcImage.rows + top + bottom;
		dstImage.Create(newRows, newCols, srcImage.numberOfChannels);
		dstImage.SetTo(Scalar(0, 0, 0));

		uchar *dataOfSrc = srcImage.data;
		uchar *dataOfDst = dstImage.data + dstImage.step*top + left*dstImage.numberOfChannels;
		for (int y = 0; y <= srcImage.rows - 1; ++y, dataOfDst += dstImage.step, dataOfSrc += srcImage.step)
		{
			memcpy(dataOfDst, dataOfSrc, srcImage.step);
		}
	} // CopyMakeBorder

	//2015-3-4 16:53:57，by QQ
	//改进的计算像素灰度值积分图像
	//方法：Integral(y,x) = Integral(y-1,x) + rowSum(y);
	void ComputeIntegralImage(const Mat<uchar> &srcImage, Mat<int> &dstImage)
	{
		//新图像的大小
		int width_Dst = srcImage.cols;
		int height_Dst = srcImage.rows;
		dstImage.Create(Size(width_Dst, height_Dst), 1);//如果重新分配，之前的空间会扔掉
		dstImage.SetTo(Scalar(0));

		int width_Src = srcImage.cols;
		int height_Src = srcImage.rows;

		//每个像素的通道数
		int channelCount_Src = srcImage.numberOfChannels;
		int channelCount_Integral = dstImage.numberOfChannels;//每个像素的通道数

		//行的通道数
		int widthStep_Src = channelCount_Src*width_Src;
		int widthStep_Integral = channelCount_Integral*width_Src;

		//第一行
		uchar *row_Src = srcImage.data;
		int *row_Integral = (int *)dstImage.data;//注意指针的转换
		for (int y = 0; y <= height_Src - 1; ++y)
		{
			int sum = 0;//当前行的累加和
			//列
			uchar *col_Src = row_Src;
			int *col_Integral = row_Integral;
			for (int x = 0; x <= width_Src - 1; ++x)
			{
				//该行的累加
				sum += col_Src[0];

				//计算第0行,第一行单独处理
				if (y == 0)
				{
					col_Integral[0] = sum;
				}
				else
				{
					//非第0行
					//当前行累加和+同列的上一个元素的值
					col_Integral[0] = sum + col_Integral[0 - widthStep_Integral];//下标
					//col_Integral[0]=sum+*(col_Integral-image_Integral.cols);//指针移动

				}

				//下一个像素
				col_Src++;
				col_Integral++;

			}
			//下一行
			row_Src += widthStep_Src;
			row_Integral += widthStep_Integral;
		}

	}// ComputeIntegralImage





}//namespace QQ
