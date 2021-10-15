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
        // imshow("colorful", colorful_output);
        // imshow("balancing", balancing_output);
        int key = waitKey();

        if(key == 78 || key == 110) {
            for (int row = 0; row < lena.rows; row++) { 
                for (int col = 0; col < lena.cols; col++) { 
                    for(int i = 0; i < 3; i++)
                        lena_output.at<Vec3b>(row, col)[i] = 255 - lena.at<Vec3b>(row, col)[i]; 
                }
            }
            // imshow("lena", lena_output);
        }

        if(key == 27) {
            break;
        }
    }

    return 0;
}