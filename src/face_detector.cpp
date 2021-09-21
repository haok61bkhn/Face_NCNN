#include "face_detector.h"

FaceDetector::FaceDetector(const std::string& param_file,
                           const std::string& weight_file ){
  LoadModel(param_file, weight_file);
}

void FaceDetector::LoadModel(const std::string& param_file,
                        const std::string& weight_file){
    
    if (_net) {
        delete _net;
        _net = nullptr;
    }
    _net = new ncnn::Net;

	int ret_param = _net->load_param(param_file.c_str());
    int ret_model = _net->load_model(weight_file.c_str());
    if (ret_param != 0 || ret_model != 0) {
        exit(1);
    }

}

std::vector<face_det> FaceDetector::detect(cv::Mat& img){
    std::vector<face_det> dets;
    ncnn::Mat input = ncnn::Mat::from_pixels_resize(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows, width, height);
    float ratio_x = float(img.cols)/width;
    float ratio_y = float(img.rows)/height;
    input.substract_mean_normalize(pixel_mean, pixel_std);
	ncnn::Extractor _extractor = _net->create_extractor();
	_extractor.input("data", input);


    std::vector<AnchorGenerator> ac(_feat_stride_fpn.size());
    for (int i = 0; i < _feat_stride_fpn.size(); ++i) {
        int stride = _feat_stride_fpn[i];
        ac[i].Init(stride, anchor_cfg[stride], false);
    }

    std::vector<Anchor> proposals;
    proposals.clear();

    for (int i = 0; i < _feat_stride_fpn.size(); ++i) { 
    	ncnn::Mat cls;
    	ncnn::Mat reg;
    	ncnn::Mat pts;

        char clsname[100]; sprintf(clsname, "face_rpn_cls_prob_reshape_stride%d", _feat_stride_fpn[i]);
        char regname[100]; sprintf(regname, "face_rpn_bbox_pred_stride%d", _feat_stride_fpn[i]);
        char ptsname[100]; sprintf(ptsname, "face_rpn_landmark_pred_stride%d", _feat_stride_fpn[i]);
        _extractor.extract(clsname, cls);
        _extractor.extract(regname, reg);
        _extractor.extract(ptsname, pts);
        ac[i].FilterAnchor(cls, reg, pts, proposals);

    }

    std::vector<Anchor> result;
   
   
    

    nms_cpu(proposals, nms_threshold, result);

    for(int i = 0; i < result.size(); i ++)
    {
        face_det det;
        cv::Rect rect((int)result[i].finalbox.x*ratio_x,(int)result[i].finalbox.y*ratio_y,(int)result[i].finalbox.width*ratio_x, (int)result[i].finalbox.height*ratio_y);
        det.face_mask=false;
        det.boxes = rect;
        for (int j = 0; j < result[i].pts.size(); ++j) {
            det.landmark.x[j]=(int)result[i].pts[j].x*ratio_x;
            det.landmark.y[j]=(int)result[i].pts[j].y*ratio_y;
        }
        int a = get_aligned_face(img, (float *)&det.landmark, 5, 112, det.face_aligned);
        dets.push_back(det);
        

    }
    return dets;

}


   

	
    
   
    

 


