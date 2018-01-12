// KeyBoardDetect.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>


#ifdef _DEBUG //这个要加上，否则不会输出定义到那个文件中（及不包含存在内存泄露的该cpp文件的相关信息）  
#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)  
#endif

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

using namespace std;
using namespace cv;

vector<Mat> read_images_in_folder(cv::String pattern);
void imgShow(unsigned char* src, int srcStep, int width, int height);
int LigitEnhance(Ipp8u * src, Ipp8u * dst, int srcStep, IppiSize roiSize, Ipp8u mulFactorValue, Ipp8u subFactorValue);
int imgMean(Ipp8u*src, IppiSize ROI, int src_step, unsigned char *dst);
int RegionsSegement(unsigned char* src,unsigned char *pSrcMarker, int srcMarkerStep, IppiSize roiSize, vector<ROI>&muraRegions);
int ContourInit_8u16u(Ipp8u *pSrc, int srcStep, Ipp16u *pDst, int dstStep, IppiSize size, int &nRoi);
int AllocationContours(Ipp16u *Contour, IppiSize size, int nRoi, ROI *roi, int AreaLow, int AreaHigh);
int ContourInit_8u16u(Ipp8u *pSrc, int srcStep, Ipp16u *pDst, int dstStep, IppiSize size, int &nRoi);
double WeiborMuraCalulate(double beforeGrayMean, double beforeArea, double backgroungGrayMean);
int GetROIDistribution(Ipp8u *pSrc, int step, IppiSize size, int nRoi, ROI *roi);


int main()
{
	//const string filename = "W:/算法部/孙哲/keyboard/缺陷样本/*.jpg";
	Directory dir;
	string path1 = "W:/算法部/孙哲/keyboard/缺陷样本/";
	//string path1 = "C:/Users/bm00133/Desktop/";
	string dst_path = "W:/算法部/孙哲/keyboard/result/";
	string  exten1 = "*.jpg";
	vector<string> filenames = dir.GetListFiles(path1, exten1, false);
	
	for (vector<string> ::iterator it = filenames.begin(); it != filenames.end(); it++)
	{

		//检测内存泄漏
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
		clock_t start, finish;
		double totaltime;
		Mat temp = imread(path1+*it,0);//读取的时候灰度化了


		int src_Step = 0;
		IppiSize roi = { temp.cols,temp.rows };
		Ipp8u *src = ippiMalloc_8u_C1(temp.cols,temp.rows,&src_Step);
		ippiCopy_8u_C1R((Ipp8u*)temp.data, temp.step[0], src, src_Step, roi);
	
		Ipp8u *dst_t = ippiMalloc_8u_C1(temp.cols, temp.rows, &src_Step);
		Ipp8u *dst = ippiMalloc_8u_C1(temp.cols, temp.rows, &src_Step);
	
		Ipp8u mulFactorValue =18;
		Ipp8u subFactorValue = 80;

		start = clock();
		try
		{
			LigitEnhance(src, dst_t, src_Step, roi, mulFactorValue, subFactorValue);
		}

		catch(int a)
		{
	 
				 if (a == 1)
				 {
					 cerr << "error函数：LigitEnhance（），图像为空！\n";
					 exit(1);
				 }
				 else if (a==2)
				 {
					 cerr << "error函数：LigitEnhance（），图像步长不合格！\n";
					 exit(1);
				 }
				 else if (a == 3)
				 {
					 cerr << "error函数：LigitEnhance（），图像尺寸不合格！\n";
					 exit(1);
				 }
				 else if (a == 4)
				 {
					 cerr << "error函数：LigitEnhance（），增强参数不合格！\n";
					 exit(1);
				 }
				 else if (a == -1)
				 {
					 cerr << " error函数：LigitEnhance（），ipp调用失败！\n";
					 exit(1);
				 }


		}
		
			//if (flag_l != 0) return flag_l;
		
		try 
		{ 
			imgMean(dst_t, roi, src_Step, dst); 
		}
		catch (int a)
		{
		
				if (a == 1)
				{
					cerr << " error函数：imgMean（），输入图像步长不合格！\n";
					exit(1);
				}
				else if (a == 2)
				{
					cerr << " error函数：imgMean（），图像尺寸不合格！\n";
					exit(1);
				}
					
				else if (a == -1)
				{
					cerr << " error函数：imgMean（），输入图像为空！\n";
					exit(1);
				}

		}
	

		//imgShow(dst, src_Step, roi.width, roi.height);

		vector<ROI>muraRegions;
		try
		{
			RegionsSegement(src, dst, src_Step, roi, muraRegions);
		}
		
		catch (int a)
		{
			//1-输入图像为空 2-输入图像步长不合格 3-图像尺寸不合格  -1-IPP调用出错 其他-待定
			if (a==1)
			{
				cerr << "error函数：RegionsSegement（），输入图像为空" << endl;
				exit(1);
			}
			if (a == 2)
			{
				cerr << "error函数：RegionsSegement（），输入图像步长不合格" << endl;
				exit(1);
			}
			if (a == 3)
			{
				cerr << "error函数：RegionsSegement（），图像尺寸不合格" << endl;
				exit(1);
			}
			if (a == -1)
			{
				cerr << "error函数：RegionsSegement（），IPP调用出错" << endl;
				exit(1);
			}
			
		}
		

		finish = clock();
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "此程序的运行时间为:" << totaltime << "秒！\n" << endl;

		int k=0;
		for (vector<ROI>::iterator it1 = muraRegions.begin(); it1 != muraRegions.end(); it1++,k++)
		{
			
			char showMsg[50];
			cv::Point pt1;
			cv::Point pt2;
			pt2.x = (*it1).region.bottomright.x;
			pt2.y = (*it1).region.bottomright.y;
			pt1. x = (*it1).region.topleft.x;
			pt1. y = (*it1).region.topleft.y;
			rectangle(temp, pt1, pt2, Scalar(255), 1, 4, 0);//用点画矩形窗  
			
			sprintf(showMsg, "(MEAN: %f,VAR: %f)", (*it1).mean, (*it1).var);
			
			putText(temp, showMsg, Point(50, 50 + k * 50), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255), 1, 2); // 显示字符

		}
			//imwrite(dst_path+(*it),temp);
			ippFree(src);
			ippFree(dst);
			ippFree(dst_t);
	}


    return 0;
}


