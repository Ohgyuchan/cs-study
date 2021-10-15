#include <iostream>
#include "opencv/cv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat lena, colorful, balancing;

    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    while(1) {
        imshow("lena", lena);
        imshow("colorful", colorful);
        imshow("balancing", balancing);

        if(waitKey() == 27) {
            break;
        }
    }

    return 0;
}