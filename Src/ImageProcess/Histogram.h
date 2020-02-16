//////////////////////////////////////////////////////////////////////////
// 直方图相关  Histogram.h
// 2014-12-6，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:qianqing13579@163.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////
// updated 2016-12-25 by QQ，2.0

#ifndef __QQ_HISTOGRAM_H__
#define __QQ_HISTOGRAM_H__
#include "Mat.h"

namespace QQ
{

// 计算直方图
DLL_EXPORTS void CalculateHistogram(const Mat<uchar> &srcImage,Mat<int> &histogram);


}//namespace QQ



#endif