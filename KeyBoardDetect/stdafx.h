// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"
#include <stdio.h>
#include "iostream"
 #include<ipp.h>
#include"string.h"
#include "mkl.h"
#include<time.h>
#include<opencv2\highgui.hpp>
#include<opencv2\imgproc.hpp>
#include <opencv2/core/core.hpp>
#include<opencv2\contrib\contrib.hpp>

#ifndef  NORM_WIDTH,NORM_HEIGHT
#define NORM_WIDTH 230 //��һ����Ŀ�͸�
#define NORM_HEIGHT 230
#endif


int Project(Ipp8u* src, int step, IppiSize size, Ipp64f *project, int len, int direct);
int RemoveContour(Ipp8u *src, int step8u, IppiSize size, Ipp16u *Contours, int step16u, int label);

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
