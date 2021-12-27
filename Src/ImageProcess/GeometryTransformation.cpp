#define DLLAPI_EXPORTS

#include "GeometryTransformation.h"
#include <math.h>
#include <string.h>
#include "Utility.h"

#define  ROTATE_SHIFT  8

namespace QQ
{

void Rotate(const Mat<uchar> &srcImage, Point center, double theta, double scale, Size dstSize, Mat<uchar> &dstImage)
{
	// 参数检查，内存分配
	dstImage.Create(dstSize, srcImage.numberOfChannels);
	dstImage.SetTo(Scalar(0, 0, 0));

	// 原图像的旋转中心
	int x0 = center.x;
	int y0 = center.y;
	theta = DEGREE2RADIAN(theta);

	// dx,dy就是dstImage中心点与srcImage的旋转中心的距离，也就是平移的距离
	int dx = dstImage.cols / 2 - x0;
	int dy = dstImage.rows / 2 - y0;
	int numberOfChannels = srcImage.numberOfChannels;

	int widthOfDst = dstImage.cols;
	int heightOfDst = dstImage.rows;

	Mat<uchar> extendedImage;
	CopyMakeBorder(srcImage, extendedImage, 1, 1, 1, 1); // 使用0填充边界

	for (int y = 0; y <= heightOfDst - 1; ++y)
	{
		for (int x = 0; x <= widthOfDst - 1; ++x)
		{
			// 计算原图坐标
			float srcX = ((x - x0 - dx)*cos(theta) + (y - y0 - dy)*sin(theta)) / scale + x0;
			float srcY = ((x0 + dx - x)*sin(theta) + (y - y0 - dy)*cos(theta)) / scale + y0;
			
			// 加1,得到在extendedImage中的坐标
			srcX++; 
			srcY++;
			
			// 最近邻
			int x1 = (int)(srcX); 
			int y1 = (int)(srcY);

			// 浮点转化为整数
			int dx1 = (srcX - x1)*(1<< ROTATE_SHIFT);
			int dy1 = (srcY - y1)*(1<< ROTATE_SHIFT);

			if (numberOfChannels == 1)
			{
				// 注意这里的范围，在extendedImage中，原图的范围就是1~cols - 2了
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{	
					// 双线性插值
					// a就是最近邻像素
					// a   b
					//   p
					// c   d
					uchar a = extendedImage.At<uchar>(y1, x1);
					uchar b = extendedImage.At<uchar>(y1, x1 + 1);
					uchar c = extendedImage.At<uchar>(y1 + 1, x1);
					uchar d = extendedImage.At<uchar>(y1 + 1, x1 + 1);

					int p = a*((1 << ROTATE_SHIFT) - dx1)*((1 << ROTATE_SHIFT) - dy1) + b*dx1*((1 << ROTATE_SHIFT) - dy1) + c*((1 << ROTATE_SHIFT) - dx1)*dy1 + d*dx1*dy1;
					p = DESCALE(p, 2*ROTATE_SHIFT);

					dstImage.At<uchar>(y, x) = p;
				}
				else
				{
					// 越界赋值0
					dstImage.At<uchar>(y, x) = 0;
				}
			}
			else
			{
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{
					// 双线性插值
					// a就是最近邻像素
					// a   b
					//   p
					// c   d
					Vec3b a = extendedImage.At<Vec3b>(y1, x1);
					Vec3b b = extendedImage.At<Vec3b>(y1, x1 + 1);
					Vec3b c = extendedImage.At<Vec3b>(y1 + 1, x1);
					Vec3b d = extendedImage.At<Vec3b>(y1 + 1, x1 + 1);

					int p1 = a[0]*((1 << ROTATE_SHIFT) - dx1)*((1 << ROTATE_SHIFT) - dy1) + b[0]*dx1*((1 << ROTATE_SHIFT) - dy1) + c[0]*((1 << ROTATE_SHIFT) - dx1)*dy1 + d[0]*dx1*dy1;
					p1 = DESCALE(p1, 2 * ROTATE_SHIFT);
					int p2 = a[1]*((1 << ROTATE_SHIFT) - dx1)*((1 << ROTATE_SHIFT) - dy1) + b[1]*dx1*((1 << ROTATE_SHIFT) - dy1) + c[1]*((1 << ROTATE_SHIFT) - dx1)*dy1 + d[1] *dx1*dy1;
					p2 = DESCALE(p2, 2 * ROTATE_SHIFT);
					int p3 = a[2]*((1 << ROTATE_SHIFT) - dx1)*((1 << ROTATE_SHIFT) - dy1) + b[2]*dx1*((1 << ROTATE_SHIFT) - dy1) + c[2]*((1 << ROTATE_SHIFT) - dx1)*dy1 + d[2] *dx1*dy1;
					p3 = DESCALE(p3, 2 * ROTATE_SHIFT);


					dstImage.At<Vec3b>(y, x) = Vec3b(p1,p2,p3);
				}
				else
				{
					dstImage.At<Vec3b>(y, x) = Vec3b(0, 0, 0);
				}

			}
		}
	}
}

void Rotate90(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	// 参数检查，内存分配
	dstImage.Create(srcImage.cols,srcImage.rows, srcImage.numberOfChannels);
	dstImage.SetTo(Scalar(0, 0, 0));

	// 原图像的旋转中心
	int x0 = srcImage.cols / 2;
	int y0 = srcImage.rows / 2;

	// dx,dy就是dstImage中心点与srcImage的旋转中心的距离，也就是平移的距离
	int dx = dstImage.cols / 2 - srcImage.cols / 2;
	int dy = dstImage.rows / 2 - srcImage.rows / 2;
	int numberOfChannels = srcImage.numberOfChannels;

	int widthOfDst = dstImage.cols;
	int heightOfDst = dstImage.rows;

	Mat<uchar> extendedImage;
	CopyMakeBorder(srcImage, extendedImage, 1, 1, 1, 1); // 使用0填充边界

	for (int y = 0; y <= heightOfDst - 1; ++y)
	{
		for (int x = 0; x <= widthOfDst - 1; ++x)
		{
			// 计算原图坐标
			int srcX = (y - y0 - dy) + x0;
			int srcY = (x0 + dx - x) + y0;
			
			// 加1,得到在extendedImage中的坐标
			srcX++; 
			srcY++;
			
			// 最近邻
			int x1 = srcX; 
			int y1 = srcY;

			if (numberOfChannels == 1)
			{
				// 注意这里的范围，在extendedImage中，原图的范围就是1~cols - 2了
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{	
					dstImage.At<uchar>(y, x) = extendedImage.At<uchar>(y1, x1);
				}
				else
				{
					// 越界赋值0
					dstImage.At<uchar>(y, x) = 0;
				}
			}
			else
			{
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{
					dstImage.At<Vec3b>(y, x) = extendedImage.At<Vec3b>(y1, x1);
				}
				else
				{
					dstImage.At<Vec3b>(y, x) = Vec3b(0, 0, 0);
				}

			}
		}
	}

}

void Rotate180(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	// 参数检查，内存分配
	dstImage.Create(srcImage.rows,srcImage.cols, srcImage.numberOfChannels);
	dstImage.SetTo(Scalar(0, 0, 0));

	// 原图像的旋转中心
	int x0 = srcImage.cols / 2;
	int y0 = srcImage.rows / 2;

	// dx,dy就是dstImage中心点与srcImage的旋转中心的距离，也就是平移的距离
	int dx = dstImage.cols / 2 - srcImage.cols / 2;
	int dy = dstImage.rows / 2 - srcImage.rows / 2;
	int numberOfChannels = srcImage.numberOfChannels;

	int widthOfDst = dstImage.cols;
	int heightOfDst = dstImage.rows;

	Mat<uchar> extendedImage;
	CopyMakeBorder(srcImage, extendedImage, 1, 1, 1, 1); // 使用0填充边界

	for (int y = 0; y <= heightOfDst - 1; ++y)
	{
		for (int x = 0; x <= widthOfDst - 1; ++x)
		{
			// 计算原图坐标
			int srcX = (x - x0 - dx)*(-1) + x0;
			int srcY = (y - y0 - dy)*(-1) + y0;
			
			// 加1,得到在extendedImage中的坐标
			srcX++; 
			srcY++;
			
			// 最近邻
			int x1 = srcX; 
			int y1 = srcY;
			
			if (numberOfChannels == 1)
			{
				// 注意这里的范围，在extendedImage中，原图的范围就是1~cols - 2了
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{	
					dstImage.At<uchar>(y, x) = extendedImage.At<uchar>(y1, x1);
				}
				else
				{
					// 越界赋值0
					dstImage.At<uchar>(y, x) = 0;
				}
			}
			else
			{
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{
					dstImage.At<Vec3b>(y, x) = extendedImage.At<Vec3b>(y1, x1);
				}
				else
				{
					dstImage.At<Vec3b>(y, x) = Vec3b(0, 0, 0);
				}

			}
		}
	}
}

void Rotate270(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	// 参数检查，内存分配
	dstImage.Create(srcImage.cols,srcImage.rows, srcImage.numberOfChannels);
	dstImage.SetTo(Scalar(0, 0, 0));

	// 原图像的旋转中心
	int x0 = srcImage.cols / 2;
	int y0 = srcImage.rows / 2;

	// dx,dy就是dstImage中心点与srcImage的旋转中心的距离，也就是平移的距离
	int dx = dstImage.cols / 2 - srcImage.cols / 2;
	int dy = dstImage.rows / 2 - srcImage.rows / 2;
	int numberOfChannels = srcImage.numberOfChannels;

	int widthOfDst = dstImage.cols;
	int heightOfDst = dstImage.rows;

	Mat<uchar> extendedImage;
	CopyMakeBorder(srcImage, extendedImage, 1, 1, 1, 1); // 使用0填充边界

	for (int y = 0; y <= heightOfDst - 1; ++y)
	{
		for (int x = 0; x <= widthOfDst - 1; ++x)
		{
			// 计算原图坐标
			int srcX = ((y - y0 - dy)*(-1)) + x0;
			int srcY = ((x0 + dx - x)*(-1)) + y0;
			
			// 加1,得到在extendedImage中的坐标
			srcX++; 
			srcY++;
			
			// 最近邻
			int x1 = srcX; 
			int y1 = srcY;

			if (numberOfChannels == 1)
			{
				// 注意这里的范围，在extendedImage中，原图的范围就是1~cols - 2了
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{	
					dstImage.At<uchar>(y, x) = extendedImage.At<uchar>(y1, x1);
				}
				else
				{
					// 越界赋值0
					dstImage.At<uchar>(y, x) = 0;
				}
			}
			else
			{
				if ((x1 >= 1 && x1 <= extendedImage.cols - 2) && (y1 >= 1 && y1 <= extendedImage.rows - 2))
				{
					dstImage.At<Vec3b>(y, x) = extendedImage.At<Vec3b>(y1, x1);
				}
				else
				{
					dstImage.At<Vec3b>(y, x) = Vec3b(0, 0, 0);
				}

			}
		}
	}

}
	

void VerticalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	dstImage.Create(srcImage.rows,srcImage.cols, srcImage.numberOfChannels);

