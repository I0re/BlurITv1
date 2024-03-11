#include "VideoProcessor.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/core/core.hpp>

VideoProcessor::VideoProcessor(const std::string& path) {
    video.open(path);
}

VideoProcessor::~VideoProcessor() {
    release();
}

bool VideoProcessor::openVideo() {
    return video.isOpened();
}

bool VideoProcessor::readFrame(cv::Mat& frame) {
    return video.read(frame);
}

void VideoProcessor::resizeFrame(cv::Mat& frame, const cv::Size& size) {
    cv::resize(frame, frame, size);
}

double VideoProcessor::getFPS() const {
    return video.get(cv::CAP_PROP_FPS);
}

bool VideoProcessor::isOpened() const {
    return video.isOpened();
}

void VideoProcessor::release() {
    if (video.isOpened()) {
        video.release();
    }
}