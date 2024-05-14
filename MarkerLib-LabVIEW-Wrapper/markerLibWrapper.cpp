#include "markerLibWrapper.h"
#include "markerLib/markerFinder.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/calib3d.hpp>

template <typename T>
cv::Mat createMat(T* data, int rows, int cols, int chs = 1) {
	// Create Mat from buffer 
	cv::Mat mat(rows, cols, CV_MAKETYPE(cv::DataType<T>::type, chs));
	memcpy(mat.data, data, rows * cols * chs * sizeof(T));
	return mat;
}

int32_t bilateralFilter(Arr2D_SGLHdl inOutput,const int d, const double sigmaColor, const double sigmaSpace) {
	try{

		int rows = (*inOutput)->dimSizes[0];
		int cols = (*inOutput)->dimSizes[1];

		//dimension check
		if (rows == 0 || cols == 0)
			return EXIT_FAILURE;

		cv::Mat input = createMat(&(**inOutput).elt[0], rows, cols);
		cv::Mat output;

		cv::bilateralFilter(input, output, d, sigmaColor, sigmaSpace);

		int elemSize = sizeof((*inOutput)->elt);
		MoveBlock(output.data, &(*inOutput)->elt[0], rows * cols * elemSize);

	}
	catch (const std::exception& e) {
		//log
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t refineCorner(const Arr2D_SGLHdl image, float* pointX, float* pointY, int32_t winSize,int32_t zeroZone) {
	try {
		BaseLib::STBimage stbDummy;
		int32_t size = (*image)->dimSizes[0] * (*image)->dimSizes[1] * sizeof(float_t);
		stbDummy.dataSGL = std::make_unique<float_t[]>(size);
		std::memcpy(stbDummy.dataSGL.get(), (*image)->elt, size);
		stbDummy.channels = 1;
		stbDummy.width = (*image)->dimSizes[1];
		stbDummy.height = (*image)->dimSizes[0];
		stbDummy.channels = 1;


		MarkerLib::MarkerFinder finder;


		return finder.refineCorner(stbDummy, pointX, pointY, winSize, zeroZone);
	}
	catch (const std::exception& e) {
		//log
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

int32_t undistort(Arr2D_DBLHdl inOutput,const Arr2D_DBLHdl cameraMatrix,const Arr_DBLHdl distCoeffs) {
	try {
		int rows = (*inOutput)->dimSizes[0];
		int cols = (*inOutput)->dimSizes[1];

		int rowsCamMat = (*cameraMatrix)->dimSizes[0];
		int colsCamMat = (*cameraMatrix)->dimSizes[1];

		//dimension check
		if (rows == 0 || cols == 0)
			return EXIT_FAILURE;

		if (rowsCamMat != 3 || colsCamMat != 3)
			return 5010;

		if ((**distCoeffs).dimSize != 8)
			return 5011;

		cv::Mat input = createMat(&(**inOutput).elt[0], rows, cols);
		cv::Mat cameraMatrixMat = createMat(&(**cameraMatrix).elt[0], rowsCamMat, colsCamMat);
		cv::Mat distCoeffsMat = createMat(&(**distCoeffs).elt[0], 8, 1);

		cv::Mat output;
		cv::undistort(input, output, cameraMatrixMat, distCoeffsMat);

		int elemSize = sizeof((*inOutput)->elt);
		MoveBlock(output.data, &(*inOutput)->elt[0], rows * cols * elemSize);
	}
	catch (const std::exception& e) {
		//log
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}