typedef struct
{
	int     x;
	int     y;
} IMG_COORD;

typedef struct
{
	double     x;
	double     y;
} IMG_LCOORD;

struct ROIRect
{
	IMG_COORD topleft;
	IMG_COORD bottomright;
};

struct ROI
{
	int Area = 0;
	double mean = 0;
	double var = 0;
	IMG_LCOORD center;
	ROIRect region;
	IMG_COORD *coordinate = NULL;
	bool vaild = true;
};

/**********************************************/
// ContourInit_8u16u
//		连通域初始化
// Input:
// 		Ipp8u  *pSrc;			输入图像头地址
//		int srcStep;			输入图像跨度
//		Ipp16u *pDst;			输入待分配连通域的图像头地址
//		int dstStep;			输入连通域图像跨度
//		IppiSize size;			输入图像尺寸
// Output:
//		Ipp16u *pDst;			输出连通域图像的头地址
// 		int &nRoi;				输出连通域个数
// Return:
//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-Roi提取数不足或超限 -1-IPP调用出错 其他-待定
// Auther: Shao Yang 12/19/2017
/**********************************************/
int ContourInit_8u16u(Ipp8u *pSrc,int srcStep, Ipp16u *pDst,int dstStep, IppiSize size, int &nRoi)
{
	if (!pSrc || !pDst)
		return 1;
	if (size.width <= 0 || size.height <= 0 || srcStep <= 0 || dstStep <= 0)
		return 2;
	IppStatus status = ippStsNoErr;
	int buffersize = 0;

	//IplImage *img = cvCreateImage(cvSize(size.width, size.height), 8, 1);
	//ippiCopy_8u_C1R(pSrc, srcStep, (Ipp8u*)img->imageData, img->widthStep, size);
	//cvNamedWindow("img", 0);
	//cvShowImage("img", img);
	//cvWaitKey(0);

	//计算连通域分配所需空间
	status = ippiLabelMarkersGetBufferSize_16u_C1R(size, &buffersize);
	if (status != ippStsNoErr)
		return -1;
	//申请临时分配连通域空间
	Ipp8u *buffer = (Ipp8u*)ippsMalloc_8u(buffersize);
	ippiConvert_8u16u_C1R(pSrc, srcStep, pDst, dstStep, size);
	//分配连通域
	status = ippiLabelMarkers_16u_C1IR(pDst, dstStep, size, 1, 65534, ippiNormInf, &nRoi, buffer);
	if (status != ippStsNoErr)
	{
		ippsFree(buffer);
		return -1;
	}
	if (nRoi <= 0 || nRoi > 65534)
	{
		nRoi = 0;
		ippsFree(buffer);
		return 3;
	}
	ippsFree(buffer);
	return 0;
}
/**********************************************/
// AllocationContours
//		获取连通区的面积，形心，区域，以及坐标
// Input:
// 		Ipp16u *Contour;		输入连通图像头地址
//		IppiSize size;			输入图像尺寸
//		int nRoi;				输入连通域个数
//		int AreaLow;			面积最低限制
//		int AreaHigh;			面积最高限制
// Output:
// 		ROI *roi;				连通域属性
// Return:
//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-roi连通属性数组未分配空间 -1-IPP调用出错 其他-待定
// Auther: Shao Yang 12/19/2017
/**********************************************/
int AllocationContours(Ipp16u *Contour, IppiSize size, int nRoi, ROI *roi, int AreaLow, int AreaHigh)
{
	if (!Contour)
		return 1;
	if (size.width <= 0 || size.height <= 0)
		return 2;
	if (!roi)
		return 3;

	int low, high;
	if (AreaLow <= AreaHigh)
	{
		low = AreaLow;
		high = AreaHigh;
	}
	else
	{
		low = AreaHigh;
		high = AreaLow;
	}
	for (int i = 0; i < nRoi; i++)
	{
		roi[i].region.topleft = { (int)size.width, (int)size.height };
		roi[i].region.bottomright = { 0,0 };
		roi[i].Area = 0;
		roi[i].center = { 0,0 };
		roi[i].coordinate = NULL;
		roi[i].mean = 0;
		roi[i].var = 0;
		roi[i].vaild = true;
	}
	
	//获取ROI
	for (int r = 0; r < size.height; r++)
	{
		for (int c = 0; c < size.width; c++)
		{
			int label = Contour[r * size.width + c];//此时一个Contours变量占2位
			if (label <= 0)
				continue;
			roi[label - 1].Area++;
			roi[label - 1].center.x += c;
			roi[label - 1].center.y += r;
			//获取每个连通域的左上与右下点坐标
			if (r < roi[label - 1].region.topleft.y)
				roi[label - 1].region.topleft.y = r;
			if (r >= roi[label - 1].region.bottomright.y)
				roi[label - 1].region.bottomright.y = r;
			if (c < roi[label - 1].region.topleft.x)
				roi[label - 1].region.topleft.x = c;
			if (c >= roi[label - 1].region.bottomright.x)
				roi[label - 1].region.bottomright.x = c;
		}
	}
	//获取面积与形心,按面积分配连通域坐标空间
	for (int i = 0; i < nRoi; i++)
	{
		if (roi[i].Area <= 0 || roi[i].Area < low || roi[i].Area > high)
		{
			roi[i].vaild = false;
			continue;
		}
		roi[i].center.x /= roi[i].Area;
		roi[i].center.y /= roi[i].Area;
		if (roi[i].coordinate == NULL)
			roi[i].coordinate = (IMG_COORD*)malloc(sizeof(IMG_COORD) * roi[i].Area);
	}
	//定义坐标数组的累加数组
	int *coordAcc = (int*)malloc(sizeof(int) * nRoi);
	memset(coordAcc, 0, sizeof(int) * nRoi);
	for (int r = 0; r < size.height; r++)
	{
		for (int c = 0; c < size.width; c++)
		{
			int label = Contour[r * size.width + c];
			if (label <= 0)
				continue;
			if(roi[label - 1].coordinate)
				roi[label - 1].coordinate[coordAcc[label - 1]] = { c,r };
			coordAcc[label - 1]++;
		}
	}

	free(coordAcc);
	return 0;
}

