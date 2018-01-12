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
	//		载入图片信息,形状特征筛选初始化
	// Input:
	// 	  IMG_UBBUF  pSrc;			输入图像以及图像宽高和步长
	// Output:
	// 	  int &nRoi;				输出连通域个数
	// Return:
	//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-Roi提取数不足或超限 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT VisBaSS_shape_Init(IMG_UBBUF *pSrc, int &nRoi);
	/**********************************************/
	// VisBaSS_Shape_Select
	//		形状筛选函数
	// Input:
	// 		char* conditions;			按照指定格式输入筛选条件（例:"shapetype1,lowvalue1,highvalue;shapetype2,lowvalue2,highvalue2")
	// Output:
	// 		ROIRect *roi;				输出符合条件的ROI
	//		REGIONSHAPE *roifeature;	输出符合条件得到特征值
	//		int &nContours;				输出符合条件的连通域个数
	// Return:
	//    int  0-通过 1-未输入条件 2-未初始化筛选函数或初始化失败 3-特征数组或Roi数组未初始化 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT VisBaSS_Shape_Select(char* conditions, ROIRect *roi, REGIONSHAPE *roifeature, int &nContours, int ResetContours = 0);
	/**********************************************/
	// VisBaSS_Shape_Get
	//		形状筛选函数
	// Input:
	// 		char* shapes; 			按照指定格式输入筛选条件（例:"shapetype1,shapetype2")
	// Output:
	// 		ROIRect *roi;				输出符合条件的ROI
	//		REGIONSHAPE *roifeature;	输出符合条件得到特征值
	// Return:
	//    int  0-通过 1-未输入条件 2-未初始化筛选函数或初始化失败 3-特征数组或Roi数组未初始化 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT VisBaSS_Shape_Get(char* shapes, ROIRect *roi, REGIONSHAPE *roifeature);
	/**********************************************/
	// VisBaSS_Shape_ValidContours
	//		输出被筛选的连通域
	// Output:
	// 		CONTOURS &pCtrs;				输出符合条件的ROI
	// Return:
	//    int  0-通过 1-未输入条件 2-未初始化筛选函数或初始化失败 3-特征数组或Roi数组未初始化 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT VisBaSS_Shape_ValidContours(CONTOURS &pCtrs);
private:
	/**********************************************/
	// ShapeSelect
	//		形状符合条件判断
	// Input:
	// 		IMG_UBBUF  pSrc;			输入图像以及图像宽高和步长
	//		int nroi;					输入对应连通域标记
	//		ShapeCondition condition;	输入条件参数
	// Output:
	// 		bool &selected;				输出符合条件判断结果
	// Return:
	//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-连通域为空 4-类初始化成员指针变量为空或初始化失败 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT ShapeSelect(IMG_UBBUF pSrc,int nroi, ShapeCondition condition, bool &selected);
	/**********************************************/
	// ShapeGet
	//		形状特征获取
	// Input:
	// 		IMG_UBBUF  pSrc;			输入图像以及图像宽高和步长
	//		int nroi;					输入对应连通域标记
	// Output:
	// 		REGIONSHAPE *roifeature;	输出形状特征值
	// Return:
	//    int  0-通过 1-输入图像为空 2-输入图像尺度不合格 3-连通域为空 4-类初始化成员指针变量为空或初始化失败 -1-IPP调用出错 其他-待定
	/**********************************************/
	IMG_INT ShapeGet(IMG_UBBUF pSrc, int nroi, ShapeType shapetype);
	/**********************************************/
	// ConditionStrProcess
	//		条件集字符串处理
	// Input:
	// 		char* str;			输入条件字符串
	// Output:
	// 		int &N;				输出条件个数
	// Return:
	//    int  0-通过 1-条件为空 其他-不符合输入条件的分段字符串编号
	/**********************************************/
	IMG_INT ConditionStrProcess(char* str, int &N);
	/**********************************************/
	// Str2Condition
	//		条件字符串处理
	// Input:
	// 		char* str;			输入条件字符串
	// Output:
	// 		ShapeCondition &sc;	输出对应条件变量
	// Return:
	//    int  0-通过 1-条件为空 -2-条件名不存在 -3-条件字符串分段个数不匹配
	/**********************************************/
	IMG_INT Str2Condition(char* str, ShapeCondition &sc);
	/**********************************************/
	// Str2Shape
	//		形状特征集字符串处理
	// Input:
	// 		char* str;			输入形状字符串
	// Output:
	// 		int &N;				输出条件个数
	// Return:
	//    int  0-通过 1-条件为空 其他-不符合输入条件的分段字符串编号
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
