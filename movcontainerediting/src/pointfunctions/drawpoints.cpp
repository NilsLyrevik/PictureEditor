#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
//simple function that takes points + frame and plots points onto frame
void drawpoints (std::vector<cv::Point> points, cv::Mat frame){

    for (auto &pt : points) {
    cv::circle(frame, pt, 1, cv::Scalar(0, 0, 255), -1); // change between frame or edgerame
    }

}