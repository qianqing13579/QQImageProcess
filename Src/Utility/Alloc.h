//////////////////////////////////////////////////////////////////////////
// 内存分配与释放
// 2016-5-30,by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __ALLOC_H__
#define __ALLOC_H__

#include "CommonDefinition.h"

namespace QQ
{

// 实现任意字节对齐的内存分配和释放
DLL_EXPORTS void *AlignedMalloc(int size, int aligned); // aligned常用16或者32
DLL_EXPORTS void AlignedFree(void *data);



}//end of namespace QQ
#endif
