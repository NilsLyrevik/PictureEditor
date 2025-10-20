#include <opencv2/opencv.hpp>
#include <iostream>

//makes frame gray
cv::Mat grayscale(cv::Mat frame) {
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
    return grayFrame;
}