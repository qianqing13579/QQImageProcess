// Copyright (c) 2014-2020, QQ<654393155@qq.com>, all rights reserved.

// 灰度变换及颜色空间转换

#ifndef __GRAY_TRANSFORMATION_H__
#define __GRAY_TRANSFORMATION_H__

#include"Mat.h"

namespace QQ
{

// 灰度化
DLL_EXPORTS void RGB2Gray(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 求灰度图的平均灰度
DLL_EXPORTS int ComputeMeanGray(const Mat<uchar> &srcImage);

// 直方图均衡化(通过灰度变换实现)
DLL_EXPORTS void EqualizeHistogram(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);


}//namespace QQ



#endif
