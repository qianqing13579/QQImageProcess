//////////////////////////////////////////////////////////////////////////
// 内存分配与释放 Alloc.h
// 2016-5-30，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:qianqing13579@163.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_ALLOC_H__
#define __QQ_ALLOC_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "CommonDefinition.h"

namespace QQ
{

	// 实现任意字节对齐的内存分配和释放
	DLL_EXPORTS void *AlignedMalloc(size_t size, int aligned); // aligned常用16或者32
	DLL_EXPORTS void AlignedFree(void *data);



}//end of namespace QQ
#endif