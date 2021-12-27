﻿//////////////////////////////////////////////////////////////////////////
// 几何变换
// 2014-11-11,by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __GEOMETRY_TRANSFORMATION_H__
#define __GEOMETRY_TRANSFORMATION_H__

#include "Mat.h"

namespace QQ
{
// 仿射变换(Rotate_Bilinear)：srcImage绕点center旋转theta角度（顺时针为正）,缩放scale,平移到dstSize中
// dstSize:目标图像大小
// theta:单位角度
// scale:缩放比例,>1 放大，<1 缩小
DLL_EXPORTS void Rotate(const Mat<uchar> &srcImage, Point center, double theta, double scale, Size dstSize, Mat<uchar> &dstImage);

// 绕图像中心顺时针旋转90(通过将Rotate的参数center,theta,scale,dstSize设置为常量)
DLL_EXPORTS void Rotate90(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 绕图像中心顺时针旋转180
DLL_EXPORTS void Rotate180(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 绕图像中心顺时针旋转270
DLL_EXPORTS void Rotate270(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 垂直翻转
DLL_EXPORTS void VerticalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 水平翻转
DLL_EXPORTS void HorizontalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);


}//namespace QQ


#endif
