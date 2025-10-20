#ifndef LOADWRITEVIDEO_HPP
#define LOADWRITEVIDEO_HPP

#include <opencv2/opencv.hpp>
#include <string>

/**
 * @brief Loads a video file using OpenCV.
 * 
 * @param filename Path to the input video file.
 * @return cv::VideoCapture Object used to read frames from the video.
 *         The caller should check if the capture is opened with cap.isOpened().
 */
cv::VideoCapture loadVideo(const std::string& filename);

/**
 * @brief Saves the frames from an existing VideoCapture to a new video file.
 * 
 * The output file is currently written to "../output/output.mp4".
 * 
 * @param cap The VideoCapture object containing frames to write.
 * @return true if the operation succeeded, false otherwise.
 */
bool saveVideo(cv::VideoCapture& cap, cv::Mat (*func)(cv::Mat));

#endif