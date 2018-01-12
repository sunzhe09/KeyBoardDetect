// KeyBoardDetect.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"

#define _CRTDBG_MAP_ALLOC
#include<crtdbg.h>


#ifdef _DEBUG //���Ҫ���ϣ����򲻻�������嵽�Ǹ��ļ��У��������������ڴ�й¶�ĸ�cpp�ļ��������Ϣ��  
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
	//const string filename = "W:/�㷨��/����/keyboard/ȱ������/*.jpg";
	Directory dir;
	string path1 = "W:/�㷨��/����/keyboard/ȱ������/";
	//string path1 = "C:/Users/bm00133/Desktop/";
	string dst_path = "W:/�㷨��/����/keyboard/result/";
	string  exten1 = "*.jpg";
	vector<string> filenames = dir.GetListFiles(path1, exten1, false);
	
	for (vector<string> ::iterator it = filenames.begin(); it != filenames.end(); it++)
	{

		//����ڴ�й©
		_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
		clock_t start, finish;
		double totaltime;
		Mat temp = imread(path1+*it,0);//��ȡ��ʱ��ҶȻ���


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
					 cerr << "error������LigitEnhance������ͼ��Ϊ�գ�\n";
					 exit(1);
				 }
				 else if (a==2)
				 {
					 cerr << "error������LigitEnhance������ͼ�񲽳����ϸ�\n";
					 exit(1);
				 }
				 else if (a == 3)
				 {
					 cerr << "error������LigitEnhance������ͼ��ߴ粻�ϸ�\n";
					 exit(1);
				 }
				 else if (a == 4)
				 {
					 cerr << "error������LigitEnhance��������ǿ�������ϸ�\n";
					 exit(1);
				 }
				 else if (a == -1)
				 {
					 cerr << " error������LigitEnhance������ipp����ʧ�ܣ�\n";
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
					cerr << " error������imgMean����������ͼ�񲽳����ϸ�\n";
					exit(1);
				}
				else if (a == 2)
				{
					cerr << " error������imgMean������ͼ��ߴ粻�ϸ�\n";
					exit(1);
				}
					
				else if (a == -1)
				{
					cerr << " error������imgMean����������ͼ��Ϊ�գ�\n";
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
			//1-����ͼ��Ϊ�� 2-����ͼ�񲽳����ϸ� 3-ͼ��ߴ粻�ϸ�  -1-IPP���ó��� ����-����
			if (a==1)
			{
				cerr << "error������RegionsSegement����������ͼ��Ϊ��" << endl;
				exit(1);
			}
			if (a == 2)
			{
				cerr << "error������RegionsSegement����������ͼ�񲽳����ϸ�" << endl;
				exit(1);
			}
			if (a == 3)
			{
				cerr << "error������RegionsSegement������ͼ��ߴ粻�ϸ�" << endl;
				exit(1);
			}
			if (a == -1)
			{
				cerr << "error������RegionsSegement������IPP���ó���" << endl;
				exit(1);
			}
			
		}
		

		finish = clock();
		totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "�˳��������ʱ��Ϊ:" << totaltime << "�룡\n" << endl;

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
			rectangle(temp, pt1, pt2, Scalar(255), 1, 4, 0);//�õ㻭���δ�  
			
			sprintf(showMsg, "(MEAN: %f,VAR: %f)", (*it1).mean, (*it1).var);
			
			putText(temp, showMsg, Point(50, 50 + k * 50), CV_FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255), 1, 2); // ��ʾ�ַ�

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

//ͼ��ȡ��
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

//opencv��ʾͼ��
void imgShow(unsigned char* src, int srcStep, int width, int height)
{
	IplImage *show = cvCreateImageHeader(cvSize(width, height), 8u, 0);
	cvSetData(show, (uchar*)src, srcStep);
	cvReleaseImageHeader(&show);
}


