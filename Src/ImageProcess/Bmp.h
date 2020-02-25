//////////////////////////////////////////////////////////////////////////
// 读写BMP图  Bmp.h
// 2014-11-12，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_BMP_H__
#define __QQ_BMP_H__

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

// 读BMP
DLL_EXPORTS void ReadBmp(const string &fileName,Mat<uchar> &image);

// 写BMP
DLL_EXPORTS void WriteBmp(const string &fileName, const Mat<uchar> &image);

// 标记BMP图
DLL_EXPORTS void WriteMarkedBMP(const string &fileName, const Mat<uchar>& image);

}//namespace QQ
#endif