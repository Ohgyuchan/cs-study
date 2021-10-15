#include <iostream>
#include "opencv/cv.hpp"

using namespace std;
using namespace cv;

class Lena {
    public:
        void negative(Mat scr, Mat &dst) {
            for (int row = 0; row < scr.rows; row++) { 
                for (int col = 0; col < scr.cols; col++) { 
                    for(int i = 0; i < 3; i++)
                        dst.at<Vec3b>(row, col)[i] = 255 - scr.at<Vec3b>(row, col)[i]; // access RGB
                }
            }
        }
};

int main() {
    Mat lena, colorful, balancing;

    Mat lena_output, colorful_output, balancing_output;

    Lena L1;

    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    colorful_output = colorful;
    balancing_output = balancing;

    while(1) {
        imshow("lena", lena_output);
        // imshow("colorful", colorful_output);
        // imshow("balancing", balancing_output);
        int key = waitKey();

        if(key == 71 || key == 103) {
            cout << key << endl;
        }

        else if(key == 78 || key == 110) {
            L1.negative(lena, lena_output);
        }

        else if(key == 27) {
            break;
        }
    }

    return 0;
}