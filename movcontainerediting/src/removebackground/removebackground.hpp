#ifndef REMOVEBACKGROUND_HPP
#define REMOVEBACKGROUND_HPP

#include <opencv2/opencv.hpp>
#include <iostream>

bool RemoveBackground(cv::VideoCapture& cap, bool mog2 = true);

#endif