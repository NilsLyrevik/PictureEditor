#include <opencv2/opencv.hpp>
#include <iostream>
#include "src/loadwritevideo.hpp"
#include "src/functions/dummy.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <video-file>" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    cv::VideoCapture cap = loadVideo(filename);
    // FIX so that user can choose which fucntion to use!
    if(!saveVideo(cap,dummy)){
        std::cout << "Failed to save video" << std::endl;
    }
    cv::destroyAllWindows();
    return 0;
}