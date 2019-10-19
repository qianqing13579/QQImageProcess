//////////////////////////////////////////////////////////////////////////
// 灰度变换及颜色空间转换 GrayTransformation.h
// 2014-11-16，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Telephone:17761745857
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////
// updated 2016-12-25 by QQ

#ifndef __GRAY_TRANSFORMATION_H__
#define __GRAY_TRANSFORMATION_H__

#include"Mat.h"
#include"Histogram.h"

namespace QQ
{
	///////////////////////////////颜色空间转换///////////////////////////////////////////////
	// 灰度化
	DLL_EXPORTS void RGB2Gray(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

	// 求灰度图的平均灰度
	DLL_EXPORTS int ComputeMeanGray(const Mat<uchar> &srcImage);


	///////////////////////////////灰度变换///////////////////////////////////////////////
	// 直方图均衡化
	DLL_EXPORTS void EqualizeHistogram(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);


}//namespace QQ



#endif