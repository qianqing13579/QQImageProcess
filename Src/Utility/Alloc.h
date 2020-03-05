// Copyright (c) 2014-2020, QQ<654393155@qq.com>, all rights reserved.

// 内存分配与释放

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