/**********************************************/
// GetROIDistribution
//		获取连通区期望方差
// Input:
// 		Ipp8u *pSrc;			输入原图头地址
//		int step;				输入原图跨度
//		IppiSize size;			输入原图尺寸
//		int nRoi;				输入连通域个数
// Output:
// 		ROI *roi;				连通域属性
// Return:
//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-roi连通属性数组未分配空间 -1-IPP调用出错 其他-待定
// Auther: Shao Yang 12/19/2017
/**********************************************/
int GetROIDistribution(Ipp8u *pSrc, int step, IppiSize size, int nRoi, ROI *roi)
{
	if (!pSrc)
		return 1;
	if (step <= 0 || size.width <= 0 || size.height <= 0 || nRoi <= 0)
		return 2;
	if (!roi)
		return 3;
	//初始化期望方差
	for (int i = 0; i < nRoi; i++)
	{
		roi[i].mean = 0;
		roi[i].var = 0;
	}
	for (int i = 0; i < nRoi; i++)
	{
		double mean = 0, mean2 = 0;
		for (int j = 0; j < roi[i].Area; j++)
		{
			int x = roi[i].coordinate[j].x;
			int y = roi[i].coordinate[j].y;
			Ipp8u pixel = pSrc[y * step + x];
			mean += pixel;
			mean2 += pixel * pixel;
		}
		mean /= roi[i].Area;
		mean2 /= roi[i].Area;
		roi[i].mean = mean;
		roi[i].var = mean2 - mean * mean;
	}
	return 0;
}
