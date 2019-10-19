#define DLLAPI_EXPORTS
#include<assert.h>
#include "Alloc.h"

namespace QQ
{
	/////////////////////////////////////////// 内存的分配与释放///////////////////////////////////
	// 实现任意字节对齐的内存分配和释放
	void *AlignedMalloc(size_t size, int aligned)
	{
		// aligned is a power of 2
		assert((aligned&(aligned - 1)) == 0);

		// 分配内存空间
		void *data = malloc(sizeof(void *)+aligned + size);
		//printf("data:%d\n", data);

		// 地址对齐，temp存放的就是地址
		void **temp = (void **)data + 1;
		void **alignedData = (void **)(((size_t)temp + aligned - 1)&-aligned);
		//printf("alignedData:%d\n", alignedData);

		// 保存原始内存地址
		alignedData[-1] = data;

		return alignedData;  // 被转换为一级指针
	}

	void AlignedFree(void *data)
	{
		if (data)
		{
			//printf("data:%d\n", ((void **)data)[-1]);
			free(((void **)data)[-1]);
		}
	}
}//namespace QQ