	// 垂直翻转
	int widthStep = srcImage.cols*srcImage.numberOfChannels;
	int width = srcImage.cols;
	int height = srcImage.rows;
	uchar *dataOfSrc = srcImage.data;
	uchar *dataOfDst = dstImage.data + widthStep*(dstImage.rows - 1);
	for (int y = 0; y <= height - 1; ++y, dataOfSrc += widthStep, dataOfDst -= widthStep)
	{
		// 拷贝一行
		memcpy(dataOfDst, dataOfSrc, widthStep);
	}
} // VerticalFlip

void HorizontalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
{
	// 分配内存
	dstImage.Create(srcImage.rows, srcImage.cols, srcImage.numberOfChannels);

	// 每一行建立查找表(对每一个通道建立索引)
	int width = srcImage.cols;
	int channelCount = srcImage.numberOfChannels;
	int widthStep = width*channelCount;
	int *table = new int[widthStep];
	for (int i = 0; i <= width - 1; ++i)
	{
		int index1 = i*channelCount;
		int index2 = (width - 1 - i)*channelCount;
		for (int j = 0; j <= channelCount - 1; ++j)
			table[index1 + j] = index2 + j;
	}


	uchar *dataOfSrc = srcImage.data;
	uchar *dataOfDst = dstImage.data;
	int limit = ((width + 1) >> 1)*channelCount; // 注意运算符优先级,为什么((width - 1) >>1)*channelCount 不对？提示:因为多通道的原因，对半使用(x+1)/2
	for (int y = 0; y <= srcImage.rows - 1; ++y, dataOfSrc += widthStep, dataOfDst += widthStep)
	{
		for (int x = 0; x <= limit; ++x)
		{
			int index = table[x];
			dataOfDst[index] = dataOfSrc[x];
			dataOfDst[x] = dataOfSrc[index];
		}
	}

	delete[] table;

}

}//namespace QQ
