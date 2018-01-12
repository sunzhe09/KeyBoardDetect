#pragma once
#ifndef BABASE_H
#define BABASE_H


#define NFREATURES 9

struct POINTF
{
	double x;
	double y;
};
struct AREACENTER
{
	double Area;
	IMG_RCOORD Center;
};

struct SMALLCIRCLE
{
	double radius;
	IMG_RCOORD Center;
};

struct ELLIPTICAXIS
{
	double Ra;
	double Rb;
	double Phi;
};

struct ECCENTRICITY
{
	double Anisometry;
	double Bulkiness;
	double StructureFactor;
};

struct ROUNDNESS
{
	double DistMean;
	double DistDeviation;
	double Sides;
	double Roundness;
};

struct ROIRect
{
	IMG_COORD topleft;
	IMG_COORD bottomright;
};

typedef struct shape
{
	AREACENTER AreaCenter;	//面积形心
	double Circularity;		//圆度
	SMALLCIRCLE SmallestCircle;	//外接圆心与半径
	double Compactness;		//紧密度(反映ROI的密实程度)
	double Contlength;		//轮廓长度
	double Convexity;		//凸度
	double Rectangularity;	//矩性
	ELLIPTICAXIS Ellipticaxis;	//类椭圆属性
	ECCENTRICITY Eccentricity;	//偏心率(反应ROI“扁”/饱和的程度）
	ROUNDNESS Roundness;		//形状因子
}REGIONSHAPE;

typedef enum
{
	shape_max = 18,

	shape_area = 0,				//"area"
	shape_circularity = 1,		//"circularity"
	shape_compactness = 2,		//"compactness"
	shape_contlength = 3,		//"contlength"
	shape_convexity = 4,		//"convexity"
	shape_radius = 5,			//"radius"
	shape_phi = 6,				//"slant"
	shape_eccentricity = 7,		//"eccentricity"
	shape_roundness = 8,		//"roundness"
	shape_rectangularity = 9,	//"rectangularity"
	shape_areacenter = 10,		//"areacenter"
	shape_ra = 11,				//"longaxis"
	shape_rb = 12,				//"shortaxis"
	shape_distmean = 13,		//"meandistedge"
	shape_distdeviation = 14,	//"vardistedge"
	shape_sides = 15,			//"sides"
	shape_anisometry = 16,		//"anisometry"
	shape_bulkiness = 17		//"shape_bulkiness"
}ShapeType;

typedef enum
{
	compare_greater = 0,
	compare_less = 1,
	compare_equal = 2,
	compare_greatereq = 4,
	compare_lesseq = 5,
	compare_nequal = 6
}CompareType;

//当lowvalue == heightvalue时,调用cmp
struct ShapeCondition
{
	ShapeType shapetype;
	IMG_LREAL lowvalue;
	IMG_LREAL highvalue;
};

struct Anisotrope_coefs//各向异性
{
	int k = 15;//迭代次数
	float lambda = 0.15;//控制平滑
	int N = 20;//导热系数, 控制平滑
			   //float T[4];
			   //float cs[4];
};

struct LimitHSV
{
	float max = 0;
	float min = 0;
};
#endif // !BABASE_H
