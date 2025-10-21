#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include "sobel.hpp"
#include "../pointfunctions/drawpoints.hpp"
#include "../pointfunctions/drawpointsdbscan.hpp"
#include "../pointfunctions/dbscan.hpp"

const unsigned char threshold = 100;

cv::Mat drawedges (cv::Mat frame){
    cv::Mat edgeframe = sobel(frame);
    std::vector<cv::Point> points;

    //Extract edgepoints into points
    for (int y = 0; y < edgeframe.rows; ++y) {
        for (int x = 0; x < edgeframe.cols; ++x) {

            if (edgeframe.at<uchar>(y, x) > threshold) { // threshold to detect strong edges
                points.push_back(cv::Point(x, y)); // maybe not push into list for computational stuff. but for now this will do. maybe i can handle it like a point cloud or smth in the future
            }

        }
    }
    /*
    use this to not color clusters using dbscan
    drawpoints(points, frame); // edits each frame (returns void)
    */
    std::vector<DBSCANPoint> dbpoints = createDB(points);
    dbscan(dbpoints,10.0,2);
    drawpointsdbscan(dbpoints, frame, true);

    return frame;

}