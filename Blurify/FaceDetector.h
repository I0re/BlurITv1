#pragma once
#include <opencv2/objdetect.hpp>

class FaceDetector {
public:
    FaceDetector();
    void loadCascade(const std::string& path);
    void detectFaces(const cv::Mat& frame, std::vector<cv::Rect>& faces);

private:
    cv::CascadeClassifier facedetect;
};
