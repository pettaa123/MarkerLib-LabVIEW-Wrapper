#include "markerLibWrapper.h"
#include "markerLib/markerFinder.h"


int32_t refineCorner(const Arr2D_SGLHdl image, float* pointX, float* pointY, int32_t winSize,int32_t zeroZone) {

	BaseLib::STBimage stbDummy;
	int32_t size = (*image)->dimSizes[0] * (*image)->dimSizes[1] * sizeof(float_t);
	stbDummy.dataSGL = std::make_unique<float_t[]>(size);
	std::memcpy(stbDummy.dataSGL.get(), (*image)->elt, size);
	stbDummy.channels = 1;
	stbDummy.width = (*image)->dimSizes[1];
	stbDummy.height = (*image)->dimSizes[0];
	stbDummy.channels = 1;
	
	
	MarkerLib::MarkerFinder finder;

	
	return finder.refineCorner(stbDummy, pointX,pointY, winSize,zeroZone);


}