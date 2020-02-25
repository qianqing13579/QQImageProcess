//////////////////////////////////////////////////////////////////////////
// Linux下Bmp图定义 Bmp_TypeDefinition_Linux.h
// 2014-11-13，by QQ
//
// Please contact me if you find any bugs, or have any suggestions.
// Contact:
//		Email:654393155@qq.com
//		Blog: http://blog.csdn.net/qianqing13579
//////////////////////////////////////////////////////////////////////////

#ifndef __QQ_BMP_DEFINITION_LINUX_H__
#define __QQ_BMP_DEFINITION_LINUX_H__

/*************************Linux BMP 类型定义******************************/
typedef unsigned short WORD; //2字节无符号
typedef unsigned int DWORD;  //4字节无符号
typedef int LONG;           //4字节有符号use int not long here!!!
typedef unsigned char BYTE; //

//BMP图相关定义
typedef struct tagBITMAPFILEHEADER  //bitmapfileheader
{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
}__attribute__ ((packed))BITMAPFILEHEADER;//禁止对齐
typedef struct tagBITMAPINFOHEADER  //bitmapinfoheader
{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
}__attribute__ ((packed))BITMAPINFOHEADER;
typedef struct tagRGBQUAD //ColorTable
{
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE reserved;
}__attribute__ ((packed))RGBQUAD;



#endif // TYPEDEFINE_H
//
