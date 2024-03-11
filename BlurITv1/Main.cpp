#include <iostream>
#include <thread>
#include <opencv2/core/ocl.hpp>
#include <opencv2/imgproc.hpp>
#include "VideoProcessor.h"
#include "FaceDetector.h"
#include "FaceTracker.h"

//C:\Users\Owner\Desktop\GitHub C++ Projects\Blurify\Resources\test.mp4 FOR TESTING

using namespace cv;
using namespace std;
using namespace ocl;

int main() {
    // Enable OpenCL for gpu acceleration (not implemented)
    setUseOpenCL(true);

    if (!haveOpenCL()) {
        cerr << "OpenCL is not supported on your system." << endl;
        return -1;
    }

    // Ask user input for the path to the video
    cout << "Enter the full path to the video you wish to blur faces from: ";
    string videoPath;
    getline(cin, videoPath);

    // Ask the user for the desired name for the file
    cout << "What do you want this file to be named (e.g., Cars.mp4): ";
    string handleName;
    getline(cin, handleName);

    // Initialize VideoProcessor
    VideoProcessor videoProcessor(videoPath);
    if (!videoProcessor.openVideo()) {
        cerr << "Error: Could not open the video file." << endl;
        return -1;
    }

    FaceDetector faceDetector1;
    FaceDetector faceDetector2;
    //since this is a basic implementation i hardcoded the path to haarcasades
    faceDetector1.loadCascade("C:/Users/Owner/Desktop/GitHub C++ Projects/Blurify/Resources/haarcascade_frontalface_default.xml");
    faceDetector2.loadCascade("C:/Users/Owner/Desktop/GitHub C++ Projects/Blurify/Resources/lbpcascade_profileface.xml");

    FaceTracker faceTracker;

    vector<Rect> trackedFaces;

    double fps = videoProcessor.getFPS();
    Size outputSize(1280, 720);

    while (true) {
        Mat frame;
        if (!videoProcessor.readFrame(frame)) {
            cerr << "Error: Could not read frame from the video." << endl;
            break;
        }

        videoProcessor.resizeFrame(frame, outputSize);

        vector<Rect> faceRectangles;
        faceDetector1.detectFaces(frame, faceRectangles);

        if (!faceRectangles.empty()) {
            rectangle(frame, faceRectangles[0], Scalar(0, 255, 0), 2);


            Mat background = frame.clone();
            rectangle(background, faceRectangles[0], Scalar(0, 0, 0), -1);


            vector<Rect> profileFaces;
            faceDetector2.detectFaces(background, profileFaces);

            if (!profileFaces.empty()) {

                rectangle(frame, profileFaces[0], Scalar(0, 0, 255), 2);

                trackedFaces = { faceRectangles[0], profileFaces[0] };
                faceTracker.initTrackers(frame, trackedFaces);
            }
        }

        // Update the tracking result for each tracked face
        if (!trackedFaces.empty() && faceTracker.updateTrackers(frame, trackedFaces)) {
            for (size_t i = 0; i < trackedFaces.size(); ++i) {
                Scalar color(50, 50 + i * 100, 255);
                rectangle(frame, trackedFaces[i], color, 3);

                // Blur the detected face region
                int PowerOfBlur = 51;
                Mat faceROI = frame(trackedFaces[i]);
                GaussianBlur(faceROI, faceROI, Size(PowerOfBlur, PowerOfBlur), 0, 0);

            }
        }
        else {
            trackedFaces.clear();
        }

        imshow(handleName, frame);

        //esc key to quit
        if (waitKey(1) == 27) {
            break;
        }
    }

    videoProcessor.release();
    destroyAllWindows();

    return 0;
}