#ifndef FACE_DETECTOR_H_
#define FACE_DETECTOR_H_

#include "anchor_generator.h"
#include "opencv2/opencv.hpp"
#include "config.h"
#include "tools.h"
#include "types.h"
#include "face_alignment.h"


class FaceDetector {
 public:
  FaceDetector(const std::string& param_file, const std::string&bin_path_file);

  void LoadModel(const std::string& param_file,
                 const std::string& weight_file5);
  std::vector<face_det> detect(cv::Mat& img);
  

 private:
 
  ncnn::Net* _net = 0;

  
};

#endif