#pragma once
namespace ngp {
	namespace filters {
		void dilate(cv::Mat& srcfile, int dilation_size, int dilation_elem);
		void erode(cv::Mat& srcfile, int erosion_size, int erosion_elem);
		void resize(cv::Mat& srcfile, int width, int height, int interpolation);
		void canny(cv::Mat& srcfile, int min_threshold);
	}
}
