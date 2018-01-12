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
	//		ͼ��Ԥ���������������ͼ���ֵ�˲�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MeanFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_GaussFilter
	//		ͼ��Ԥ���������������ͼ���˹�˲�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_GaussFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_BinomialFilter
	//		ͼ��Ԥ���������������ͼ�����˹�˲�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_BinomialFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MedianFilter
	//		ͼ��Ԥ���������������ͼ����ֵ�˲�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MedianFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_AnisotropyFilter
	//		ͼ��Ԥ���������������ͼ�����������ɢ����
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  Anisotrope_coefs *coef;��������ϵ��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_AnisotropyFilter(IMG_UBBUF  pSrc, IMG_UBBUF pDst, Anisotrope_coefs *coef);
	/**********************************************/
	// VisBaSB_ArrangeFilter
	//		ͼ��Ԥ���������������ͼ�������˲�
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	//	  IMG_INT ARR;����λ�ã�0<=ARR<�˵Ŀ���Ըߣ�
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_ArrangeFilter(IMG_UBBUF  pSrc, IMG_SIZE  pKernel, IMG_UBBUF  pDst, IMG_INT ARR);

	/**********************************************/
	// VisBaSB_MorphologyConnectCom_FloodFill
	//		FloodFill����ͨ��ֻ���һ����ͨ��
	// Input:
	// 	 pBinary  ����ͼ�񣨶�ֵͼ,ǰ��Ϊ255������Ϊ0��
	//	 seed  ���ӵ�
	//newVal  ������ֵ
	// Output:
	//   pRegin   ��ͨ����Ϣ
	// 	 pMarker  ��ͨ�򱻱�ǵ�ͼ��
	// Return:
	//    int  0-ͨ�� -1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyConnectCom_FloodFill(Ipp8u*  pBinary, int Width, int Height, IppiPoint seed, int newVal, IppiConnectedComp &pRegin);

	// VisBaSB_MorphologyConnectComLabel_FloodFill
	//		���������ͨ��
	// Input:
	// 	 pBinary  ����ͼ�񣨶�ֵͼ��ǰ��Ϊ255������Ϊ0��
	// Output:
	//   pRegin   ��ͨ����Ϣ
	// 	 pMarker  ��ͨ�򱻱�ǵ�ͼ��(1~254)
	//   pNum     ��ͨ�����
	// Return:
	//    int  0-ͨ�� -1-ʧ�� ����-����
	int VisBaSB_MorphologyConnectComLabel_FloodFill(IMG_UBBUF pBinary, IMG_UBBUF pMarker, IppiConnectedComp *&pRegin, int &pNum);

	/**********************************************/

	/**********************************************/
	// VisBaSB_MorphologyErode
	//		��̬ѧ��������ͼ��
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyErode(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyDilate
	//		��̬ѧ��������ͼ������
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyDilate(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyOpen
	//		��̬ѧ��������ͼ������
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyOpen(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyClose
	//		��̬ѧ��������ͼ�������
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyClose(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyGrad
	//		��̬ѧ��������ͼ����̬ѧ�ݶȼ���
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	//	  IMG_SIZE  maskSize;�˴�С��3*3,5*5��
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyGrad(IMG_UBBUF  pSrc, IMG_SIZE  maskSize, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyLabelMarker
	//		��̬ѧ��������ͼ��blob���
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	//	  int &pNum;ȫ����ͨ�����
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyLabelMarker(IMG_UBBUF  pSrc, IMG_UBBUF  pDst, int &pNum);
	/**********************************************/
	// VisBaSB_MorphologySkeletonize
	//		��̬ѧ��������ͼ��ϸ������
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologySkeletonize(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);
	/**********************************************/
	// VisBaSB_MorphologyHoleFill
	//		��̬ѧ��������ͼ��ն�������
	// Input:
	// 	  IMG_UBBUF  pSrc;����ͼ���Լ�ͼ���ߺͲ���
	// Output:
	// 	  IMG_UBBUF  pDst;���ͼ���Լ�ͼ���ߺͲ���
	// Return:
	//    int  0-ͨ�� 1-ʧ�� ����-����
	/**********************************************/
	int VisBaSB_MorphologyHoleFill(IMG_UBBUF  pSrc, IMG_UBBUF  pDst);


private:
	
};