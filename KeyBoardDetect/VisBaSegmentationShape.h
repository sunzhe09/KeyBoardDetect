#pragma once

#include "BlobAnalysis.h"

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

struct CONTOURS
{
	Ipp16u *ptr = NULL;
	IppiSize size = { 0,0 };
	int linestep = 0;
	int ncontours = 0;
};

class DLL_API VisBaSegmentationShape
{
public:
	VisBaSegmentationShape();
	~VisBaSegmentationShape();

	/**********************************************/
	// VisBaSS_shape_Init
	//		����ͼƬ��Ϣ,��״����ɸѡ��ʼ��
	// Input:
	// 	  IMG_UBBUF  pSrc;			����ͼ���Լ�ͼ���ߺͲ���
	// Output:
	// 	  int &nRoi;				�����ͨ�����
	// Return:
	//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-Roi��ȡ��������� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT VisBaSS_shape_Init(IMG_UBBUF *pSrc, int &nRoi);
	/**********************************************/
	// VisBaSS_Shape_Select
	//		��״ɸѡ����
	// Input:
	// 		char* conditions;			����ָ����ʽ����ɸѡ��������:"shapetype1,lowvalue1,highvalue;shapetype2,lowvalue2,highvalue2")
	// Output:
	// 		ROIRect *roi;				�������������ROI
	//		REGIONSHAPE *roifeature;	������������õ�����ֵ
	//		int &nContours;				���������������ͨ�����
	// Return:
	//    int  0-ͨ�� 1-δ�������� 2-δ��ʼ��ɸѡ�������ʼ��ʧ�� 3-���������Roi����δ��ʼ�� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT VisBaSS_Shape_Select(char* conditions, ROIRect *roi, REGIONSHAPE *roifeature, int &nContours, int ResetContours = 0);
	/**********************************************/
	// VisBaSS_Shape_Get
	//		��״ɸѡ����
	// Input:
	// 		char* shapes; 			����ָ����ʽ����ɸѡ��������:"shapetype1,shapetype2")
	// Output:
	// 		ROIRect *roi;				�������������ROI
	//		REGIONSHAPE *roifeature;	������������õ�����ֵ
	// Return:
	//    int  0-ͨ�� 1-δ�������� 2-δ��ʼ��ɸѡ�������ʼ��ʧ�� 3-���������Roi����δ��ʼ�� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT VisBaSS_Shape_Get(char* shapes, ROIRect *roi, REGIONSHAPE *roifeature);
	/**********************************************/
	// VisBaSS_Shape_ValidContours
	//		�����ɸѡ����ͨ��
	// Output:
	// 		CONTOURS &pCtrs;				�������������ROI
	// Return:
	//    int  0-ͨ�� 1-δ�������� 2-δ��ʼ��ɸѡ�������ʼ��ʧ�� 3-���������Roi����δ��ʼ�� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT VisBaSS_Shape_ValidContours(CONTOURS &pCtrs);
private:
	/**********************************************/
	// ShapeSelect
	//		��״���������ж�
	// Input:
	// 		IMG_UBBUF  pSrc;			����ͼ���Լ�ͼ���ߺͲ���
	//		int nroi;					�����Ӧ��ͨ����
	//		ShapeCondition condition;	������������
	// Output:
	// 		bool &selected;				������������жϽ��
	// Return:
	//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-��ͨ��Ϊ�� 4-���ʼ����Աָ�����Ϊ�ջ��ʼ��ʧ�� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT ShapeSelect(IMG_UBBUF pSrc,int nroi, ShapeCondition condition, bool &selected);
	/**********************************************/
	// ShapeGet
	//		��״������ȡ
	// Input:
	// 		IMG_UBBUF  pSrc;			����ͼ���Լ�ͼ���ߺͲ���
	//		int nroi;					�����Ӧ��ͨ����
	// Output:
	// 		REGIONSHAPE *roifeature;	�����״����ֵ
	// Return:
	//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-��ͨ��Ϊ�� 4-���ʼ����Աָ�����Ϊ�ջ��ʼ��ʧ�� -1-IPP���ó��� ����-����
	/**********************************************/
	IMG_INT ShapeGet(IMG_UBBUF pSrc, int nroi, ShapeType shapetype);
	/**********************************************/
	// ConditionStrProcess
	//		�������ַ�������
	// Input:
	// 		char* str;			���������ַ���
	// Output:
	// 		int &N;				�����������
	// Return:
	//    int  0-ͨ�� 1-����Ϊ�� ����-���������������ķֶ��ַ������
	/**********************************************/
	IMG_INT ConditionStrProcess(char* str, int &N);
	/**********************************************/
	// Str2Condition
	//		�����ַ�������
	// Input:
	// 		char* str;			���������ַ���
	// Output:
	// 		ShapeCondition &sc;	�����Ӧ��������
	// Return:
	//    int  0-ͨ�� 1-����Ϊ�� -2-������������ -3-�����ַ����ֶθ�����ƥ��
	/**********************************************/
	IMG_INT Str2Condition(char* str, ShapeCondition &sc);
	/**********************************************/
	// Str2Shape
	//		��״�������ַ�������
	// Input:
	// 		char* str;			������״�ַ���
	// Output:
	// 		int &N;				�����������
	// Return:
	//    int  0-ͨ�� 1-����Ϊ�� ����-���������������ķֶ��ַ������
	/**********************************************/
	IMG_INT Str2Shape(char* str, int &N);

private:
	//VisBaFeatureExtraction CFeatureExtration;
	//VisBaImagePreprocess CImagePreprocess;
	//VisBaImageSegmentation CImageSegmentation;
	//VisBaMorphology CMorphology;
	bool *shapemark = NULL;
	CONTOURS Contours;
	ROIRect *ROIs = NULL;
	REGIONSHAPE *RoiFeatures = NULL;
	ShapeCondition *condition = NULL;
	ShapeType *shapes = NULL;
};
