//////////////////////////////////////////////////////////////////////////
// Windows下Bmp图定义 Bmp_Definition_Windows.h
// 2014-11-13，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.ww
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_BMP_DEFINITION_WINDOWS_H__
#define __QQ_BMP_DEFINITION_WINDOWS_H__

/*************************Windows BMP 类型定义******************************/
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef long				LONG;

#pragma  pack(1)//禁止VC字节对齐
typedef struct tagBITMAPFILEHEADER {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

#pragma pack()
//
//
//
#endif