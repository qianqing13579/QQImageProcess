#define DLLAPI_EXPORTS
#include "Bmp.h"
#if (defined WIN32 || defined _WIN32)
#include "BmpDefinition_Windows.h" // 在Linux中使用 BmpDefinition_Linux.h
#else
#include "BmpDefinition_Linux.h"
#endif
namespace QQ
{


void ReadBmp(const string &fileName, Mat<uchar> &image)
{
	//图像参数
	int width,height,bitCount_PerPixel;
	
	//读BMP
	uchar *data=ReadBmp_C(fileName.c_str(),width,height,bitCount_PerPixel);
	
	//设置图像头
	int numberOfChannels = bitCount_PerPixel >> 3;
	Mat<uchar> temp(height, width, numberOfChannels, data, true);

	image = temp;

	delete[] data;

}

void WriteBmp(const string &fileName, const Mat<uchar> &image)
{
	//写入bmp
	int bitCount_PerPixel=image.numberOfChannels<<3;
	WriteBmp_C(image.data,image.cols,image.rows,fileName.c_str(),bitCount_PerPixel);
}
void WriteMarkedBMP(const string &fileName, const Mat<uchar> &image)
{
	WriteMarkedBmp_C(image.data, image.cols, image.rows, fileName.c_str());
}

///读取8位或者24位Bmp
///返回原始图像数据，未对齐的数据
uchar *ReadBmp_C(const char * fileName,
	int &width, int &height,//图像大小(像素的宽度和高度)
	int &bitCount_PerPixel//返回图像的每像素位数
	)
{
	FILE *fp;
	BITMAPFILEHEADER bitmap_FileHeader;
	BITMAPINFOHEADER bitmap_InfoHeader;
	RGBQUAD *colorTable;
	bool isSuccess = true;

	width = height = 0;
	if ((fp = fopen(fileName, "rb")) == NULL)
		return NULL;

	// 读入文件头和信息头内的信息
	if (fread((void *)&bitmap_FileHeader, 1, sizeof(BITMAPFILEHEADER), fp) != sizeof(BITMAPFILEHEADER))
		isSuccess = false;
	if (fread((void *)&bitmap_InfoHeader, 1, sizeof(BITMAPINFOHEADER), fp) != sizeof(BITMAPINFOHEADER))
		isSuccess = false;
	if ((isSuccess == false) || (bitmap_FileHeader.bfOffBits<sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)))
	{
		fclose(fp);
		return NULL;
	}
	width = bitmap_InfoHeader.biWidth;
	height = bitmap_InfoHeader.biHeight;
	bitCount_PerPixel = bitmap_InfoHeader.biBitCount;//每像素位数
	int ucharCount_PerPixel = bitCount_PerPixel / 8;
	int dataSize = bitmap_InfoHeader.biSizeImage;

	// 读入颜色表(8位的有，24位的没有)
	if (bitCount_PerPixel == 8)
	{
		//申请颜色表所需要的空间，读颜色表进内存
		colorTable = new RGBQUAD[256];
		int count = fread(colorTable, sizeof(RGBQUAD), 256, fp);
		if (count != 256)//读取颜色表错误
		{
			isSuccess = false;
			return NULL;
		}
		//输出颜色表信息结构体
		/*FILE *outFile;
		fopen_s(&outFile, "D:output.txt", "w");
		for (int i = 0; i < 256; i++)
		{
		fprintf_s(outFile, "colorTable[%d]\n", i);
		fprintf_s(outFile, "\tB:%d\n", colorTable[i].rgbBlue);
		fprintf_s(outFile, "\tG:%d\n", colorTable[i].rgbGreen);
		fprintf_s(outFile, "\tR:%d\n", colorTable[i].rgbRed);
		}
		fclose(outFile);*/
	}


	// 读取图像数据	
	// 读取图像数据，由于BMP扫描方式是从下到上，所以BMP图像存储方式是从下到上，所以读的时候，需要倒着读取
	int ucharCount_PerLine = (width*ucharCount_PerPixel + 3) / 4 * 4;//存储中，每行字节数(4字节对齐)
	uchar *image_Src = new uchar[height*width*ucharCount_PerPixel];
	uchar temp;
	int extend = ucharCount_PerLine - width*ucharCount_PerPixel;//每行由于四字节对其而需要补充的字节数
	for (int i = 0; i<height; i++)
	{
		int readCount = fread(image_Src + (height - 1 - i)*width * ucharCount_PerPixel, sizeof(uchar), width* ucharCount_PerPixel, fp);
		if (readCount != width * ucharCount_PerPixel)
		{
			fclose(fp);
			delete[]image_Src;
			image_Src = NULL;
			return NULL;
		}
		for (int k = 0; k<extend; k++) // 扩充的数据
		{
			if (fread(&temp, sizeof(uchar), 1, fp) != 1)
			{
				fclose(fp);
				delete[] image_Src;
				image_Src = NULL;
				return NULL;

			}
		}
	}
	fclose(fp);
	return image_Src;
}



