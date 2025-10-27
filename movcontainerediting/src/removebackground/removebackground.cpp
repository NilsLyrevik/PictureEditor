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

/*
function does alot. like a little bit to much but whatever
    --> Will probobly have to execute this on a child thread or something. dont wanna rewrite my whole main... holy guacamole
*/
bool RemoveBackground(cv::VideoCapture& cap, bool mog2) {
    double fps = cap.get(cv::CAP_PROP_FPS);
    int width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    std::system("mkdir -p ../../output");

    cv::VideoWriter writer("../../output/output.mp4",
                           cv::VideoWriter::fourcc('a','v','c','1'),
                           fps,
                           cv::Size(width, height));

    cap.set(cv::CAP_PROP_POS_FRAMES, 0);
    cv::Mat frame, fgMask;

    // BACKGROUND SUBTRACTOR STUFF
    cv::Ptr<cv::BackgroundSubtractor> pBackSub;
    if (mog2) {
        pBackSub = cv::createBackgroundSubtractorMOG2();
    } else {
        pBackSub = cv::createBackgroundSubtractorKNN();
    }

    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        // update the background model
        pBackSub->apply(frame, fgMask);

        // get the frame number and write it on the current frame
        cv::rectangle(frame, cv::Point(10, 2), cv::Point(100, 20),
                      cv::Scalar(255, 255, 255), -1);
        std::stringstream ss;
        ss << cap.get(cv::CAP_PROP_POS_FRAMES);
        std::string frameNumberString = ss.str();
        cv::putText(frame, frameNumberString.c_str(), cv::Point(15, 15),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

        // show the current frame and the fg mask
        cv::imshow("Frame", frame);
        cv::imshow("FG Mask", fgMask);

        cv::Mat grayMask, combined;
        cv::cvtColor(fgMask, grayMask, cv::COLOR_GRAY2BGR); // convert mask to 3-channel
        cv::hconcat(frame, grayMask, combined);              // combine side by side
        writer.write(combined);

        if (cv::waitKey(1) == 27) break; // ESC to exit early
    }

    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return true; // if whole function executes correctly
}
