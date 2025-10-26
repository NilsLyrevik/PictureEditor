/*
Pipeline: 
    1. Convert into grayscale
    2. Apply a background subtractor
    --> MOG2 | KNN | simple frame differencing
    3. Threshold the motion mask
    4.Apply morphological operations (Dilate -> Erode) to clean up
    5. Find contours (little bit confused as to what to do with this later...)
*/

#include <opencv2/opencv.hpp>
#include <iostream>

/*
function does nothing. literally
*/
cv::Mat RemoveBackground(cv::Mat frame){
    return frame; 
}