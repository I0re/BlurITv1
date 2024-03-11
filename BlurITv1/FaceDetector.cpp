#include "FaceDetector.h"

FaceDetector::FaceDetector() {}

void FaceDetector::loadCascade(const std::string& path) {
    facedetect.load(path);
}

void FaceDetector::detectFaces(const cv::Mat& frame, std::vector<cv::Rect>& faces) {
    facedetect.detectMultiScale(frame, faces, 1.3, 5);
}
