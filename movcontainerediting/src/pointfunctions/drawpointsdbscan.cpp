#include "drawpointsdbscan.hpp"

void drawpointsdbscan(const std::vector<DBSCANPoint>& points, cv::Mat& frame, bool drawNoise) {
    int maxCluster = 0;
    for (const auto& p : points)
        if (p.label > maxCluster) maxCluster = p.label;

    // Ensure colors array is non-empty
    if (maxCluster == 0) maxCluster = 1;

    std::vector<cv::Scalar> colors;
    cv::RNG rng(12345);
    for (int i = 0; i <= maxCluster; ++i)
        colors.push_back(cv::Scalar(rng.uniform(0,255), rng.uniform(0,255), rng.uniform(0,255)));

    for (const auto& pt : points) {
        if (pt.label > 0) {
            cv::Scalar color = colors[pt.label % colors.size()];
            cv::circle(frame, pt.data, 2, color, -1);
        } else if (drawNoise) {
            cv::circle(frame, pt.data, 2, cv::Scalar(0,0,255), -1);
        }
    }
}
