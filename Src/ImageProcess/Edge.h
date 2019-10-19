//////////////////////////////////////////////////////////////////////////
// ±ßÔµ¼ì²â Edge.h
// 2017-1-12£¬by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Telephone:17761745857
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////


#ifndef __EDGE_H__
#define __EDGE_H__

#include<stddef.h>
#include<queue>
#include "Mat.h"
#include"Utility.h"
using namespace std;


#define CANNY_SHIFT 16
#define TAN_225  (int)(0.4142135623730950488016887242097*(1 << CANNY_SHIFT));
#define TAN_675  (int)(2.4142135623730950488016887242097*(1 << CANNY_SHIFT));

namespace QQ
{

	// Sobel Ëã×Ó
	DLL_EXPORTS void Sobel(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

	// Canny,from Canny3,ÍÆ¼öãÐÖµ:low:50 , high:150
	DLL_EXPORTS void Canny(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double lowThreshold, double highThreshold, bool L2 = false);









}// namesapce QQ




#endif