vector<Mat> read_images_in_folder(cv::String pattern)
{
	vector<cv::String> fn;
	glob(pattern, fn, false);
	vector<Mat> images;
	size_t count = fn.size(); //number of jpg files in images folder
	for (size_t i = 0; i < count; i++)
	{
		images.push_back(imread(fn[i]));
		/*imshow("img", imread(fn[i]));
		waitKey(1000);*/
	}
	return images;
}

//图像取反
void  imgInvert(Ipp8u*src,IppiSize ROI,int src_step)
{
	for (int i = 0; i < ROI.height; i++)
	{
		for (int j = 0; j <ROI.width; j++)
		{
			src[i*src_step + j] = 255 - src[i*src_step + j];
		}
	}

}

//opencv显示图像
void imgShow(unsigned char* src, int srcStep, int width, int height)
{
	IplImage *show = cvCreateImageHeader(cvSize(width, height), 8u, 0);
	cvSetData(show, (uchar*)src, srcStep);
	cvReleaseImageHeader(&show);
}


/**********************************************/
// imgMean
//		最小值滤波/
// Input:
// 		Ipp8u*src;				未处理的原图像		
//		int src_step;			图像的步长
//		IppiSize ROI			图像的ROI范围	
// Output:
//		unsigned char *dst;		滤波后的图像
// Return:
//    int  0-通过 -1-输入图像为空 1-输入图像步长不合格 2-图像尺寸不合格  
// Auther: Sun Zhe 12/20/2017
/**********************************************/
int imgMean(Ipp8u*src, IppiSize ROI, int src_step,unsigned char *dst)
{
	if (src == NULL)
		throw -1;
	if (ROI.height <= 0 || ROI.width <= 0)
		throw 2;
	if (src_step <= 0)
		throw 1;
	unsigned char p[9], s;

	for (int i = 1; i < ROI.height-1; i++)
	{
		for (int j = 1; j < ROI.width-1; j++)
		{
			
			//把一个像素周围的8个像素值分别赋值给p[0]到p[8]
			/*p[0] = src[j + ( i)*src_step];
			p[1] = src[j + (i - 1)*src_step];
			p[2] = src[j +1 + (i - 1)*src_step];
			p[3] = src[j -1+ (i-1)*src_step];
			p[4] = src[j -1+ i*src_step];
			p[5] = src[j + 1 + i*src_step];
			p[6] = src[j - 1 + (i + 1)*src_step];
			p[7] = src[j + (i + 1)*src_step];
			p[8] = src[j +1 + (i + 1)*src_step];
			s = p[4];
			for(int k=0;k<9;k++)
			{
				s = std::min(p[k],s);
			}

			dst[i*src_step + j] = s;*/
			
			dst[i*src_step + j] = (src[i*src_step + j] + src[(i - 1)*src_step + j] + src[(i + 1)*src_step + j] + src[i*src_step + j - 1] + src[i*src_step + j + 1] + src[(i - 1)*src_step + j - 1] + src[(i - 1)*src_step + j + 1] + src[(i + 1)*src_step + j - 1] + src[(i + 1)*src_step + j + 1])/9;
		}
	}

	//imgShow(dst, src_step, ROI.width, ROI.height);
	return 0;
}

