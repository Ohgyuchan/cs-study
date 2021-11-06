#include <iostream>
#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

int main() {
    Mat finger_print, adaptive_1, adaptive;

    finger_print = imread("finger_print.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    
    // OTSU Algorithm
    threshold(finger_print, finger_print, 0, 255, THRESH_BINARY | THRESH_OTSU);

    adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 5, 10);

    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 5, 10);

    imshow("finger_print", finger_print);
    imshow("adaptive_1", adaptive_1);
    imshow("adaptive", adaptive);

    waitKey(0);

    return 0;
}