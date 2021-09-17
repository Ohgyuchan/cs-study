#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat gray_img;
    Mat negative_img;
    
    gray_img = imread("lena.png", 0);

    // negative image
    // s = L-1- r

    negative_img = 255 - gray_img;

    //log image
    // s = c * log(1+r) , c: constant, r: input, s: output

    Mat log_img;
    Mat log_input_img = gray_img.clone();
    double log_c = 1.5;

    log_input_img.convertTo(log_input_img, CV_32F);
    log_input_img = abs(log_input_img) + 1;
    log(log_input_img, log_img);
    normalize(log_img, log_img, 0, 255, NORM_MINMAX);
    log_img = log_c * log_img;
    log_img.convertTo(log_img, CV_8UC1);

    
    // gamma image
    // s = c * r^gamma c:constant, s:output, r:input
    // c = 255 / max_input_pixel_value^gamma
    Mat gamma_img;
    Mat gamma_input_img = gray_img.clone();
    
    double gamma = 0.5;
    double g_min, g_max;
    minMaxLoc(gamma_input_img, &g_min, &g_max);
    double gamma_c = 255 / pow(g_max, gamma);

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
// Mat input_img, log_img;
// gray_img.convertTo(input_img, CV_32F);
// input_img = abs(input_img) + 1;
// log(input_img, input_img);
// normalize(input_img, input_img, 0, 255, NORM_MINMAX);
// convertScaleAbs(input_img, log_img, c);

/* gamma */
// Mat gamma_img;
// MatIterator_<uchar> iterator, end;
// unsigned char pixel[256];

// for (int i = 0; i < 256; i++) {
//     pixel[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f);
// }
// gamma_img = gray_img.clone();

// end = gamma_img.end<uchar>();
// for (iterator = gamma_img.begin<uchar>(); iterator != end; iterator++)
//     *iterator = pixel[(*iterator)];