/**********************************************/
// LigitEnhance
//		图像增强
// Input:
// 		Ipp8u*src;				未处理的原图像		
//		int src_step;			图像的步长
//		IppiSize roiSize		图像的ROI范围
//		Ipp8u mulFactorValue    图像乘法因子（增强对比度）
//		Ipp8u subFactorValue	图像减法因子（背景）
// Output:
//		Ipp8u *dst;				增强后的图像
// Return:
//		int  0-通过 1-输入图像为空 2-输入图像步长不合格 3-图像尺寸不合格 4-增强参数不合格  -1-ipp调用失败
// Auther: Sun Zhe 12/19/2017
/**********************************************/

int LigitEnhance(Ipp8u * src, Ipp8u * dst, int srcStep, IppiSize roiSize, Ipp8u mulFactorValue, Ipp8u subFactorValue)
{
	IppStatus status = ippStsNoErr;
	//Ipp8u mulFacorValue = 12;
	//subFactorValue=65


	if (!src || !dst)
		throw 1;
	if (srcStep <= 0)
		throw 2;
	if (roiSize.width <= 0 || roiSize.height <= 0)
		throw 3;
	if (mulFactorValue <= 0 || subFactorValue <= 0)
		throw 4;

	status=ippiMulC_8u_C1RSfs(src, srcStep, mulFactorValue, dst, srcStep, roiSize, 0);
	if (status != ippStsNoErr)
		throw status;

	for (int i = 0; i < roiSize.height; i++)
	{
		for (int j = 0; j < roiSize.width; j++)
		{
			dst[i*srcStep + j] = (dst[i*srcStep + j] - subFactorValue)/(255- subFactorValue)*255;
		}
	}
	//imgShow(dst, srcStep, roiSize.width, roiSize.height);
	return 0;
}



/**********************************************/
// RegionsSegement
//		图像分割连通域计算
// Input:
// 		unsigned char* src;			未处理的原图像
//		unsigned char *pSrcMarker;	增强后的图像
//		int srcMarkerStep;			图像的步长
//		IppiSize roiSize;			图像的ROI范围	
// Output:
//		vector<ROI> &muraRegions	存放mura缺陷的连通域集合
// Return:
//		int  0-通过 1-输入图像为空 2-输入图像步长不合格 3-图像尺寸不合格  -1-IPP调用出错 其他-待定
// Auther: Sun Zhe 12/19/2017
/**********************************************/

