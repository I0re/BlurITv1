#pragma once
#include <opencv2/tracking.hpp>
#include <vector>

class FaceTracker {
public:
    FaceTracker();
    void initTrackers(const cv::Mat& frame, const std::vector<cv::Rect>& rects);
    bool updateTrackers(const cv::Mat& frame, std::vector<cv::Rect>& rects);

private:
    std::vector<cv::Ptr<cv::Tracker>> trackers;
};