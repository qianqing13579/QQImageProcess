#define DLLAPI_EXPORTS

#include"Edge.h"
#include<queue>
#include"Utility.h"

namespace QQ
{

	void Sobel(const Mat<uchar> &srcImage, Mat<uchar> &dstImage)
	{
		// 目标图像
		int widthOfDst = srcImage.cols;
		int heightOfDst = srcImage.rows;
		dstImage.Create(heightOfDst, widthOfDst, 1);

		// 扩充原图
		Mat<uchar> extendedImage;
		CopyMakeBorder(srcImage, extendedImage, 1, 1, 1, 1);

		uchar *rowOfExtendedImage = extendedImage.data + extendedImage.cols + 1;
		uchar *rowOfDstImage = dstImage.data;
		for (int y = 0; y <= heightOfDst - 1; ++y,rowOfExtendedImage+=extendedImage.cols,rowOfDstImage+=dstImage.cols)
		{
			uchar *colOfExtendedImage = rowOfExtendedImage;
			uchar *colOfDstImage = rowOfDstImage;
			for (int x = 0; x <= widthOfDst - 1; ++x,++colOfExtendedImage,++colOfDstImage)
			{
				int fx = (colOfExtendedImage[0 + 1 - extendedImage.cols] + 2 * colOfExtendedImage[0 + 1] + colOfExtendedImage[0 + 1 + extendedImage.cols]) -
					(colOfExtendedImage[0 - 1 - extendedImage.cols] + 2 * colOfExtendedImage[0 - 1] + colOfExtendedImage[0 - 1 + extendedImage.cols]);

				int fy = (colOfExtendedImage[0 + extendedImage.cols - 1] + 2 * colOfExtendedImage[0 + extendedImage.cols] + colOfExtendedImage[0 + extendedImage.cols + 1]) -
					(colOfExtendedImage[0 - extendedImage.cols - 1] + 2 * colOfExtendedImage[0 - extendedImage.cols] + colOfExtendedImage[0 - extendedImage.cols + 1]);

				colOfDstImage[0] = MIN(255, abs(fx) + abs(fy));
			}

		}
	}