int RegionsSegement(unsigned char* src, unsigned char *pSrcMarker, int srcMarkerStep, IppiSize roiSize, vector<ROI> &muraRegions)
{


	if (src == NULL || pSrcMarker == NULL)
		throw 1;
	if (srcMarkerStep <= 0)
		throw 2;
	if (roiSize.height <= 0 || roiSize.width <= 0)
		throw 3;

	IppStatus status = ippStsNoErr;

	int minLabel = 1;
	int maxLabel = 50000;
	int markersNum = 0;
	Ipp8u* pBuffer = NULL;
	int bufferSize = 0;
	float lowThreshold_weibor = 10.0;
	float highThreshold_weibor = 120.0;


	Ipp8u threshold = 40;
	int AreaLow = 27, AreaHigh=1000;
	IppCmpOp ippcmpop = ippCmpGreaterEq;

	status=	ippiCompareC_8u_C1R(pSrcMarker, srcMarkerStep, threshold, pSrcMarker, srcMarkerStep, roiSize, ippcmpop);
	if (status != ippStsNoErr)
		throw status;


	/*显示中间结果*/
	IplImage *show = cvCreateImageHeader(cvSize(roiSize.width, roiSize.height), 8u, 1);
	cvSetData(show, (unsigned char*)pSrcMarker, srcMarkerStep);

	Ipp16u *Contours = NULL;
	Contours = (Ipp16u*)malloc(sizeof(Ipp16u) * roiSize.width * roiSize.height);//mark图索引
	int nRoi = 0;
	try
	{ 
		ContourInit_8u16u(pSrcMarker, srcMarkerStep, Contours, roiSize.width * sizeof(Ipp16u), roiSize, nRoi); 
	}
	catch(int a)
	{
		//1 - 输入图像为空 2 - 输入图像尺度不合格 3 - Roi提取数不足或超限 - 1 - IPP调用出错 其他 - 待定
		if (a == 1)
		{
			cerr << "error函数;ContourInit_8u16u(),输入图像为空！" << endl;
			exit(1);
		}
		else if (a == 2)
		{
			cerr << "error函数;ContourInit_8u16u(),输入图像尺度不合格！" << endl;
			exit(1);
		}
		else if (a==3)
		{
			cerr << "error函数;ContourInit_8u16u(),Roi提取数不足或超限！" << endl;
			exit(1);
		}
		else if (a == -1)
		{
			cerr << "error函数;ContourInit_8u16u(),IPP调用出错！" << endl;
			exit(1);
		}

	}
	
	ROI *Rois = (ROI*)malloc(sizeof(ROI) * nRoi);

	try
	{ 
		AllocationContours(Contours, roiSize, nRoi, Rois, AreaLow, AreaHigh); 
	}
	catch (int a)
	{
		//1-输入图像为空 2-输入图像尺度不合格 3-roi连通属性数组未分配空间 -1-IPP调用出错 其他-待定
		if (a == 1)
		{
			cerr << "error函数;AllocationContours(),输入图像为空！" << endl;
			exit(1);
		}
		else if (a==2)
		{
			cerr << "error函数;AllocationContours(),输入图像尺度不合格！" << endl;
			exit(1);
		}
		else if (a == 3)
		{
			cerr << "error函数;AllocationContours(),roi连通属性数组未分配空间！" << endl;
			exit(1);
		}
		else if (a == -1)
		{
			cerr << "error函数;AllocationContours(),IPP调用出错！" << endl;
			exit(1);
		}
	}
	
	try

	{
		GetROIDistribution(src, srcMarkerStep, roiSize, nRoi, Rois);
	}
	catch (int a)
	{
		//1-输入图像为空 2-输入图像尺度不合格 3-roi连通属性数组未分配空间 -1-IPP调用出错 其他-待定
		if (a == 1)
		{
			cerr << "error函数;GetROIDistribution(),输入图像为空！" << endl;
			exit(1);
		}
		else if (a==2)
		{
			cerr << "error函数;GetROIDistribution(),输入图像尺度不合格" << endl;
			exit(1);
		}
		else if (a==3)
		{
			cerr << "error函数;GetROIDistribution(),roi连通属性数组未分配空间" << endl;
			exit(1);
		}

		else if (a==-1)
		{
			cerr << "error函数;GetROIDistribution(),IPP调用出错！" << endl;
			exit(1);
		}

	}

	double grayMean_before=0.0, grayMean_back=0.0;

	int rel = 0;//扩大背景的偏置量
	double k = 0.0;
	
	vector<double> top,bottom,left,right;
	top.push_back(0);
	bottom.push_back(roiSize.height);
	left.push_back(0);
	right.push_back(roiSize.width);

	for (int i = 0; i < nRoi; i++)
	{
		if (Rois[i].vaild == false)
			continue;
		for (int k = 0; k < Rois[i].Area; k++)
		{
						
			grayMean_before =Rois[i].mean;
					 
		}

		//面积的开方获得偏置量
		rel = sqrt(Rois[i].Area);
		int numPixs = 0;
		
		for (int m = Rois[i].region.topleft.y - rel; m < Rois[i].region.bottomright.y + rel; m++)
		{
			for (int n = Rois[i].region.topleft.x - rel; n < Rois[i].region.bottomright.x + rel; n++)
			{
				bool flag = true;//true代表没有越界
				int	m_=0, n_=0;

				if (m < 0|| m >= roiSize.height)
				{
					m_ = (2 * Rois[i].center.y - m);
					flag = false;
				}
				if (n < 0||n>=roiSize.width)
				{
					n_ = 2 * Rois[i].center.x - n;
					flag = false;
				}
		
				if(flag==true)
					grayMean_back += src[n + m*srcMarkerStep];
				else
				{
					grayMean_back += src[n_ + m_*srcMarkerStep];
				}
					numPixs++;
							
			}
		}
		
		//grayMean_back /= (Rois[i].region.bottomright.y - Rois[i].region.topleft.y + 2 * rel)*(Rois[i].region.bottomright.x - Rois[i].region.topleft.x + 2 * rel);
		grayMean_back /= numPixs;

		try
		{
			k = WeiborMuraCalulate(grayMean_before, Rois[i].Area, grayMean_back);
		}
		catch (int a)
		{
			if (a == -1)
			{
				cerr << "error函数;WeiborMuraCalulate(),输入参数不合格" << endl;
				exit(1);
			}

		}
		
		cout << k << endl;
		//判定是否为真正的mura
		double height_roi = Rois[i].region.bottomright.y - Rois[i].region.topleft.y;
		double width_roi = Rois[i].region.bottomright.x - Rois[i].region.topleft.x;
		double rate = height_roi / width_roi;
		
		if (rate < 1 )
			rate = 1 / rate;
		double top_b = 0.0,  bottom_t = 0.0, left_r = 0.0, right_l = 0.0;

		//判断上下的正常漏光范围
		if ((Rois[i].region.bottomright.x - Rois[i].region.topleft.x) > 80)
		{
			
			if((roiSize.height - Rois[i].center.y)<25)
			{ 
			 //底部正常漏光
			 top_b = Rois[i].region.topleft.y;
			 bottom.push_back(top_b);

			}

			if (Rois[i].center.y < 25)
			{
			//顶部正常漏光		
			bottom_t = Rois[i].region.bottomright.y;
			top.push_back(bottom_t);
			}
			
		
		}

		//判断左右的正常漏光范围
		if ((Rois[i].region.bottomright.y - Rois[i].region.topleft.y) > 80 )
		{
			
			if ( (roiSize.width - Rois[i].center.x) < 30)
			{
				//右部正常漏光
				left_r = Rois[i].region.topleft.x;
				right.push_back(left_r);
				
			}

			if (Rois[i].center.x < 30)
			{
				//左部正常漏光			
				right_l = Rois[i].region.bottomright.x;
				left.push_back(right_l);
			}

		}


		if ( lowThreshold_weibor <k&&k < highThreshold_weibor&&Rois[i].var < 8000)//rate miss
		{
			muraRegions.push_back(Rois[i]);
		}
			
	}
		
	//获得边界值
	
	vector<double>::iterator topmax = std::max_element(std::begin(top), std::end(top));
	vector<double>::iterator bottommin = std::min_element(std::begin(bottom), std::end(bottom));
	vector<double>::iterator leftmax = std::max_element(std::begin(left), std::end(left));
	vector<double>::iterator rightmin = std::min_element(std::begin(right), std::end(right));

	cvLine(show,cvPoint(*leftmax,0),cvPoint(*leftmax,roiSize.height-1),cvScalar(255));
	cvLine(show, cvPoint(*rightmin, 0), cvPoint(*rightmin, roiSize.height - 1), cvScalar(255));
	cvLine(show, cvPoint(0,*topmax), cvPoint(roiSize.width-1,*topmax), cvScalar(255));
	cvLine(show, cvPoint( 0,*bottommin), cvPoint(roiSize.width-1, *bottommin), cvScalar(255));

	for (vector<ROI>::iterator it=muraRegions.begin();it!=muraRegions.end();)
	{
		if ((*it).center.x < *leftmax|| (*it).center.x > *rightmin|| (*it).center.y < *topmax|| (*it).center.y>*bottommin|| (*it).Area>AreaHigh)
		{
			//(*it).vaild = false;
			it = muraRegions.erase(it);
			
		}
		else
		{
			it++;
		}
		
	}

	ippsFree(pBuffer);
	cvReleaseImageHeader(&show);
	
	return 0;


}


