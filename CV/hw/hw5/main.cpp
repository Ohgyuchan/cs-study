#include <iostream>
#include "opencv/cv.hpp"

using namespace std;
using namespace cv;

int main() {
    Mat lena, colorful, balancing;

    Mat lena_output, colorful_output, balancing_output;

    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    lena_output = lena;
    colorful_output = colorful;
    balancing_output = balancing;



    while(1) {
        imshow("lena", lena_output);
        imshow("colorful", colorful_output);
        imshow("balancing", balancing_output);

        if(waitKey() == 27) {
            break;
        }
    }

    return 0;
}