	void Canny(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double lowThreshold, double highThreshold, bool L2)
	{
		dstImage.Create(srcImage.rows,srcImage.cols, 1);

		// L2范数计算边缘强度的时候，距离采用平方的方式，所以阈值也需要采用平方
		if (L2)
		{
			lowThreshold = MIN(32767.0, lowThreshold);
			highThreshold = MIN(32767.0, highThreshold);

			if (lowThreshold > 0) lowThreshold *= lowThreshold;
			if (highThreshold > 0) highThreshold *= highThreshold;
		}

		// 计算fx,fy,强度图
		Mat<int> fx(srcImage.rows, srcImage.cols, 1);
		Mat<int> fy(srcImage.rows, srcImage.cols, 1);
		Mat<uchar> enlargedImage;
		Mat<int> magnitudeImage(srcImage.rows + 2, srcImage.cols + 2, 1);
		magnitudeImage.SetTo(Scalar(0));
		CopyMakeBorder(srcImage, enlargedImage, 1, 1, 1, 1);
		int stepOfEnlargedImage = enlargedImage.cols;
		int stepOffx = fx.cols;
		int height = srcImage.rows;
		int width = srcImage.cols;
		uchar *rowOfEnlargedImage = enlargedImage.data + stepOfEnlargedImage + 1;
		int *rowOffx = (int *)fx.data;
		int *rowOffy = (int *)fy.data;
		int *rowOfMagnitudeImage = (int *)magnitudeImage.data + stepOfEnlargedImage + 1;
		for (int y = 0; y <= height - 1; ++y, rowOfEnlargedImage += stepOfEnlargedImage, rowOfMagnitudeImage += stepOfEnlargedImage, rowOffx += stepOffx, rowOffy += stepOffx)
		{
			uchar *colOfEnlargedImage = rowOfEnlargedImage;
			int *colOffx = rowOffx;
			int *colOffy = rowOffy;
			int *colOfMagnitudeImage = rowOfMagnitudeImage;
			for (int x = 0; x <= width - 1; ++x, ++colOfEnlargedImage, ++colOffx, ++colOffy, ++colOfMagnitudeImage)
			{
				// fx
				colOffx[0] = colOfEnlargedImage[1 - stepOfEnlargedImage] + 2 * colOfEnlargedImage[1] + colOfEnlargedImage[1 + stepOfEnlargedImage] -
					colOfEnlargedImage[-1 - stepOfEnlargedImage] - 2 * colOfEnlargedImage[-1] - colOfEnlargedImage[-1 + stepOfEnlargedImage];

				// fy
				colOffy[0] = colOfEnlargedImage[stepOfEnlargedImage - 1] + 2 * colOfEnlargedImage[stepOfEnlargedImage] + colOfEnlargedImage[stepOfEnlargedImage + 1] -
					colOfEnlargedImage[-stepOfEnlargedImage - 1] - 2 * colOfEnlargedImage[-stepOfEnlargedImage] - colOfEnlargedImage[-stepOfEnlargedImage + 1];

				// 计算边缘强度，由于只是用于比较，为了加快速度，只计算平方和
				if (L2)
				{
					colOfMagnitudeImage[0] = colOffx[0] * colOffx[0] + colOffy[0] * colOffy[0];
				}
				else
				{
					colOfMagnitudeImage[0] = abs(colOffx[0]) + abs(colOffy[0]);
				}

			}
		}


		// 非极大抑制，同时标记图做标记,双阈值处理
		//   0 - 可能是边缘
		//   1 - 不是边缘
		//   2 - 一定是边缘
		Mat<uchar> labelImage(srcImage.rows + 2, srcImage.cols + 2, 1);
		memset(labelImage.data, 1, labelImage.rows*labelImage.cols);
		rowOffx = (int *)fx.data;
		rowOffy = (int *)fy.data;
		rowOfMagnitudeImage = (int *)magnitudeImage.data + stepOfEnlargedImage + 1;
		uchar *rowOfLabelImage = labelImage.data + stepOfEnlargedImage + 1;
		queue<uchar*> queueOfEdgePixel;
		for (int y = 0; y <= height - 1; ++y, rowOfMagnitudeImage += stepOfEnlargedImage, rowOffx += stepOffx, rowOffy += stepOffx, rowOfLabelImage += stepOfEnlargedImage)
		{
			int *colOffx = rowOffx;
			int *colOffy = rowOffy;
			int *colOfMagnitudeImage = rowOfMagnitudeImage;
			uchar *colOfLabelImage = rowOfLabelImage;
			for (int x = 0; x <= width - 1; ++x, ++colOffx, ++colOffy, ++colOfMagnitudeImage, ++colOfLabelImage)
			{
				int fx = colOffx[0];
				int fy = colOffy[0];

				// 取绝对值，转换为正数
#if (defined WIN32 || defined _WIN32)
				int abs_fx = std::abs(fx);
				int abs_fy = std::abs(fy);
#else  // Linux中C＋＋标准库有差异
				int abs_fx = abs(fx);
				int abs_fy = abs(fy);
#endif
				

				// 该像素点才有可能是边缘点
				if (colOfMagnitudeImage[0] > lowThreshold)
				{
					// 非极大抑制
					abs_fy = abs_fy << CANNY_SHIFT; // 对正数直接移位

					// 在乘以较小的浮点数的时候，需要进行数据类型转换
					int tan225 = abs_fx * TAN_225;
					int tan675 = abs_fx * TAN_675;

					// 梯度方向0°
					if (abs_fy< tan225)
					{
						// 极大值，有可能是边缘
						if (colOfMagnitudeImage[0] >= colOfMagnitudeImage[-1] && colOfMagnitudeImage[0] >= colOfMagnitudeImage[1])
						{
							// 大于高阈值，是边缘，标记为2
							if (colOfMagnitudeImage[0] > highThreshold)
							{
								// 进入队列，并设置标记
								colOfLabelImage[0] = 2;
								queueOfEdgePixel.push(colOfLabelImage);
							}
							else
							{
								// 有可能是边缘，标记为0
								colOfLabelImage[0] = 0;

							}
						}
					}

					// 梯度方向90°
					if (abs_fy>tan675)
					{
						// 极大值，有可能是边缘
						if (colOfMagnitudeImage[0] >= colOfMagnitudeImage[stepOfEnlargedImage] && colOfMagnitudeImage[0] >= colOfMagnitudeImage[-stepOfEnlargedImage])
						{
							// 大于高阈值，是边缘，标记为2
							if (colOfMagnitudeImage[0] > highThreshold)
							{
								// 进入队列，并设置标记
								colOfLabelImage[0] = 2;
								queueOfEdgePixel.push(colOfLabelImage);
							}
							else
							{
								// 有可能是边缘，标记为0
								colOfLabelImage[0] = 0;

							}

						}

					}

					// 梯度方向45°/-45°
					if (abs_fy > tan225&&abs_fy<tan675)
					{
						int s = (fy*fx) < 0 ? -1 : 1;
						// 极大值，有可能是边缘
						if (colOfMagnitudeImage[0] >= colOfMagnitudeImage[-stepOfEnlargedImage - s] && colOfMagnitudeImage[0] >= colOfMagnitudeImage[stepOfEnlargedImage + s])
						{
							// 大于高阈值，是边缘，标记为2
							if (colOfMagnitudeImage[0] > highThreshold)
							{
								// 进入队列，并设置标记
								colOfLabelImage[0] = 2;
								queueOfEdgePixel.push(colOfLabelImage);
							}
							else
							{
								// 有可能是边缘，标记为0
								colOfLabelImage[0] = 0;

							}

						}

					}

				}
			}

		}

		// 连接性分析,这里采用队列实现，也可以采用栈实现
		// 注意，这里采用递归分析
		// 如果A像素为0，与2在8领域连接，那么标记为2，如果此时有像素值为0的像素与A相邻，则被标记为2,
		while (!queueOfEdgePixel.empty())
		{
			uchar *m = queueOfEdgePixel.front();
			queueOfEdgePixel.pop();

			// 在8领域搜索
			if (!m[-1])
			{
				m[-1] = 2;
				queueOfEdgePixel.push(m - 1);
			}

			if (!m[1])
			{
				m[1] = 2;
				queueOfEdgePixel.push(m + 1);
			}
			if (!m[-stepOfEnlargedImage - 1])
			{
				m[-stepOfEnlargedImage - 1] = 2;
				queueOfEdgePixel.push(m - stepOfEnlargedImage - 1);
			}
			if (!m[-stepOfEnlargedImage])
			{
				m[-stepOfEnlargedImage] = 2;
				queueOfEdgePixel.push(m - stepOfEnlargedImage);
			}
			if (!m[-stepOfEnlargedImage + 1])
			{
				m[-stepOfEnlargedImage + 1] = 2;
				queueOfEdgePixel.push(m - stepOfEnlargedImage + 1);
			}
			if (!m[stepOfEnlargedImage - 1])
			{
				m[stepOfEnlargedImage - 1] = 2;
				queueOfEdgePixel.push(m + stepOfEnlargedImage - 1);
			}
			if (!m[stepOfEnlargedImage])
			{
				m[stepOfEnlargedImage] = 2;
				queueOfEdgePixel.push(m + stepOfEnlargedImage);
			}
			if (!m[stepOfEnlargedImage + 1])
			{
				m[stepOfEnlargedImage + 1] = 2;
				queueOfEdgePixel.push(m + stepOfEnlargedImage + 1);
			}
		}

		// 最后生成边缘图
		rowOfLabelImage = labelImage.data + stepOfEnlargedImage + 1;
		uchar *rowOfDst = dstImage.data;
		for (int y = 0; y <= height - 1; ++y, rowOfLabelImage += stepOfEnlargedImage, rowOfDst += stepOffx)
		{
			uchar *colOfLabelImage = rowOfLabelImage;
			uchar *colOfDst = rowOfDst;
			for (int x = 0; x <= width - 1; ++x, ++colOfDst, ++colOfLabelImage)
			{
				if (colOfLabelImage[0] == 2)
					colOfDst[0] = 255;
				else
				{
					colOfDst[0] = 0;
				}
			}
		}

	}

}// namespace QQ