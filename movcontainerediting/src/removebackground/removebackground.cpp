/*
Pipeline: 
    1. Convert into grayscale // this step probably wount be necessary this is since OpenCV already has a background subtracor.
    2. Apply a background subtractor
    --> MOG2 | KNN | simple frame differencing
    3. Threshold the motion mask
    4.Apply morphological operations (Dilate -> Erode) to clean up
    5. Find contours (little bit confused as to what to do with this later...)
*/
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../functions/grayscale.hpp"

bool RemoveBackground(cv::VideoCapture& cap, bool mog2) {
    double fps = cap.get(cv::CAP_PROP_FPS);
    int width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::system("mkdir -p ../output");

    // Writer will save a video with same resolution as the input
    cv::VideoWriter writer(
        "../output/output.mp4",
        cv::VideoWriter::fourcc('a', 'v', 'c', '1'),
        fps,
        cv::Size(width, height)
    );

    if (!writer.isOpened()) {
        std::cerr << "Error: Could not open output file for writing." << std::endl;
        return false;
    }

    cap.set(cv::CAP_PROP_POS_FRAMES, 0);
    cv::Mat frame, fgMask, mask3ch;

    // Background subtractor
    cv::Ptr<cv::BackgroundSubtractor> pBackSub;
    if (mog2){
        pBackSub = cv::createBackgroundSubtractorMOG2();
    }
    else{
        pBackSub = cv::createBackgroundSubtractorKNN();
    }

    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // Compute the foreground mask
        pBackSub->apply(frame, fgMask);

        //remove noise
        /*
        cv::threshold(fgMask, fgMask, 128, 255, cv::THRESH_BINARY);
        cv::morphologyEx(fgMask, fgMask, cv::MORPH_OPEN, cv::Mat());
        cv::morphologyEx(fgMask, fgMask, cv::MORPH_CLOSE, cv::Mat());
        */

        // Convert to 3-channel image before saving
        cv::cvtColor(fgMask, mask3ch, cv::COLOR_GRAY2BGR);

        // Write processed mask to video
        writer.write(mask3ch);
    }

    cap.release();
    writer.release();

    return true;
}
