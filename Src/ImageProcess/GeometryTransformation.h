//////////////////////////////////////////////////////////////////////////
// 几何变换 GeometryTransformation.h
// 2014-11-11，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:qianqing13579@163.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////
// updated 2016-12-21 by QQ,add CopyMakeBorder,Rotate
// updated 2017-1-12 by QQ,add VerticalFlip,HorizontalFlip

#ifndef __QQ_GEOMETRY_TRANSFORMATION_H__
#define __QQ_GEOMETRY_TRANSFORMATION_H__

#include "Mat.h"
#include "Utility.h"

#define  ROTATE_SHIFT  8

namespace QQ
{
/////////////////////////////////仿射变换/////////////////////////////////////////
// 仿射变换：srcImage绕点center旋转theta角度（顺时针为正）,缩放scale,平移到dstSize中
// dstSize:目标图像大小
// theta:单位角度
// scale:缩放比例,>1 放大，<1 缩小
DLL_EXPORTS void Rotate(const Mat<uchar> &srcImage, Point center, double theta, double scale, Size dstSize, Mat<uchar> &dstImage);

// 绕图像中心顺时针旋转90
DLL_EXPORTS void Rotate90(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 绕图像中心顺时针旋转270
DLL_EXPORTS void Rotate270(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 垂直翻转
DLL_EXPORTS void VerticalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);

// 水平翻转
DLL_EXPORTS void HorizontalFlip(const Mat<uchar> &srcImage, Mat<uchar> &dstImage);


}//namespace QQ


#endif