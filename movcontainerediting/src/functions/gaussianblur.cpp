#include <opencv2/opencv.hpp>
#include <iostream>

//performs gaussian blur
cv::Mat gaussianblur(cv::Mat frame) {
    cv::Mat blurredFrame;
    cv::GaussianBlur(frame, blurredFrame, cv::Size(5, 5), 1.5);
    return blurredFrame;
}
