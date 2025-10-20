#include <opencv2/opencv.hpp>
#include <iostream>

cv::VideoCapture loadVideo(const std::string& filename) {
    cv::VideoCapture cap;
    
    // ERROR HANDLING: opening of file
    if (!cap.open(filename)) { // this line tries to open the file located at the filepath, if successful returns true
        std::cerr << "Error: Could not open video file: " << filename << std::endl;
        return cap;
    }
    
    return cap;
}

/*
returns false if it fails anywhere along the way
idea: maybe can be int/char/short to enhance error handling
*/
bool saveVideo(cv::VideoCapture& cap, cv::Mat (*func)(cv::Mat)) {
    //basic info needed for writer
    double fps = cap.get(cv::CAP_PROP_FPS);
    int width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::system("mkdir -p ../output");

    cv::VideoWriter writer("../output/output.mp4",
                           cv::VideoWriter::fourcc('a','v','c','1'),
                           fps,
                           cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Error opening output file" << std::endl;
        return false;
    }


    cap.set(cv::CAP_PROP_POS_FRAMES, 0); // reset to first frame
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        frame = func(frame);
        writer.write(frame);  // write to output
        if (cv::waitKey(1) == 27) break;  // ESC to exit early
    }

    writer.release();
    return true;
}
