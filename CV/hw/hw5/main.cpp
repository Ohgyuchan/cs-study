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
            // vector<Mat> channels;
            cvtColor(scr, dst, CV_BGR2YUV);
            // cvtColor(scr, dst, CV_BGR2YCrCb);
            split(dst,channels); 
            equalizeHist(channels[0], channels[0]); 
            merge(channels, 3, dst);
            // merge(channels, dst);
            cvtColor(dst, dst, CV_YUV2BGR); 
            // cvtColor(dst, dst, CV_YCrCb2BGR);
        }
};

class Colorful {
    public:
        void colorSclicing(Mat scr, Mat &dst) {
            Mat HSV;

            vector<Mat> mo(3);
            
            int rows = scr.rows;
            int cols = scr.cols;
            
            uchar* h;
            uchar* s;
            uchar* v;
            
            cvtColor(scr, HSV, COLOR_BGR2HSV);
            split(HSV, mo);
            
            // masking out except orange
            for(int i = 0; i < rows; i++) {
                h = mo[0].ptr<uchar>(i);
                s = mo[1].ptr<uchar>(i);
                for(int j = 0; j < cols; j++) {
                    if(h[j] > 9 && h[j] < 23)
                        s[j] = s[j];
                    
                    else
                        s[j] = 0;
                }
            }
            
            merge(mo, dst);

            cvtColor(dst, dst, COLOR_HSV2BGR);
        }

        void colorConversion(Mat scr, Mat &dst) {
            Mat HSV;

            vector<Mat> cc(3);
            
            int rows = scr.rows;
            int cols = scr.cols;
            
            uchar* h;
            uchar* s;
            uchar* v;
            
            cvtColor(scr, HSV, COLOR_BGR2HSV);
            split(HSV, cc);

            // changing all colors
            for(int i = 0; i < rows; i++) {
                h = cc[0].ptr<uchar>(i);
                s = cc[1].ptr<uchar>(i);
                for(int j = 0; j < cols; j++) {
                    if(h[j] + 50 > 129)
                    h[j] = h[j] - 129;
                    
                    else h[j] += 50;
                }
            }

            merge(cc, dst);

            cvtColor(dst, dst, COLOR_HSV2BGR);
        }
};

class Balancing {
    public:
        void averageFiltering(Mat scr, Mat &dst) {
            blur(scr, dst, Size(9, 9));
        }
        
        void whiteBalacing(Mat dst) {
            Mat bgr_channels[3];
            
            split(dst, bgr_channels);
            
            double avg;
            int sum,temp,i, j, c;
            
            for (c = 0; c < dst.channels(); c++) {
                sum = 0;
                avg = 0.0f;
                for (i = 0; i < dst.rows; i++) {
                    for (j = 0; j < dst.cols; j++) {
                        sum += bgr_channels[c].at<uchar>(i, j);
                    }
                }
                
                avg = sum / (dst.rows * dst.cols);
                
                for (i = 0; i < dst.rows; i++) {
                    for (j = 0; j < dst.cols; j++) {
                        temp = (128 / avg) * bgr_channels[c].at<uchar>(i, j);
                        
                        if (temp>255)
                            bgr_channels[c].at<uchar>(i, j) = 255;
                        
                        else
                            bgr_channels[c].at<uchar>(i, j) = temp;
                    }
                }
            }

            merge(bgr_channels, 3, dst);
        }
};

int main() {
    Mat lena, colorful, balancing;

    Mat lena_output, colorful_output, balancing_output;

    Lena L1;
    Colorful C1;
    Balancing B1;

    lena = imread("lena.png");
    colorful = imread("colorful.jpg");
    balancing = imread("balancing.jpg");

    lena_output = lena.clone();
    colorful_output = colorful.clone();
    balancing_output = balancing.clone();

    while(1) {
        // imshow("lena", lena_output);
        // imshow("colorful", colorful_output);
        imshow("balancing", balancing_output);
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
            C1.colorConversion(colorful_output, colorful_output);
        }

        else if(key == 115) { // input 's'
            C1.colorSclicing(colorful_output, colorful_output);
        }

        else if(key == 97) { // input 'a'
            B1.averageFiltering(balancing_output, balancing_output);
        }

        else if(key == 119) { // input 'w'
            B1.whiteBalacing(balancing_output);
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