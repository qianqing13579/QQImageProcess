#define DLLAPI_EXPORTS

#include "Histogram.h"

namespace QQ
{

void CalculateHistogram(const Mat<uchar> &srcImage, Mat<int> &histogram)
{
	histogram.Create(1, 256, 1);
	histogram.SetTo(Scalar(0));
	
	int pixelCount = srcImage.rows*srcImage.cols;
	uchar *dataOfSrc = srcImage.data;
	int *dataOfHistogram = (int *)histogram.data;
	for (int i = 0; i <= pixelCount - 1; ++i)
	{
		dataOfHistogram[dataOfSrc[i]]++;
	}
}



}//end of namespace QQ

