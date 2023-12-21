#pragma once
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class VideoProcessor {
public:
    VideoProcessor(const std::string& path);
    ~VideoProcessor();
    bool openVideo();
    bool readFrame(cv::Mat& frame);
    void resizeFrame(cv::Mat& frame, const cv::Size& size);
    double getFPS() const;
    bool isOpened() const;
    void release();

private:
    cv::VideoCapture video;
};
