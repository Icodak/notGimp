#include <opencv2/opencv.hpp>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "filters.h"

void ngp::filters::canny(cv::Mat& srcfile, int min_threshold) {
    const int max_minThreshold = 100;
    const int ratio = 3;
    const int kernel_size = 3;

    cv::Mat srcfile_gray, detected_edges, copy;
    if (min_threshold <= max_minThreshold){
        cv::cvtColor( srcfile, srcfile_gray, cv::COLOR_BGR2GRAY );
        cv::blur( srcfile_gray, detected_edges, cv::Size(3,3) );
    	cv::Canny(detected_edges, detected_edges, min_threshold, min_threshold*ratio, kernel_size);
    	copy = cv::Scalar::all(0);
        srcfile.copyTo( copy, detected_edges);
        copy.copyTo(srcfile);
    } else {
        std::cout << "Inserted value is greater than 100, please provide valid value" << std::endl;
    }
}
