/*
source:
https://en.wikipedia.org/wiki/DBSCAN

simple dbscan made on points
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <set>
#include <algorithm>

enum class PointLabel { NOISE = 0, UNDEFINED = -1 };

struct DBSCANPoint {
    cv::Point data;
    int label = static_cast<int>(PointLabel::UNDEFINED);
};

double distance(const cv::Point& p1, const cv::Point& p2) {
    long dx = p1.x - p2.x;
    long dy = p1.y - p2.y;
    return static_cast<double>(dx * dx + dy * dy);
}

std::vector<DBSCANPoint> createDB(std::vector<cv::Point>& points){
    std::vector<DBSCANPoint> retDB;
    retDB.reserve(points.size());
    for (auto &pt : points){
        DBSCANPoint dbpt;
        dbpt.data = pt;
        dbpt.label = static_cast<int>(PointLabel::UNDEFINED);
        retDB.push_back(dbpt);
    }
    return retDB;
}

bool operator==(const DBSCANPoint& a, const DBSCANPoint& b) {
    return a.data.x == b.data.x && a.data.y == b.data.y;
}

std::vector<DBSCANPoint> remove_point(const std::vector<DBSCANPoint>& set, const DBSCANPoint& pt) {
    std::vector<DBSCANPoint> result;
    result.reserve(set.size());
    for (const auto& setpt : set) {
        if (!(setpt == pt)) {
            result.push_back(setpt);
        }
    }
    return result;
}

std::vector<DBSCANPoint> combine_sets(const std::vector<DBSCANPoint>& set1, const std::vector<DBSCANPoint>& set2) {
    std::vector<DBSCANPoint> result = set1;
    for (const auto& pt : set2) {
        if (std::find(result.begin(), result.end(), pt) == result.end()) {
            result.push_back(pt);
        }
    }
    return result;
}

std::vector<DBSCANPoint> range_query(const std::vector<DBSCANPoint>& DB, const DBSCANPoint& P, double eps) {
    std::vector<DBSCANPoint> neighbors;
    double eps2 = eps * eps;
    for (const auto& candidate : DB) {
        if (distance(candidate.data, P.data) <= eps2) {
            neighbors.push_back(candidate);
        }
    }
    return neighbors;
}

void dbscan(std::vector<DBSCANPoint>& DB, double eps, int minpoints ){
    int cluster_count = 0;

    for (auto &dbpt : DB){
        if (dbpt.label != static_cast<int>(PointLabel::UNDEFINED)){
            continue;
        }

        std::vector<DBSCANPoint> neighbors = range_query(DB, dbpt, eps);

        if (neighbors.size() < (size_t)minpoints){
            dbpt.label = static_cast<int>(PointLabel::NOISE);
            continue;
        }

        cluster_count += 1;
        dbpt.label = cluster_count;

        std::vector<DBSCANPoint> SeedSet = remove_point(neighbors, dbpt);

        for (auto &setpt : SeedSet){
            if (setpt.label == static_cast<int>(PointLabel::NOISE)){
                setpt.label = cluster_count;
            }
            if (setpt.label != static_cast<int>(PointLabel::UNDEFINED)){
                continue;
            }
            setpt.label = cluster_count;

            std::vector<DBSCANPoint> newNeighbors = range_query(DB, setpt, eps);
            if (newNeighbors.size() >= (size_t)minpoints){
                SeedSet = combine_sets(SeedSet, newNeighbors);
            }
        }
    }
}
