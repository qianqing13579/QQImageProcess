//////////////////////////////////////////////////////////////////////////
// 灰度变换及颜色空间转换 GrayTransformation.h
// 2014-11-16，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_GRAY_TRANSFORMATION_H__
#define __QQ_GRAY_TRANSFORMATION_H__

#include"Mat.h"
#include"Histogram.h"

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