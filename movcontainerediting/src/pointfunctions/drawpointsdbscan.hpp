#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include "dbscan.hpp"

// drawNoise = true will plot outliers in red
void drawpointsdbscan(const std::vector<DBSCANPoint>& points, cv::Mat& frame, bool drawNoise=false);
