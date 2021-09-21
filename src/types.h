#ifndef TYPES_H_
#define TYPES_H_
#include <opencv2/opencv.hpp>

struct face_landmark
{
    float x[5];
    float y[5];
};

struct face_det
{
    cv::Rect boxes;
    float conf;
    face_landmark landmark;
    cv::Mat face_aligned;
    bool face_mask;
};

struct feature
{
    cv::Mat f;

};
#endif