////写入原始图像数据，未对齐的数据
///8位或者24位
bool WriteBmp_C(uchar *imageData, //原始图像数据
	int width, int height, //Bmp图像大小
	const char *fileName,
	int bitCount_PerPixel//Bmp每个像素的位数
	)
{
	FILE * fp;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int colorTableSize = 0;
	int i;
	bool isSuccess = true;
	uchar p[4];//颜色表

	if ((fp = fopen(fileName, "wb")) == NULL)
	{
		return false;
	}

	// 写文件头fileHeader
	// 文件头+信息头+颜色表
	bitmapFileHeader.bfType = ((WORD)('M' << 8) | 'B');
	if (bitCount_PerPixel == 8)//8bit Bmp
	{
		colorTableSize = 1024;
	}
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTableSize;
	int ucharCount_PerPixel = bitCount_PerPixel / 8;
	int ucharCount_PerLine = (width*ucharCount_PerPixel + 3) / 4 * 4;//4字节对齐
	bitmapFileHeader.bfSize = bitmapFileHeader.bfOffBits + ucharCount_PerLine*height;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	if (fwrite((void *)&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), fp) != sizeof(BITMAPFILEHEADER))
		isSuccess = false;


	// 写信息头
	bitmapInfoHeader.biSize = 40;
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bitCount_PerPixel;
	bitmapInfoHeader.biCompression = 0;
	bitmapInfoHeader.biSizeImage = height*ucharCount_PerLine;//图像数据部分，4字节对齐
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	if (fwrite((void *)&bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), fp) != sizeof(BITMAPINFOHEADER))
		isSuccess = false;

	// 写入颜色表(8位有颜色表，24位的没有颜色表)
	///8位BMP图像数据部分存储的是颜色表的索引
	if (bitCount_PerPixel == 8)
	{
		for (i = 0, p[3] = 0; i<256; i++)//8位颜色表长度256，4位为16
		{
			p[3] = 0;
			p[0] = i;//B
			p[1] = i;//G
			p[2] = i; //R
			if (fwrite((void *)p, 1, 4, fp) != 4)
			{
				isSuccess = false;
				break;
			}
		}
	}


	// 写入图像数据
	// 由于BMP扫描方式是从下到上，所以BMP图像存储方式是从下到上，所以写的时候，需要倒着写
	int extend = ucharCount_PerLine - width * ucharCount_PerPixel;
	int writeCount;
	uchar *temp;
	if (extend == 0)
	{
		for (temp = imageData + (height - 1) * ucharCount_PerPixel * width; temp >= imageData; temp -= ucharCount_PerPixel * width)
		{
			writeCount = fwrite((void *)temp, 1, width * ucharCount_PerPixel, fp);
			if (writeCount != (unsigned int)(ucharCount_PerPixel * width))
				isSuccess = false; // 真实的数据
		}
	}
	else
	{
		for (temp = imageData + (height - 1) * ucharCount_PerPixel * width; temp >= imageData; temp -= ucharCount_PerPixel * width)
		{
			writeCount = fwrite((void *)temp, 1, width * ucharCount_PerPixel, fp);
			if (writeCount != (unsigned int)(ucharCount_PerPixel * width))
				isSuccess = false; // 真实的数据
			for (i = 0; i<extend; i++) // 扩充的数据，数据内容不限
			{
				writeCount = fwrite((void *)(temp + ucharCount_PerPixel* (width - 1)), 1, 1, fp);
				if (writeCount != 1)
					isSuccess = false;
			}
		}
	}
	// Return;
	fclose(fp);
	return isSuccess;
}

