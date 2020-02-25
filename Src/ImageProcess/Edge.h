//////////////////////////////////////////////////////////////////////////
// ±ßÔµ¼ì²â Edge.h
// 2017-1-12£¬by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_EDGE_H__
#define __QQ_EDGE_H__

#include<stddef.h>
#include "Mat.h"
using namespace std;

namespace QQ
{

// Sobel Ëã×Ó
DLL_EXPORTS void Sobel(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// Canny(Canny3),ÍÆ¼öãÐÖµ:low:50 , high:150
DLL_EXPORTS void Canny(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double lowThreshold, double highThreshold, bool L2 = false);









}// namesapce QQ




#endif