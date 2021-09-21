
// Copyright 2021 The DaisyKit Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.



#include "face_extractor.h"



#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>



FaceExtractor::FaceExtractor(
    const std::string& param_file, const std::string& weight_file) {
  LoadModel(param_file, weight_file);
}


void FaceExtractor::LoadModel(const std::string& param_file,
                                        const std::string& weight_file) {
  if (model_) {
    delete model_;
    model_ = nullptr;
  }
  model_ = new ncnn::Net;
  int ret_param = model_->load_param(param_file.c_str());
  int ret_model = model_->load_model(weight_file.c_str());
  if (ret_param != 0 || ret_model != 0) {
    exit(1);
  }
}




void preprocess(cv::Mat& image, ncnn::Mat& in)
{
    int img_w = image.cols;
    int img_h = image.rows;
    in = ncnn::Mat::from_pixels(image.data, ncnn::Mat::PIXEL_BGR, img_w, img_h);
    const float mean_vals[3] = {127.5f, 127.5f, 127.5f};
    const float norm_vals[3] = {1.0 / 127.5, 1.0 / 127.5, 1.0 / 127.5};
    
    in.substract_mean_normalize(mean_vals, norm_vals);
}


feature FaceExtractor::extract(cv::Mat& image)
{

   
    float fnum[512];
    float* prob=fnum;
    feature feature_out;
    ncnn::Mat input;
    ncnn::Mat out;


    preprocess(image, input);
    ncnn::MutexLockGuard g(lock_);
    auto ex = model_->create_extractor();
    ex.input("input", input);
    ex.extract("output", out);
    

    for (int j = 0; j < 512; j++) {
        fnum[j] = out[j];
    }   
    cv::Mat out_m(512, 1, CV_32FC1, prob);
    cv::Mat out_norm;
    cv::normalize(out_m, feature_out.f);
    return feature_out;
}