/**********************************************/
// WeiborMuraCalulate
//		根据韦伯定律计算前、背景的对比度
// Input:
// 		double beforeGrayMean;		连通域的灰度均值
//		double beforeArea;			连通域的面积
//		double backgroungGrayMean;	扩大半径后的包含前景+背景的灰度均值
// Output:
// 		int weibor;				输出计算的韦伯系数
// Return:
//    int  大于0：通过 -1-输入参数不合格 其他-待定
// Auther: Sun Zhe 12/19/2017
/**********************************************/

double WeiborMuraCalulate(double beforeGrayMean,double beforeArea,double backgroungGrayMean)
{
	if (beforeGrayMean <= 0 || beforeArea <= 0 || backgroungGrayMean <=0)
	throw -1;

	double weibor = (beforeGrayMean - backgroungGrayMean)/(1.97/pow(beforeArea,0.33)+0.72);
	
	return weibor;

}

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
int ContourInit_8u16u(Ipp8u *pSrc, int srcStep, Ipp16u *pDst, int dstStep, IppiSize size, int &nRoi)
{
	if (!pSrc || !pDst)
		throw 1;
	if (size.width <= 0 || size.height <= 0 || srcStep <= 0 || dstStep <= 0)
		throw 2;
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
		throw -1;
	//申请临时分配连通域空间
	Ipp8u *buffer = (Ipp8u*)ippsMalloc_8u(buffersize);
	ippiConvert_8u16u_C1R(pSrc, srcStep, pDst, dstStep, size);
	//分配连通域
	status = ippiLabelMarkers_16u_C1IR(pDst, dstStep, size, 1, 65534, ippiNormInf, &nRoi, buffer);
	if (status != ippStsNoErr)
	{
		ippsFree(buffer);
		throw -1;
	}
	if (nRoi <= 0 || nRoi > 65534)
	{
		nRoi = 0;
		ippsFree(buffer);
		throw 3;
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
		throw 1;
	if (size.width <= 0 || size.height <= 0)
		throw 2;
	if (!roi)
		throw 3;

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
		if (roi[i].Area <= 0 || roi[i].Area < low )// || roi[i].Area > high
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
			if (roi[label - 1].coordinate)
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
		if (roi[i].vaild == false)
			continue;
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

