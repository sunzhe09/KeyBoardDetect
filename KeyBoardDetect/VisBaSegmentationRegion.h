#pragma once

#include "BlobAnalysis.h"

#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif
class DLL_API VisBaSegmentationRegion
{
public:
	VisBaSegmentationRegion();
	~VisBaSegmentationRegion();

private:
	//VisBaFeatureExtraction CFeatureExtration;
	//VisBaImagePreprocess CImagePreprocess;
	//VisBaImageSegmentation CImageSegmentation;
	//VisBaMorphology CMorphology;
};

