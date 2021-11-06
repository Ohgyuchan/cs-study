#include <iostream>
#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

int main() {
    Mat finger_print, adaptive_1, adaptive;

    finger_print = imread("finger_print.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    Mat dst;

    for (int j = 0; j < adaptive.rows; j++) {
        for (int i = 0; i < adaptive.cols; i++) {
            if(adaptive.at<uchar>(j, i) == 100) {
                dst.at<uchar>(j, i) = adaptive.at<uchar>(j, i);
            } else {
                dst.at<uchar>(j, i) = adaptive.at<uchar>(j, i) + 100;
            }
        }
    }

    
    // OTSU Algorithm
    // threshold(finger_print, finger_print, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 55, 10);

    // adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 55, 10);

    // imshow("finger_print", finger_print);
    // imshow("adaptive_1", adaptive_1);
    imshow("adaptive", adaptive);
    imshow("dst", dst);

    waitKey(0);

    return 0;
}