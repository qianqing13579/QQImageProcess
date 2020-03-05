// Copyright (c) 2014-2020, QQ<654393155@qq.com>, all rights reserved.

// ±ßÔµ¼ì²â

#ifndef __EDGE_H__
#define __EDGE_H__

#include "Mat.h"

namespace QQ
{

// Sobel Ëã×Ó
DLL_EXPORTS void Sobel(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// Canny(Canny3),ÍÆ¼öãÐÖµ:low:50 , high:150
DLL_EXPORTS void Canny(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double lowThreshold, double highThreshold, bool L2 = false);









}// namesapce QQ




#endif