/**********************************************/
// imgMean
//		��Сֵ�˲�/
// Input:
// 		Ipp8u*src;				δ�����ԭͼ��		
//		int src_step;			ͼ��Ĳ���
//		IppiSize ROI			ͼ���ROI��Χ	
// Output:
//		unsigned char *dst;		�˲����ͼ��
// Return:
//    int  0-ͨ�� -1-����ͼ��Ϊ�� 1-����ͼ�񲽳����ϸ� 2-ͼ��ߴ粻�ϸ�  
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
			
			//��һ��������Χ��8������ֵ�ֱ�ֵ��p[0]��p[8]
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
//		ͼ����ǿ
// Input:
// 		Ipp8u*src;				δ�����ԭͼ��		
//		int src_step;			ͼ��Ĳ���
//		IppiSize roiSize		ͼ���ROI��Χ
//		Ipp8u mulFactorValue    ͼ��˷����ӣ���ǿ�Աȶȣ�
//		Ipp8u subFactorValue	ͼ��������ӣ�������
// Output:
//		Ipp8u *dst;				��ǿ���ͼ��
// Return:
//		int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ�񲽳����ϸ� 3-ͼ��ߴ粻�ϸ� 4-��ǿ�������ϸ�  -1-ipp����ʧ��
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
//		ͼ��ָ���ͨ�����
// Input:
// 		unsigned char* src;			δ�����ԭͼ��
//		unsigned char *pSrcMarker;	��ǿ���ͼ��
//		int srcMarkerStep;			ͼ��Ĳ���
//		IppiSize roiSize;			ͼ���ROI��Χ	
// Output:
//		vector<ROI> &muraRegions	���muraȱ�ݵ���ͨ�򼯺�
// Return:
//		int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ�񲽳����ϸ� 3-ͼ��ߴ粻�ϸ�  -1-IPP���ó��� ����-����
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


	/*��ʾ�м���*/
	IplImage *show = cvCreateImageHeader(cvSize(roiSize.width, roiSize.height), 8u, 1);
	cvSetData(show, (unsigned char*)pSrcMarker, srcMarkerStep);

	Ipp16u *Contours = NULL;
	Contours = (Ipp16u*)malloc(sizeof(Ipp16u) * roiSize.width * roiSize.height);//markͼ����
	int nRoi = 0;
	try
	{ 
		ContourInit_8u16u(pSrcMarker, srcMarkerStep, Contours, roiSize.width * sizeof(Ipp16u), roiSize, nRoi); 
	}
	catch(int a)
	{
		//1 - ����ͼ��Ϊ�� 2 - ����ͼ��߶Ȳ��ϸ� 3 - Roi��ȡ��������� - 1 - IPP���ó��� ���� - ����
		if (a == 1)
		{
			cerr << "error����;ContourInit_8u16u(),����ͼ��Ϊ�գ�" << endl;
			exit(1);
		}
		else if (a == 2)
		{
			cerr << "error����;ContourInit_8u16u(),����ͼ��߶Ȳ��ϸ�" << endl;
			exit(1);
		}
		else if (a==3)
		{
			cerr << "error����;ContourInit_8u16u(),Roi��ȡ��������ޣ�" << endl;
			exit(1);
		}
		else if (a == -1)
		{
			cerr << "error����;ContourInit_8u16u(),IPP���ó���" << endl;
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
		//1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-roi��ͨ��������δ����ռ� -1-IPP���ó��� ����-����
		if (a == 1)
		{
			cerr << "error����;AllocationContours(),����ͼ��Ϊ�գ�" << endl;
			exit(1);
		}
		else if (a==2)
		{
			cerr << "error����;AllocationContours(),����ͼ��߶Ȳ��ϸ�" << endl;
			exit(1);
		}
		else if (a == 3)
		{
			cerr << "error����;AllocationContours(),roi��ͨ��������δ����ռ䣡" << endl;
			exit(1);
		}
		else if (a == -1)
		{
			cerr << "error����;AllocationContours(),IPP���ó���" << endl;
			exit(1);
		}
	}
	
	try

	{
		GetROIDistribution(src, srcMarkerStep, roiSize, nRoi, Rois);
	}
	catch (int a)
	{
		//1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-roi��ͨ��������δ����ռ� -1-IPP���ó��� ����-����
		if (a == 1)
		{
			cerr << "error����;GetROIDistribution(),����ͼ��Ϊ�գ�" << endl;
			exit(1);
		}
		else if (a==2)
		{
			cerr << "error����;GetROIDistribution(),����ͼ��߶Ȳ��ϸ�" << endl;
			exit(1);
		}
		else if (a==3)
		{
			cerr << "error����;GetROIDistribution(),roi��ͨ��������δ����ռ�" << endl;
			exit(1);
		}

		else if (a==-1)
		{
			cerr << "error����;GetROIDistribution(),IPP���ó���" << endl;
			exit(1);
		}

	}

	double grayMean_before=0.0, grayMean_back=0.0;

	int rel = 0;//���󱳾���ƫ����
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

		//����Ŀ������ƫ����
		rel = sqrt(Rois[i].Area);
		int numPixs = 0;
		
		for (int m = Rois[i].region.topleft.y - rel; m < Rois[i].region.bottomright.y + rel; m++)
		{
			for (int n = Rois[i].region.topleft.x - rel; n < Rois[i].region.bottomright.x + rel; n++)
			{
				bool flag = true;//true����û��Խ��
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
				cerr << "error����;WeiborMuraCalulate(),����������ϸ�" << endl;
				exit(1);
			}

		}
		
		cout << k << endl;
		//�ж��Ƿ�Ϊ������mura
		double height_roi = Rois[i].region.bottomright.y - Rois[i].region.topleft.y;
		double width_roi = Rois[i].region.bottomright.x - Rois[i].region.topleft.x;
		double rate = height_roi / width_roi;
		
		if (rate < 1 )
			rate = 1 / rate;
		double top_b = 0.0,  bottom_t = 0.0, left_r = 0.0, right_l = 0.0;

		//�ж����µ�����©�ⷶΧ
		if ((Rois[i].region.bottomright.x - Rois[i].region.topleft.x) > 80)
		{
			
			if((roiSize.height - Rois[i].center.y)<25)
			{ 
			 //�ײ�����©��
			 top_b = Rois[i].region.topleft.y;
			 bottom.push_back(top_b);

			}

			if (Rois[i].center.y < 25)
			{
			//��������©��		
			bottom_t = Rois[i].region.bottomright.y;
			top.push_back(bottom_t);
			}
			
		
		}

		//�ж����ҵ�����©�ⷶΧ
		if ((Rois[i].region.bottomright.y - Rois[i].region.topleft.y) > 80 )
		{
			
			if ( (roiSize.width - Rois[i].center.x) < 30)
			{
				//�Ҳ�����©��
				left_r = Rois[i].region.topleft.x;
				right.push_back(left_r);
				
			}

			if (Rois[i].center.x < 30)
			{
				//������©��			
				right_l = Rois[i].region.bottomright.x;
				left.push_back(right_l);
			}

		}


		if ( lowThreshold_weibor <k&&k < highThreshold_weibor&&Rois[i].var < 8000)//rate miss
		{
			muraRegions.push_back(Rois[i]);
		}
			
	}
		
	//��ñ߽�ֵ
	
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
//		����Τ�����ɼ���ǰ�������ĶԱȶ�
// Input:
// 		double beforeGrayMean;		��ͨ��ĻҶȾ�ֵ
//		double beforeArea;			��ͨ������
//		double backgroungGrayMean;	����뾶��İ���ǰ��+�����ĻҶȾ�ֵ
// Output:
// 		int weibor;				��������Τ��ϵ��
// Return:
//    int  ����0��ͨ�� -1-����������ϸ� ����-����
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
//		��ͨ���ʼ��
// Input:
// 		Ipp8u  *pSrc;			����ͼ��ͷ��ַ
//		int srcStep;			����ͼ����
//		Ipp16u *pDst;			�����������ͨ���ͼ��ͷ��ַ
//		int dstStep;			������ͨ��ͼ����
//		IppiSize size;			����ͼ��ߴ�
// Output:
//		Ipp16u *pDst;			�����ͨ��ͼ���ͷ��ַ
// 		int &nRoi;				�����ͨ�����
// Return:
//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-Roi��ȡ��������� -1-IPP���ó��� ����-����
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

	//������ͨ���������ռ�
	status = ippiLabelMarkersGetBufferSize_16u_C1R(size, &buffersize);
	if (status != ippStsNoErr)
		throw -1;
	//������ʱ������ͨ��ռ�
	Ipp8u *buffer = (Ipp8u*)ippsMalloc_8u(buffersize);
	ippiConvert_8u16u_C1R(pSrc, srcStep, pDst, dstStep, size);
	//������ͨ��
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
//		��ȡ��ͨ������������ģ������Լ�����
// Input:
// 		Ipp16u *Contour;		������ͨͼ��ͷ��ַ
//		IppiSize size;			����ͼ��ߴ�
//		int nRoi;				������ͨ�����
//		int AreaLow;			����������
//		int AreaHigh;			����������
// Output:
// 		ROI *roi;				��ͨ������
// Return:
//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-roi��ͨ��������δ����ռ� -1-IPP���ó��� ����-����
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

	//��ȡROI
	for (int r = 0; r < size.height; r++)
	{
		for (int c = 0; c < size.width; c++)
		{
			int label = Contour[r * size.width + c];//��ʱһ��Contours����ռ2λ
			if (label <= 0)
				continue;
			roi[label - 1].Area++;
			roi[label - 1].center.x += c;
			roi[label - 1].center.y += r;
			//��ȡÿ����ͨ������������µ�����
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
	//��ȡ���������,�����������ͨ������ռ�
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
	//��������������ۼ�����
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
//		��ȡ��ͨ����������
// Input:
// 		Ipp8u *pSrc;			����ԭͼͷ��ַ
//		int step;				����ԭͼ���
//		IppiSize size;			����ԭͼ�ߴ�
//		int nRoi;				������ͨ�����
// Output:
// 		ROI *roi;				��ͨ������
// Return:
//    int  0-ͨ�� 1-����ͼ��Ϊ�� 2-����ͼ��߶Ȳ��ϸ� 3-roi��ͨ��������δ����ռ� -1-IPP���ó��� ����-����
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
	//��ʼ����������
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

