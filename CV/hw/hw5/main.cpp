/*
References
Color Image Histogram https://newbedev.com/histogram-equalization-not-working-on-color-image-opencv
*/

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

        void gamma(Mat scr, Mat &dst) {
            double gamma = 2.5;
            double g_min, g_max;
            minMaxLoc(scr, &g_min, &g_max);
            double gamma_c = 255 / pow(g_max, gamma);
            
            // Normalize pixel values from 0 to 1.0
            scr.convertTo(scr, CV_32F);
            
            pow(scr, gamma, dst);
            dst = gamma_c * dst;
            
            dst.convertTo(dst, CV_8UC1);
        }

        void equalizeHistogram(Mat scr, Mat &dst) {
            Mat channels[3];
            // Vector<Mat> channels
            cvtColor(scr, dst, CV_BGR2YCrCb); 
            split(dst,channels); 
            equalizeHist(channels[1], channels[1]); 
            merge(channels, 3, dst);
            // merge(channels, dst);
            cvtColor(dst, dst, CV_YCrCb2BGR); 
        }
};

int main() {
    Mat lena, colorful, balancing;

    Mat lena_output, colorful_output, balancing_output;

    Lena L1;

    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    lena_output = lena.clone();
    colorful_output = colorful.clone();
    balancing_output = balancing.clone();

    while(1) {
        // imshow("lena", lena_output);
        imshow("colorful", colorful_output);
        // imshow("balancing", balancing_output);
        int key = waitKey();

        if(key == 103) { // input 'g'
            L1.gamma(lena_output, lena_output);
        }

        else if(key == 104) { // input 'h'
            L1.equalizeHistogram(lena_output, lena_output);
        }

        else if(key == 110) { // input 'n'
            L1.negative(lena_output, lena_output);
        }

        else if(key == 99) { // input 'c'
            cout << key << endl;
        }

        else if(key == 115) { // input 's'
            cout << key << endl;
        }

        else if(key == 114) {
            // Clone to reset (Deep copy)
            lena_output = lena.clone();
            colorful_output = colorful.clone();
            balancing_output = balancing.clone();
        }

        else if(key == 27) {
            break;
        }
    }

    return 0;
}