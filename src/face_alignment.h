#ifndef ALIGNMENT_H_
#define ALIGNMENT_H_

#include <opencv2/opencv.hpp>

int get_aligned_face(cv::Mat& img, float* landmark, int landmark_number, int desired_size,cv::Mat& out);

#endif