//灰度图中用颜色标记信息
bool WriteMarkedBmp_C(uchar *image,
	int width, int height, //Bmp图像大小
	const char * filename
	)
{

	FILE * fp;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	int colorTableSize = 0;
	int i;
	bool isSuccess = true;
	uchar colorTableItem[4];//颜色表项
	int bitCount_PerPixel = 8;//Bmp每个像素的位数

	if ((fp = fopen(filename, "w+b")) == NULL)
	{
		return false;
	}

	// 写文件头fileHeader
	// 文件头+信息头+颜色表
	bitmapFileHeader.bfType = ((WORD)('M' << 8) | 'B');
	if (bitCount_PerPixel == 8)//8bit Bmp
	{
		colorTableSize = 1024;
	}
	bitmapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+colorTableSize;
	int ucharCount_PerPixel = bitCount_PerPixel / 8;
	int ucharCount_PerLine = (width*ucharCount_PerPixel + 3) / 4 * 4;//4字节对齐
	bitmapFileHeader.bfSize = bitmapFileHeader.bfOffBits + ucharCount_PerLine*height;
	bitmapFileHeader.bfReserved1 = 0;
	bitmapFileHeader.bfReserved2 = 0;
	if (fwrite((void *)&bitmapFileHeader, 1, sizeof(BITMAPFILEHEADER), fp) != sizeof(BITMAPFILEHEADER))
		isSuccess = false;

	// 写信息头
	bitmapInfoHeader.biSize = 40;
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biBitCount = bitCount_PerPixel;
	bitmapInfoHeader.biCompression = 0;
	bitmapInfoHeader.biSizeImage = height*ucharCount_PerLine;//图像数据部分，4字节对齐
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biClrImportant = 0;
	if (fwrite((void *)&bitmapInfoHeader, 1, sizeof(BITMAPINFOHEADER), fp) != sizeof(BITMAPINFOHEADER))
		isSuccess = false;

	// 写入颜色表(8位有颜色表，24位的没有颜色表),注意通道顺序：BGR
	///8位BMP图像数据部分存储的是颜色表的索引
	if (bitCount_PerPixel == 8)
	{
		for (i = 0; i < 256; i++)
		{
			colorTableItem[3] = 0;
			switch (i) //还可以定义其他颜色R = 0，B = 255, G = 255:青色
			{
			case 255://红色
			{
						 colorTableItem[0] = 0;
						 colorTableItem[1] = 0;
						 colorTableItem[2] = 255;//R
						 break;
			}
			case 254://绿色
			{
						 colorTableItem[0] = 0;
						 colorTableItem[1] = 255;//G
						 colorTableItem[2] = 0;
						 break;
			}
			case 253://蓝色
			{
						 colorTableItem[0] = 255;//B
						 colorTableItem[1] = 0;
						 colorTableItem[2] = 0;
						 break;
			}
			case 252://黄色
			{
						 colorTableItem[0] = 0;//B
						 colorTableItem[1] = 255;//G
						 colorTableItem[2] = 255;//R
						 break;
			}
			case 251://紫色
			{
						 colorTableItem[0] = 255;//B
						 colorTableItem[1] = 0;//G
						 colorTableItem[2] = 255;//R
						 break;
			}
			default:
			{
					   colorTableItem[0] = i;//B
					   colorTableItem[1] = i;//G
					   colorTableItem[2] = i; //R
					   break;
			}
			}
			if (fwrite((void *)colorTableItem, 1, 4, fp) != 4)
			{
				isSuccess = false;
				break;
			}
		}
	}


	// 写入图像数据
	// 由于BMP扫描方式是从下到上，所以BMP图像存储方式是从下到上，所以写的时候，需要倒着写进文件
	int extend = ucharCount_PerLine - width * ucharCount_PerPixel;
	uchar *temp;
	if (extend == 0)
	{
		for (temp = image + (height - 1) * ucharCount_PerPixel * width; temp >= image; temp -= ucharCount_PerPixel * width)
		{
			if (fwrite((void *)temp, 1, width * ucharCount_PerPixel, fp) != (unsigned int)(ucharCount_PerPixel * width))
				isSuccess = false; // 真实的数据
		}
	}
	else
	{
		for (temp = image + (height - 1) * ucharCount_PerPixel * width; temp >= image; temp -= ucharCount_PerPixel * width)
		{
			if (fwrite((void *)temp, 1, width * ucharCount_PerPixel, fp) != (unsigned int)(ucharCount_PerPixel * width))
				isSuccess = false; // 真实的数据
			for (i = 0; i < extend; i++) // 扩充的数据，数据内容不限
			{
				if (fwrite((void *)(temp + ucharCount_PerPixel* (width - 1)), 1, 1, fp) != 1)
					isSuccess = false;
			}
		}
	}

	// Return;
	fclose(fp);
	return isSuccess;
}

}// namespace QQ