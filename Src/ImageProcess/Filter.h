//////////////////////////////////////////////////////////////////////////
// 滤波
// 2014-12-10,by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __FILTER_H__
#define __FILTER_H__

#include "Mat.h"

namespace QQ
{

// 均值滤波(V4.0)
DLL_EXPORTS void Blur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, Size kernelSize);

// 中值滤波(V4.0)
// width_Aperture:滑动窗口大小
DLL_EXPORTS void MedianBlur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, int width_Aperture);

// 高斯滤波
// sigma：标准差，常用值：0.84089642
DLL_EXPORTS void GaussianBlur(const Mat<uchar> &srcImage, Mat<uchar> &dstImage, double sigma);

// Gabor 滤波,获取Gabor滤波核
// D:\Library\OpenCV\OpenCV_2.4.12\sources\modules\imgproc\src\gabor.cpp
DLL_EXPORTS Mat<float> GetGaborKernel(Size ksize, double sigma, double theta, double lambd, double gamma, double psi = PI*0.5);

// 卷积运算(Convolution22),只支持单通道
DLL_EXPORTS void Convolution(const Mat<uchar> &srcImage, const Mat<float> &kernel, Mat<uchar> &dstImage);

















}//end of namespace QQ

#endif
