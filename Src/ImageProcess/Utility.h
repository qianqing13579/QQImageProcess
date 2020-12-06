//////////////////////////////////////////////////////////////////////////
// 常用工具
// 2016-12-25,by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

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
