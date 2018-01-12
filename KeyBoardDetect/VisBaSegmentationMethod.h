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

	//��Ҫ���ʹ�� ����ʹ��ǰ��ѯ
	IMG_INT VisBaSM_Segment_RegionGrow(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_RegionGrow(IMG_UBBUF  pSrc, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF pMarker, IppiNorm norm, int flag);
	IMG_INT VisBaSM_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_UBBUF pMarker, IppiNorm norm, int flag);


	//IMG_INT VisBAIP_Segment_Wartershed(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);

	//IMG_INT VisBAIP_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);
	//FloodFillͼ��ָ
	//Input
	//pSrc  ����ͼ��
	//T   �����ӵ�ĻҶ�ֵ��
	//roi Ҫ����ĸ���Ȥ����
	//OutPut
	//pDst  ���ͼ��
	//pNum �ָ���Ŀ���
	//
	//Return
	//0   ����
	//-1  �쳣
	IMG_INT VisBaSM_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);
	IMG_INT VisBaSM_Segment_FloodFill(IMG_UBBUF  pSrc, IMG_INT  T, IMG_UBBUF  pDst, int &pNum);




	////K-means�����ָ�ͼ�񣨻��ڻҶ�ֱ��ͼ��Ϊ�����⣩
	///**********************************************/
	//// VisBaIS_Cluster_kmeans
	////		ͼ��Ԥ�ָ������������ͼ��K-means�����ָ�ͼ��
	//// Input:
	//// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	////	  IMG_INT  K,�ָ�ظ���
	////	  IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	//// Output:
	//// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	////	  SEED_TYPE = 1 K_means++��ʽ��ȡK����ʼλ��
	////    SEED_TYPE = 0 ȡֵ�����ȵȷֳ�ʼλ��
	//// Return:
	////    int  0-ͨ�� 1-ʧ�� ����-����
	///**********************************************/
	//IMG_INT VisBaSM_Cluster_kmeans(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF &pDst, IMG_INT K, IMG_BOOL SEED_TYPE = 0);
	//IMG_INT VisBaSM_Cluster_kmeans(IMG_UBBUF src, IMG_UBBUF &dst, IMG_INT K, IMG_BOOL SEED_TYPE = 0);
	///**********************************************/
	//// VisBaIS_Cluster_kmeansP
	////		ͼ��Ԥ�ָ������������Kmeans++�Ҷ�ֵ����ָ�(��������ֵ��
	//// Input:
	////		IMG_UBBUF src,		����ͼ���Լ�ͼ���ߺͲ���
	////		IMG_INT K,			�������
	////		IMG_INT nchannel,	ͼ��ͨ��
	////	    IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	//// Output:
	////		IMG_UBBUF &dst,		���ͼ���Լ�ͼ���ߺͲ���
	//// Return:
	////    int  0-ͨ�� 1-ͼ��Ϊ�� 2-�������֮��255����2�� 3-����������������Ŀ ����-����
	///**********************************************/
	//IMG_INT VisBaSM_Cluster_kmeansP(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF pDst, IMG_INT K, IMG_INT nchannel);
	//IMG_INT VisBaSM_Cluster_kmeansP(IMG_UBBUF src, IMG_UBBUF dst, IMG_INT K, IMG_INT nchannel);

	/**********************************************/
	// VisBaIS_Histogram_valley
	//		ͼ��Ԥ�ָ������������ֱ��ͼ���ȷ����ָ�ͼ��
	// Input:
	//		IMG_UBBUF src,		����ͼ���Լ�ͼ���ߺͲ���
	//		IMG_INT classes,	�������
	//	    IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	// Output:
	//		IMG_UBBUF &dst,		���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ͼ��Ϊ�� 2-���ٷ�Ϊ���� 3-δ�ֹ�ָ����� ����-����
	/**********************************************/
	IMG_INT VisBaSM_Histogram_valley(IMG_UBBUF src, IMG_WINDOW roi, IMG_UBBUF dst, IMG_INT classes);
	IMG_INT VisBaSM_Histogram_valley(IMG_UBBUF src, IMG_UBBUF dst, IMG_INT classes);

	/**********************************************/
	// VisBaIS_Threshold_dyn
	//		ͼ��Ԥ�ָ�����������ж�̬��ֵ�ָ�
	// Input:
	//		IMG_UBBUF src,			����ͼ���Լ�ͼ���ߺͲ���
	//		IMG_INT KernelSize,		ƽ���˴�С
	//		const char* LightDark,	������:"light","dark","equal","nequal"
	//		LightDark = "light"		:src - offset >= dst
	//		LightDark = "dark"		:src + offset <= dst
	//		LightDark = "equal"		:src + offset >= dst & src - offset <= dst
	//		LightDark = "nequal"	:src + offset < dst | src - offset > dst
	//		IMG_INT offset,			ƫ����
	//	    IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	// Output:
	//		IMG_UBBUF &dst,			���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ͼ��Ϊ�� 2-ƽ����Ϊ���� 3-��������Ϊ��
	/**********************************************/
	IMG_INT VisBaSM_Threshold_dyn(IMG_UBBUF pSrc, IMG_WINDOW roi, IMG_UBBUF &pDst, IMG_INT KernelSize, const char* LightDark, IMG_INT offset = 0);
	IMG_INT VisBaSM_Threshold_dyn(IMG_UBBUF src, IMG_UBBUF &dst, IMG_INT KernelSize, const char* LightDark, IMG_INT offset = 0);

	/**********************************************/
	// VisBAIP_SegmentThre
	//		ͼ��Ԥ�ָ������������ͼ��̶���ֵ�ָ�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_INT  threshold;ͼ��ָ���ֵ
	//	  IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSM_SegmentThre(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_INT  threshold, IMG_UBBUF  pDst);
	int VisBaSM_SegmentThre(IMG_UBBUF  pSrc, IMG_INT  threshold, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBAIP_SegmentOTSU
	//		ͼ��Ԥ�ָ������������ͼ������Ӧ��ֵ�ָ�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSM_SegmentOTSU(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU1(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_UBBUF  pDst);
	int VisBaSM_SegmentOTSU1(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBAIP_SegmentCntDots
	//		ͼ��Ԥ�ָ������������ͼ��ֱ��ͼ��������ֵ�ָ�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_ULWORD  fWhiteRatio��ֱ��ͼ�ָ����
	//	  IMG_WINDOW roi��Ҫ����ĸ���Ȥ����
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSM_SegmentCntDots(IMG_UBBUF  pSrc, IMG_WINDOW roi, IMG_ULWORD  fWhiteRatio, IMG_UBBUF  pDst);
	int VisBaSM_SegmentCntDots(IMG_UBBUF  pSrc, IMG_ULWORD  fWhiteRatio, IMG_UBBUF  pDst);



	//��ȡ�ض���ɫΪǰ��
	/**********************************************/
	// VisBaSM_Segment_RGB_Selectivecolor
	//Extract specific color for foreground.
	//// Input:
	//pSrc      Struct of the source image ��three channels-- - RGB��.
	//nChannel  The number of channel.
	//roi		region of interest
	//Limit_r		The maximum gray value of  r channel and The minimum gray value of  r channel.
	//Limit_g		The maximum gray value of  g channel and The minimum gray value of  g channel.
	//Limit_b       The maximum gray value of  b channel and The minimum gray value of  b channel.

	// Output:
	//pDst        Struct of the destination image ��one channel��.
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