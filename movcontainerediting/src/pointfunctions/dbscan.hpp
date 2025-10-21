#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <opencv2/opencv.hpp>

enum class PointLabel { NOISE = 0, UNDEFINED = -1 };

struct DBSCANPoint {
    cv::Point data;
    int label = static_cast<int>(PointLabel::UNDEFINED);
};

// Distance squared between two points
inline double distance(const cv::Point& p1, const cv::Point& p2) {
    long dx = p1.x - p2.x;
    long dy = p1.y - p2.y;
    return static_cast<double>(dx * dx + dy * dy);
}

// Convert cv::Point vector into DBSCANPoint vector
inline std::vector<DBSCANPoint> createDB(const std::vector<cv::Point>& points){
    std::vector<DBSCANPoint> retDB;
    retDB.reserve(points.size());
    for (const auto& pt : points){
        DBSCANPoint dbpt;
        dbpt.data = pt;
        dbpt.label = static_cast<int>(PointLabel::UNDEFINED);
        retDB.push_back(dbpt);
    }
    return retDB;
}

// Return indices of neighbors within eps
inline std::vector<size_t> range_query(const std::vector<DBSCANPoint>& DB, size_t idx, double eps) {
    std::vector<size_t> neighbors;
    double eps2 = eps * eps;
    const auto& p = DB[idx].data;
    for (size_t i = 0; i < DB.size(); ++i) {
        if (distance(DB[i].data, p) <= eps2) {
            neighbors.push_back(i);
        }
    }
    return neighbors;
}

// In-place DBSCAN using indices
inline void dbscan(std::vector<DBSCANPoint>& DB, double eps, int minpoints) {
    int cluster_count = 0;

    for (size_t i = 0; i < DB.size(); ++i) {
        if (DB[i].label != static_cast<int>(PointLabel::UNDEFINED)) continue;

        std::vector<size_t> neighbors = range_query(DB, i, eps);
        if (neighbors.size() < static_cast<size_t>(minpoints)) {
            DB[i].label = static_cast<int>(PointLabel::NOISE);
            continue;
        }

        cluster_count++;
        DB[i].label = cluster_count;

        // SeedSet contains indices of neighbors to expand
        std::vector<size_t> seedSet;
        for (size_t idx : neighbors) if (idx != i) seedSet.push_back(idx);

        size_t j = 0;
        while (j < seedSet.size()) {
            size_t current = seedSet[j];

            if (DB[current].label == static_cast<int>(PointLabel::NOISE))
                DB[current].label = cluster_count;

            if (DB[current].label != static_cast<int>(PointLabel::UNDEFINED)) {
                j++;
                continue;
            }

            DB[current].label = cluster_count;

            std::vector<size_t> currentNeighbors = range_query(DB, current, eps);
            if (currentNeighbors.size() >= static_cast<size_t>(minpoints)) {
                for (size_t idx : currentNeighbors) {
                    if (std::find(seedSet.begin(), seedSet.end(), idx) == seedSet.end()) {
                        seedSet.push_back(idx);
                    }
                }
            }
            j++;
        }
    }
}
