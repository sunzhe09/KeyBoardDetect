#pragma once

#include "BlobAnalysis.h"

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
class DLL_API VisBaSegmentationMethod
{
public:
	VisBaSegmentationMethod();
	~VisBaSegmentationMethod();

	IMG_INT VisBaSM_Segmentation_Cluster(IMG_UBBUF pSrc, IMG_WINDOW roi/*std::vector<IMG_COORD> &roi*/,/*IMG_INT roiStatus,*/ IMG_UBBUF &pDst, IMG_INT K, IMG_INT NChannel);
	IMG_INT VisBaSM_Segmentation_Cluster(IMG_UBBUF pSrc, IMG_UBBUF &pDst, IMG_INT K, IMG_INT NChannel);
	//typedef struct {
	//	IMG_COORD	coWindowOff;
	//	IMG_SIZE	szWindowSize;
	//} IMG_WINDOW;

	//需要配合使用 建议使用前查询
	IMG_INT VisBaSM_Segment_RegionGrow(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_RegionGrow(IMG_UBBUF  pSrc, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_UBBUF pMarker, IppiNorm norm, int flag);


	//IMG_INT VisBAIP_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);

	//IMG_INT VisBAIP_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);
	//FloodFill图像分割：
	//Input
	//pSrc  输入图像
	//T   与种子点的灰度值差
	//roi 要处理的感兴趣区域
	//OutPut
	//pDst  输出图像
	//pNum 分割出的块数
	//
	//Return
	//0   正常
	//-1  异常
	IMG_INT VisBaSM_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);
	IMG_INT VisBaSM_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);




	////K-means方法分割图像（基于灰度直方图作为样本库）
	///**********************************************/
	//// VisBaIS_Cluster_kmeans
	////		图像预分割基本操作进行图像K-means方法分割图像
	//// Input:
	//// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	////	  IMG_INT  K,分割簇个数
	////	  IMG_WINDOW roi，要处理的感兴趣区域
	//// Output:
	//// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	////	  SEED_TYPE = 1 K_means++方式获取K个初始位置
	////    SEED_TYPE = 0 取值区间跨度等分初始位置
	//// Return:
	////    int  0-通过 1-失败 其他-待定
	///**********************************************/
	//IMG_INT VisBaSM_Cluster_kmeans(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF &pDst, IMG_INT K, IMG_BOOL SEED_TYPE = 0);
	//IMG_INT VisBaSM_Cluster_kmeans(IMG_UBBUF src, IMG_UBBUF &dst, IMG_INT K, IMG_BOOL SEED_TYPE = 0);
	///**********************************************/
	//// VisBaIS_Cluster_kmeansP
	////		图像预分割基本操作进行Kmeans++灰度值聚类分割(基于像素值）
	//// Input:
	////		IMG_UBBUF src,		输入图像以及图像宽高和步长
	////		IMG_INT K,			聚类个数
	////		IMG_INT nchannel,	图像通道
	////	    IMG_WINDOW roi，要处理的感兴趣区域
	//// Output:
	////		IMG_UBBUF &dst,		输出图像以及图像宽高和步长
	//// Return:
	////    int  0-通过 1-图像为空 2-聚类个数之多255至少2个 3-聚类个数超过类别数目 其他-待定
	///**********************************************/
	//IMG_INT VisBaSM_Cluster_kmeansP(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF pDst, IMG_INT K, IMG_INT nchannel);
	//IMG_INT VisBaSM_Cluster_kmeansP(IMG_UBBUF src, IMG_UBBUF dst, IMG_INT K, IMG_INT nchannel);

	/**********************************************/
	// VisBaIS_Histogram_valley
	//		图像预分割基本操作进行直方图波谷方法分割图像
	// Input:
	//		IMG_UBBUF src,		输入图像以及图像宽高和步长
	//		IMG_INT classes,	分类个数
	//	    IMG_WINDOW roi，要处理的感兴趣区域
	// Output:
	//		IMG_UBBUF &dst,		输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-图像为空 2-至少分为两类 3-未分够指定类别 其他-待定
	/**********************************************/
	IMG_INT VisBaSM_Histogram_valley(IMG_UBBUF src, IMG_WINDOW roi, IMG_UBBUF dst, IMG_INT classes);
	IMG_INT VisBaSM_Histogram_valley(IMG_UBBUF src, IMG_UBBUF dst, IMG_INT classes);

	/**********************************************/
	// VisBaIS_Threshold_dyn
	//		图像预分割基本操作进行动态阈值分割
	// Input:
	//		IMG_UBBUF src,			输入图像以及图像宽高和步长
	//		IMG_INT KernelSize,		平滑核大小
	//		const char* LightDark,	检测类别:"light","dark","equal","nequal"
	//		LightDark = "light"		:src - offset >= dst
	//		LightDark = "dark"		:src + offset <= dst
	//		LightDark = "equal"		:src + offset >= dst & src - offset <= dst
	//		LightDark = "nequal"	:src + offset < dst | src - offset > dst
	//		IMG_INT offset,			偏移量
	//	    IMG_WINDOW roi，要处理的感兴趣区域
	// Output:
	//		IMG_UBBUF &dst,			输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-图像为空 2-平滑核为基数 3-检测类别不能为空
	/**********************************************/
	IMG_INT VisBaSM_Threshold_dyn(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF &pDst, IMG_INT KernelSize, const char* LightDark, IMG_INT offset = 0);
	IMG_INT VisBaSM_Threshold_dyn(IMG_UBBUF src, IMG_UBBUF &dst, IMG_INT KernelSize, const char* LightDark, IMG_INT offset = 0);

	/**********************************************/
	// VisBAIP_SegmentThre
	//		图像预分割基本操作进行图像固定阈值分割
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_INT  threshold;图像分割阈值
	//	  IMG_WINDOW roi，要处理的感兴趣区域
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSM_SegmentThre(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_INT  threshold, IMG_UBBUF  pDst);
	int VisBaSM_SegmentThre(IMG_UBBUF  pSrc, IMG_INT  threshold, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBAIP_SegmentOTSU
	//		图像预分割基本操作进行图像自适应阈值分割
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_WINDOW roi，要处理的感兴趣区域
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSM_SegmentOTSU(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU1(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU1(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBAIP_SegmentCntDots
	//		图像预分割基本操作进行图像直方图比例法阈值分割
	// Input:
	// 	  IMG_UBBUF  pSrc;输入图像以及图像宽高和步长
	//	  IMG_ULWORD  fWhiteRatio，直方图分割比例
	//	  IMG_WINDOW roi，要处理的感兴趣区域
	// Output:
	// 	  IMG_UBBUF  pDst;输出图像以及图像宽高和步长
	// Return:
	//    int  0-通过 1-失败 其他-待定
	/**********************************************/
	int VisBaSM_SegmentCntDots(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_ULWORD  fWhiteRatio, IMG_UBBUF  pDst);
	int VisBaSM_SegmentCntDots(IMG_UBBUF  pSrc, IMG_ULWORD  fWhiteRatio, IMG_UBBUF  pDst);



	//提取特定颜色为前景
	/**********************************************/
	// VisBaSM_Segment_RGB_Selectivecolor
	//Extract specific color for foreground.
	//// Input:
	//pSrc      Struct of the source image （three channels-- - RGB）.
	//nChannel  The number of channel.
	//roi		region of interest
	//Limit_r		The maximum gray value of  r channel and The minimum gray value of  r channel.
	//Limit_g		The maximum gray value of  g channel and The minimum gray value of  g channel.
	//Limit_b       The maximum gray value of  b channel and The minimum gray value of  b channel.

	// Output:
	//pDst        Struct of the destination image （one channel）.
	//Return Values
	//0   Indicates no error.
	//1   Error.
	IMG_INT VisBaSM_Segment_RGB_Selectivecolor(IMG_UBBUF  pSrc, IMG_WINDOW roi, int nChannel, IMG_UBBUF pDst,
		LimitHSV rMaxrMin, LimitHSV gMaxgMin, LimitHSV bMaxbMin);
	IMG_INT VisBaSM_Segment_RGB_Selectivecolor(IMG_UBBUF  pSrc, int nChannel, IMG_UBBUF pDst,
		LimitHSV rMaxrMin, LimitHSV gMaxgMin, LimitHSV bMaxbMin);

	/**********************************************/
	// VisBAIP_SegmentHSV
	//Extract specific color for foreground.
	//// Input:
	//pSrc      Struct of the source image .
	//roi		region of interest
	//Limit_s		The maximum gray value of  s channel and The minimum gray value of  s channel.
	//Limit_v		The maximum gray value of  v channel and The minimum gray value of  v channel.
	//Limit_h       The maximum gray value of  H channel and The minimum gray value of  H channel.
	//bMax     
	// Output:
	//pDst        Struct of the destination image.
	//Return Values
	//0   Indicates no error.
	//1   Error.
	int VisBaSM_SegmentHSV(IMG_UBBUF  pSrc, IMG_WINDOW roi, LimitHSV Limit_h, LimitHSV Limit_s, LimitHSV Limit_v, IMG_UBBUF  pDst);
	int VisBaSM_SegmentHSV(IMG_UBBUF  pSrc, LimitHSV Limit_h, LimitHSV Limit_s, LimitHSV Limit_v, IMG_UBBUF  pDst);

private:
	//VisBaFeatureExtraction CFeatureExtration;
	//VisBaImagePreprocess CImagePreprocess;
	//VisBaImageSegmentation CImageSegmentation;
	//VisBaMorphology CMorphology;
};