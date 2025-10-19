#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <video-file>" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    cv::VideoCapture cap;

    // ERROR HANDLING: opening of file
    if (!cap.open(filename)) {
        std::cerr << "❌ Error: Could not open video file: " << filename << std::endl;
        return -1;
    }

    //FRAME CODE
    cv::Mat frame;
    double fps = cap.get(cv::CAP_PROP_FPS);
    int delay = 1000 / fps;

    while (true) {
        cap >> frame; // Read next frame
        if (frame.empty()) {
            std::cout << "End." << std::endl;
            break;
        }

        cv::imshow("Video Playback Window", frame);
        char key = (char)cv::waitKey(delay/2);
        if (key == 27 || key == 'q') break; // press ESC or press q to quit
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
