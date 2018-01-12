// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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
#define NORM_WIDTH 230 //归一化后的宽和高
#define NORM_HEIGHT 230
#endif


int Project(Ipp8u* src, int step, IppiSize size, Ipp64f *project, int len, int direct);
int RemoveContour(Ipp8u *src, int step8u, IppiSize size, Ipp16u *Contours, int step16u, int label);

// TODO:  在此处引用程序需要的其他头文件
