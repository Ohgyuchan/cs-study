#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;



int main() {
    Mat gray_img;
    Mat negative_img;
    
    gray_img = imread("lena.png", 0);

    //negative image
    negative_img = gray_img.clone();
    for (int i = 0; i < gray_img.rows; i++) {
        for (int j = 0; j < gray_img.cols; j++) {
            negative_img.at<uchar>(i, j) = 255 - gray_img.at<uchar>(i, j);
        }
    }

    //log image
    Mat float_img, log_img;
    double c = 1.5f;
    gray_img.convertTo(float_img, CV_32F);
    float_img = abs(float_img) + 1;
    log(float_img, float_img);
    normalize(float_img, float_img, 0, 255, NORM_MINMAX);
    convertScaleAbs(float_img, log_img, c);
    
    //gamma image
    Mat gamma_img;
    MatIterator_<uchar> iterator, end;
    
    float gamma = 0.5;
    unsigned char pixel[256];
    
    for (int i = 0; i < 256; i++) {
        pixel[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
    }
    gamma_img = gray_img.clone();
    
    for (iterator = gamma_img.begin<uchar>(), end = gamma_img.end<uchar>(); iterator != end; iterator++) {
        *iterator = pixel[(*iterator)];
    }

    imshow("Input image", gray_img);
    imshow("negative image", negative_img);
    imshow("log image", log_img);
    imshow("gamma image", gamma_img);

    waitKey(0);
    return 0;
}