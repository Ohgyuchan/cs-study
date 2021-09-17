#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat gray_img;
    Mat negative_img;
    
    gray_img = imread("Lena.png", 0);

    // negative image
    // s = L-1- r

    negative_img = 255 - gray_img;

    //log image
    // s=c log(1+r) , c: constant, r: input, s: outp
    Mat log_input_img, log_img;

    log_input_img = gray_img;
    
    double log_c = 1.5;
    log_input_img.convertTo(log_input_img, CV_32F);
    log_input_img = abs(log_input_img) + 1;
    log(log_input_img, log_img);
    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    log_img = log_c * log_img;
    log_img.convertTo(log_img, CV_8UC1);

    
    // gamma image
    // s = cr^gamma c:constant, s:output, r:input
    Mat gamma_input_img, gamma_img;
    
    gamma_input_img = gray_img;
    
    double gamma = 2.5;
    double gamma_c = 1.0;
    gamma_input_img.convertTo(gamma_input_img, CV_32F);
    pow(gamma_input_img, gamma, gamma_img);
    gamma_img = gamma_c * gamma_img;
    normalize(gamma_img, gamma_img, 0, 1.0, NORM_MINMAX, CV_32F);
    gamma_img.convertTo(gamma_img, CV_8UC1);

    imshow("gray image", gray_img);
    imshow("negative image", negative_img);
    imshow("log image", log_img);
    imshow("gamma image", gamma_img);

    waitKey(0);
    return 0;
}

/* negative */
// negative_img = gray_img.clone();
// for (int i = 0; i < gray_img.rows; i++)
//     for (int j = 0; j < gray_img.cols; j++)
//         negative_img.at<uchar>(i, j) = 255 - gray_img.at<uchar>(i, j);

/* log */
// Mat input_img2, log_img2;
// gray_img.convertTo(input_img2, CV_32F);
// input_img2 = abs(input_img2) + 1;
// log(input_img2, input_img2);
// normalize(input_img2, input_img2, 0, 255, NORM_MINMAX);
// convertScaleAbs(input_img2, log_img2, c);

/* gamma */
// Mat gamma_img2;
// MatIterator_<uchar> iterator, end;
// unsigned char pixel[256];

// for (int i = 0; i < 256; i++) {
//     pixel[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
// }
// gamma_img2 = gray_img.clone();

// end = gamma_img2.end<uchar>();
// for (iterator = gamma_img2.begin<uchar>(); iterator != end; iterator++)
//     *iterator = pixel[(*iterator)];