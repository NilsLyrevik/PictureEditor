#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <video_file.mov>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    cv::VideoCapture cap(filename);

    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open video file: " << filename << std::endl;
        return 1;
    }

    // Basic video information
    double fps = cap.get(cv::CAP_PROP_FPS);
    double frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);
    double width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    double duration = frame_count / fps;

    std::cout << "File: " << filename << std::endl;
    std::cout << "Resolution: " << width << " x " << height << std::endl;
    std::cout << "FPS: " << fps << std::endl;
    std::cout << "Total frames: " << frame_count << std::endl;
    std::cout << "Duration: " << duration << " seconds" << std::endl;

    cap.release();
    return 0;
}
