#pragma once

#include "BlobAnalysis.h"


#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
class DLL_API VisBaSegmentationEnvironment
{
public:
	VisBaSegmentationEnvironment();
	~VisBaSegmentationEnvironment();

private:
	//VisBaFeatureExtraction CFeatureExtration;
	//VisBaImagePreprocess CImagePreprocess;
	//VisBaImageSegmentation CImageSegmentation;
	//VisBaMorphology CMorphology;
};