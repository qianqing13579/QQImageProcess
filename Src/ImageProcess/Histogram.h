//////////////////////////////////////////////////////////////////////////
// 直方图相关  Histogram.h
// 2014-12-6，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Telephone:17761745857
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////
// updated 2016-12-25 by QQ，2.0

#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__
#include "Mat.h"

namespace QQ
{

// 计算直方图
DLL_EXPORTS void CalculateHistogram(const Mat<uchar> &srcImage,Mat<int> &histogram);


}//namespace QQ



#endif