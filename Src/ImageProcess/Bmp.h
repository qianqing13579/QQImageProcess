//////////////////////////////////////////////////////////////////////////
// 读写BMP图  Bmp.h
// 2014-11-12，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Telephone:17761745857
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////


#ifndef __BMP_H__
#define __BMP_H__
#include "Mat.h"
#include "CommonDefinition.h"
#if (defined WIN32 || defined _WIN32)
#include "BmpDefinition_Windows.h" // 在Linux中使用 BmpDefinition_Linux.h
#else
#include "BmpDefinition_Linux.h"
#endif
#include <string>
using namespace std;

namespace QQ
{

// C++接口（支持8位单通道和3通道）
DLL_EXPORTS void ReadBmp(const string &fileName,Mat<uchar> &image);// 读BMP
DLL_EXPORTS void WriteBmp(const string &fileName, const Mat<uchar> &image);// 写BMP
DLL_EXPORTS void WriteMarkedBMP(const string &fileName, const Mat<uchar>& image);// 标记BMP图

// C接口
DLL_EXPORTS uchar *ReadBmp_C(const char * fileName, int &width, int &height, int &bitCount_PerPixel);
DLL_EXPORTS bool WriteBmp_C(uchar *image, int width, int height, const char * fileName, int bitCount_PerPixel);
DLL_EXPORTS bool WriteMarkedBmp_C(uchar *image, int width, int height, const char * filename);

}//namespace QQ
#endif