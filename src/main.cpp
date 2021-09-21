#include "face_detector.h"
#include "face_extractor.h"
#include <time.h>
#define CLOCKS_PER_SEC 1000000


FaceDetector *face_detector = new FaceDetector("../models/retina.param","../models/retina.bin");
FaceExtractor *face_extractor = new FaceExtractor("../models/iresnet50_1.param","../models/iresnet50_1.bin");



float distance(cv::Mat f1,cv::Mat f2){
        return cv::norm( f1, f2);
}


cv::Mat img1 = cv::imread("../images/test3.jpg");
cv::Mat img2 = cv::imread("../images/test4.jpg");

int main(){

std::vector<face_det> dets1 = face_detector->detect(img1);
std::vector<face_det> dets2 = face_detector->detect(img2);
std::cout<<"image1 "<<" : "<<dets1.size()<<" faces \n";
std::cout<<"image2 "<<" : "<<dets2.size()<<" faces \n";
for(int i = 0 ; i<dets1.size();i++){
    for(int j = 0 ; j<dets2.size();j++){
        feature feature1 =face_extractor->extract(dets1[i].face_aligned);
        feature feature2 =face_extractor->extract(dets2[j].face_aligned);
        std::cout<<"dis : "<<distance(feature1.f,feature2.f)<<"\n";
    }
}

    return 0;
}