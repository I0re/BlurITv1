#include "FaceTracker.h"

FaceTracker::FaceTracker() {}

void FaceTracker::initTrackers(const cv::Mat& frame, const std::vector<cv::Rect>& rects) {
    trackers.clear();

    for (const auto& rect : rects) {
        cv::Ptr<cv::Tracker> tracker = cv::TrackerKCF::create();
        tracker->init(frame, rect);
        trackers.push_back(tracker);
    }
}

bool FaceTracker::updateTrackers(const cv::Mat& frame, std::vector<cv::Rect>& rects) {
    bool allUpdated = true;
    rects.clear();

    for (const auto& tracker : trackers) {
        cv::Rect rect;
        if (tracker->update(frame, rect)) {
            rects.push_back(rect);
        }
        else {
            allUpdated = false;
        }
    }

    return allUpdated;
}