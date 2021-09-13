#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat gray_image, color_image;
    
    // 0 on the 2nd parameter means read img in grayscale
    gray_image = imread("lena.png", 0);
    
    // blank 2nd parameter means 1, which means read img in colors
    color_image = imread("lena.png");

    imshow("gray image", gray_image);
    imshow("color image", color_image);

    waitKey(0);
    return 0;
}