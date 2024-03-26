#pragma once


#ifdef MARKERLIBDLL_EXPORTS
#define MARKERLIBDLL_API __declspec(dllexport)
#else
#define MARKERLIBDLL_API __declspec(dllimport)
#endif


#include "fundtypes.h"
#include "extcode.h"

#include "lv_prolog.h"
#include "platdefines.h"

/* LabVIEW created typedef */
typedef struct {
	int32 dimSizes[2];
	float_t elt[1];
} Arr2D_SGL;
typedef Arr2D_SGL** Arr2D_SGLHdl;

#include "lv_epilog.h"

#if IsOpSystem64Bit
#define uPtr uQ //unsigned Quad aka 64-bit
#else
#define uPtr uL //unsigned Long aka 32-bit
#endif

extern "C" MARKERLIBDLL_API int32_t refineCorner(const Arr2D_SGLHdl image, float* pointX, float* pointY,int32_t winSize,int32_t zeroZone);


