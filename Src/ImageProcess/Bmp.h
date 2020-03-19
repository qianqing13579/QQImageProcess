//////////////////////////////////////////////////////////////////////////
// ¶ÁÐ´BMPÍ¼
// 2014-11-12£¬by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __BMP_H__
#define __BMP_H__

#include "Mat.h"
#include <string>
using namespace std;

namespace QQ
{

// ¶ÁBMP
DLL_EXPORTS void ReadBmp(const string &fileName,Mat<uchar> &image);

// Ð´BMP
DLL_EXPORTS void WriteBmp(const string &fileName, const Mat<uchar> &image);

// ±ê¼ÇBMPÍ¼
DLL_EXPORTS void WriteMarkedBMP(const string &fileName, const Mat<uchar>& image);

}//namespace QQ
#endif
