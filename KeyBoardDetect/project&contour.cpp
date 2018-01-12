#include "stdafx.h"
/**********************************************/
// Project
//		水平垂直投影
// Input:
// Ipp8u* src		原图
// int step			原图跨度
// IppiSize size	原图尺度
// int len			投影长度
// int direct		投影方向
//					1 - 水平投影
//					2 - 垂直投影
// Output:
// Ipp64f *project	投影空间
// Return:
//    
// Author: Shao Yang, 1/11/2017
/**********************************************/
int Project(Ipp8u* src, int step, IppiSize size, Ipp64f *project, int len, int direct)
{
	if (!src || !project)
		return 1;
	if (size.width <= 0 || size.height <= 0)
		return 2;
	if (step < size.width)
		return 3;
	if (direct != 1 && direct != 2)
		return 4;
	if (direct == 1 && len != size.height)
		return 5;
	if (direct == 2 && len != size.width)
		return 6;
	__try
	{
		if (direct == 1)
		{
			for (int r = 0; r < size.height; r++)
				ippiSum_8u_C1R(src + r * step, step, { size.width,1 }, &project[r]);
		}
		else if (direct == 2)
		{
			for (int c = 0; c < size.width; c++)
				ippiSum_8u_C1R(src + c, step, { 1,size.height }, &project[c]);
		}
	}
	__except (0)
	{
		return 7;
	}
	return 0;
}

/**********************************************/
// RemoveContour
//		从原图中剔除制定连通域
// Input:
// Ipp8u* src		原图
// int step8u		原图跨度
// IppiSize size	原图尺度
// Ipp16u *Contours	原图连通域图
// int step16u		连通域跨度
// int label		制定连通域标记
// Output:
// Ipp8u* src		剔除连通域的图
// Return:
//    
// Author: Shao Yang, 1/11/2017
/**********************************************/
int RemoveContour(Ipp8u *src, int step8u, IppiSize size, Ipp16u *Contours,int step16u, int label)
{
	if (!src || !Contours)
		return 1;
	if (size.width <= 0 || size.height <= 0)
		return 2;
	if (step8u < size.width || step16u <size.width * sizeof(Ipp16u))
		return 3;
	if (label <= 0)
		return 4;
	int err = 0;
	Ipp8u *mask = NULL;
	mask = (Ipp8u*)malloc(size.width * size.height * sizeof(Ipp8u));
	ippiCompareC_16u_C1R(Contours, step16u, label, mask, size.width, size, ippCmpEq);
	ippiNot_8u_C1IR(mask, size.width, size);
	ippiDivC_8u_C1IRSfs(255, mask, size.width, size, 0);
	ippiMul_8u_C1IRSfs(mask, size.width, src, step8u, size, 0);
	if (mask)
	{
		free(mask);
		mask = NULL;
	}
	return 0;
}