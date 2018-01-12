#pragma once

#include "BlobAnalysis.h"


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

class DLL_API VisBaSegmentationBase
{
public:
	VisBaSegmentationBase();
	~VisBaSegmentationBase();
	//virtual~VisBaSegmentationBase();
	//vector<IMG_COORD> x;
	IMG_INT VisBaSB_getROI(IMG_UBBUF src,std::vector<IMG_COORD> roi);

	/**********************************************/
	// VisBaSB_MeanFilter
	//		图像预处理基本操作进行图像均值滤波
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MeanFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_GaussFilter
	//		图像预处理基本操作进行图像高斯滤波
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_GaussFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_BinomialFilter
	//		图像预处理基本操作进行图像类高斯滤波
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_BinomialFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MedianFilter
	//		图像预处理基本操作进行图像中值滤波
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MedianFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_AnisotropyFilter
	//		图像预处理基本操作进行图像各向异性扩散降噪
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  Anisotrope_coefs *coef;各向异性系数
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_AnisotropyFilter(IMG_UBBUF  pSrc, IMG_UBBUF pDst, Anisotrope_coefs *coef);
	/**********************************************/
	// VisBaSB_ArrangeFilter
	//		图像预处理基本操作进行图像排列滤波
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	//	  IMG_INT ARR;排列位置（0<=ARR<核的宽乘以高）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_ArrangeFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst, IMG_INT ARR);

	/**********************************************/
	// VisBaSB_MorphologyConnectCom_FloodFill
	//		FloodFill找连通域，只标记一个连通域
	// Input:
	// 	 pBinary  输入图像（二值图,前景为255，背景为0）
	//	 seed  种子点
	//newVal  赋的新值
	// Output:
	//   pRegin   连通域信息
	// 	 pMarker  连通域被标记的图像
	// Return:
	//    int  0-通过 -1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyConnectCom_FloodFill(Ipp8u*  pBinary, int Width, int Height, IppiPoint seed, int newVal, IppiConnectedComp &pRegin);

	// VisBaSB_MorphologyConnectComLabel_FloodFill
	//		标记所有连通域
	// Input:
	// 	 pBinary  输入图像（二值图，前景为255，背景为0）
	// Output:
	//   pRegin   连通域信息
	// 	 pMarker  连通域被标记的图像(1~254)
	//   pNum     连通域个数
	// Return:
	//    int  0-通过 -1-失败 其他-待定
	int VisBaSB_MorphologyConnectComLabel_FloodFill(IMG_UBBUF pBinary, IMG_UBBUF pMarker, IppiConnectedComp *&pRegin, int &pNum);

	/**********************************************/

	/**********************************************/
	// VisBaSB_MorphologyErode
	//		形态学操作进行图像
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyErode(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyDilate
	//		形态学操作进行图像膨胀
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyDilate(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyOpen
	//		形态学操作进行图像开运算
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyOpen(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyClose
	//		形态学操作进行图像闭运算
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyClose(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyGrad
	//		形态学操作进行图像形态学梯度计算
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_SIZE  maskSize;核大小（3*3,5*5）
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyGrad(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyLabelMarker
	//		形态学操作进行图像blob标记
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	//	  int &pNum;全部连通域个数
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyLabelMarker(IMG_UBBUF  pSrc, IMG_UBBUF  pDst, int &pNum);
	/**********************************************/
	// VisBaSB_MorphologySkeletonize
	//		形态学操作进行图像细化操作
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologySkeletonize(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyHoleFill
	//		形态学操作进行图像空洞填充操作
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSB_MorphologyHoleFill(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);


private:
	
};