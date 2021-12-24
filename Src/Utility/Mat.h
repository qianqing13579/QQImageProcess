//////////////////////////////////////////////////////////////////////////
// 矩阵类
// 2016-12-24,by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog:http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////
// Merry Christmas !


#ifndef __MAT_H__
#define __MAT_H__

#include "CommonDefinition.h"
#include "Alloc.h"

namespace QQ
{


template <typename T>
class  DLL_EXPORTS Mat
{
public:
	//构造函数
	Mat();
	Mat(const Mat<T>& m);// 拷贝构造
	Mat(Mat<T>&& m);// 移动构造
	Mat(int _rows, int _cols, int _numberOfChannels);
	Mat(int _rows, int _cols, int _numberOfChannels, Scalar scalar); 
	Mat(int _rows, int _cols, int _numberOfChannels, void *_data, bool needCopyData = false);// 外部数据_data需要外部释放
	
	//析构函数
	virtual ~Mat();//调用Release()
	void Release();//引用计数减1
	void Deallocate();//释放数据

	//自动分配内存
	void Create(int _rows, int _cols, int _numberOfChannels);
	void Create(Size _size, int _numberOfChannels);

	//重载赋值操作符
	Mat& operator = (const Mat &dstMat);//共享数据

	void SetTo(const Scalar &scalar);

	// 获取指定位置的元素
	template<typename _Tp>
	inline _Tp& At(int y, int x)
	{
		return ((_Tp*)(data + step*y))[x];
	}

	void InitEmpty();

public:
	int rows;
	int cols;
	int numberOfChannels;//通道数
	int step;// 步长(每行字节数)
	
	uchar *data;	

	//引用计数
	int *refCount;// 如果为空，表示不需要释放内存(使用了外部数据)

};// Mat


//////////////////////////////Mat的实现////////////////////////////////////////////

template <typename T>
inline Mat<T>::Mat()
{
	InitEmpty();

}

template <typename T>
inline Mat<T>::Mat(const Mat<T> &m)
{
	// 引用计数加1
	refCount = m.refCount;
	if(refCount!=NULL)
	{
		(*refCount)++;
	}

	rows = m.rows;
	cols = m.cols;
	numberOfChannels = m.numberOfChannels;
	step = m.step;
	data = m.data; 

}

// 移动构造
template <typename T>
inline Mat<T>::Mat(Mat<T> &&m)
{
	// 移动资源
	data = m.data;
	refCount = m.refCount;
	rows = m.rows;
	cols = m.cols;
	numberOfChannels = m.numberOfChannels;
	step = m.step;

	// 使得m运行析构函数是安全的
	m.refCount=NULL;
	
}

template <typename T>
inline void Mat<T>::InitEmpty()
{
	rows = cols = numberOfChannels = 0;
	data = 0;
	refCount = NULL;

}

template <typename T>
inline Mat<T>::Mat(int _rows, int _cols, int _numberOfChannels)
{
	InitEmpty();
	Create(_rows, _cols, _numberOfChannels);
}

template <typename T>
inline Mat<T>::Mat(int _cols, int _rows, int _numberOfChannels, Scalar scalar)
{
	InitEmpty();
	Create(_cols, _rows, _numberOfChannels);

	SetTo(scalar);

}

//默认不拷贝数据,外部数据_data需要外部释放
template <typename T>
inline Mat<T>::Mat(int _rows, int _cols, int _numberOfChannels, void *_data, bool needCopyData)
{
	rows = _rows;
	cols = _cols;
	numberOfChannels = _numberOfChannels;
	step = cols*numberOfChannels*sizeof(T);

	if (needCopyData == false)
	{
		data=(uchar *)_data;

		refCount = NULL;
	}
	else
	{
		data = (uchar *)AlignedMalloc((step*rows + (int)sizeof(int)), 16);

		refCount = (int*)(data + step*rows);
		*refCount = 1;

		memcpy(data, _data, step*rows);//拷贝
	}


}
template <typename T>
Mat<T>::~Mat()
{
	Release();//释放
}

// 引用计数减1，如果引用计数为0了，调用Deallocate()
template <typename T>
inline void Mat<T>::Release()
{
	//引用计数减1,如果引用计数为0，说明没有引用，释放数据
	if ((refCount!=NULL) && ((*refCount)-- == 1))
	{
		Deallocate();
	}

	InitEmpty();

}
//释放数据
template <typename T>
inline void Mat<T>::Deallocate()
{

	AlignedFree(data);


}

template <typename T>
inline void Mat<T>::Create(int _rows, int _cols, int _numberOfChannels)
{
	if (rows == _rows&&cols == _cols&&numberOfChannels == _numberOfChannels)
	{
		return;
	}
	else
	{
		//如果不一致，引用计数减1,此时引用计数为0，释放数据和引用计数
		Release();

		rows = _rows;
		cols = _cols;
		numberOfChannels = _numberOfChannels;
		step = cols*numberOfChannels*sizeof(T);

		// 内存地址16字节对齐(用于指令集优化)
		data = (uchar *)AlignedMalloc((step*rows + (int)sizeof(int)), 16);

		refCount = (int*)(data + step*rows);
		*refCount = 1;

	}
}

template <typename T>
inline void Mat<T>::Create(Size _size, int _numberOfChannels)
{
	int _rows = _size.height;
	int _cols = _size.width;

	Create(_rows, _cols, _numberOfChannels);
}

//重载操作符
template <typename T>
inline Mat<T>& Mat<T>::operator = (const Mat<T> &dstMat)
{
	if (this != &dstMat)
	{
		// 调用this的release
		Release();

		rows = dstMat.rows;
		cols = dstMat.cols;
		numberOfChannels = dstMat.numberOfChannels;
		step = dstMat.step;

		data = dstMat.data;

		//引用计数
		refCount = dstMat.refCount;
		if(refCount!=NULL)
		{
			(*refCount)++;
		}
			
	}

	return *this;

}

template <typename T>
void Mat<T>::SetTo(const Scalar &scalar)
{
	T *dataOfSrc = (T *)data;
	int numberOfElement = rows*cols;
	for (int i = 0; i <= numberOfElement - 1; ++i, dataOfSrc += numberOfChannels)
	{
		for (int k = 0; k <= numberOfChannels - 1; ++k)
			dataOfSrc[k] = scalar.val[k];
	}

}

}// namespace QQ
#endif
