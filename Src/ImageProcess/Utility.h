//////////////////////////////////////////////////////////////////////////
// 常用工具 Utility.h
// 2016-12-25，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:qianqing13579@163.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_UTILITY_H__
#define __QQ_UTILITY_H__

#include "Mat.h"

namespace QQ
{

	// 边界扩充，使用0扩充
	DLL_EXPORTS void CopyMakeBorder(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, int top, int bottom, int left, int right);

	// 计算积分图
	//dstImage:积分图
	DLL_EXPORTS void ComputeIntegralImage(const Mat<uchar> &srcImage, Mat<int> &dstImage);//改进的方法




}//end of namespace QQ
#endif