#include <opencv2/opencv.hpp>
#include <iostream>
#include "gaussianblur.hpp"
#include "grayscale.hpp"

/*
functions performs classic sobel pipeline!
*/
cv::Mat sobel(cv::Mat frame) {
    frame = grayscale(frame);
    frame = gaussianblur(frame);

    cv::Mat gradX, gradY;
    cv::Sobel(frame, gradX, CV_16S, 1, 0, 3);
    cv::Sobel(frame, gradY, CV_16S, 0, 1, 3);

    cv::Mat absGradX, absGradY, result;
    cv::convertScaleAbs(gradX, absGradX);
    cv::convertScaleAbs(gradY, absGradY);
    cv::addWeighted(absGradX, 0.5, absGradY, 0.5, 0, result);

    return result;
}
