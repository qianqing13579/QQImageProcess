// Copyright (c) 2014-2020, QQ<654393155@qq.com>, all rights reserved.

// 常用工具

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Mat.h"

namespace QQ
{

// 边界扩充，使用0扩充
DLL_EXPORTS void CopyMakeBorder(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, int top, int bottom, int left, int right);

// 计算积分图(CalculateIntegralImage)
//dstImage:积分图
DLL_EXPORTS void ComputeIntegralImage(const Mat<uchar> &srcImage, Mat<int> &dstImage);

}//end of namespace QQ
#endif
