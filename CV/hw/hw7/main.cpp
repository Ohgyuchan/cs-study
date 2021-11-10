#include <iostream>
#include "opencv/cv.hpp"

int count_pixel[256] = {0, };

using namespace cv;
using namespace std;

float mean(int arr[], int n);
void leastSquare(int arr1[], int arr2[], int n);
Mat drawHistogram(Mat src);



int main() {
    Mat finger_print, adaptive_1, adaptive;
    
    finger_print = imread("finger_print.png");
    cvtColor(finger_print, finger_print, CV_BGR2GRAY);
    adaptive_1 = imread("adaptive_1.jpg");
    cvtColor(adaptive_1, adaptive_1, CV_BGR2GRAY);
    adaptive = imread("adaptive.png");
    cvtColor(adaptive, adaptive, CV_BGR2GRAY);
    
    threshold(finger_print, finger_print, 159, 255, THRESH_BINARY);
    imshow("finger_print", finger_print);
    
    adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 49, 11);
    imshow("adaptive_1", adaptive_1);

    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 15);
    imshow("adaptive", adaptive);
    
    waitKey(0);
    
    return 0;
}

Mat drawHistogram(Mat src) {
    Mat hist, histImage;
    // establish the number of bins
    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    int channels[] = {0};

    // Set the number of bins to 16
    histSize = 256;
    hist_w = 1024;
    hist_h = 512;
    bin_w = cvRound((double)hist_w / histSize);
    
    //draw the histogram
    histImage = Mat(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    
    // compute the histograms
    // &src: input image, 1: #of src image, 0: #of channels numerated from 0 ~ channels()-1, Mat(): optional mask
    // hist: output histogram, 1: histogram dimension, &histSize: array of histogram size, &histRange: array of histogram’s boundaries
    calcHist(&src, 1, channels, Mat(), hist, 1, &histSize, &histRange);
    
    // Fit the histogram to [0, histImage.rows]
    // hist: input Mat, hist: output Mat, 0: lower range boundary of range normalization, histImage.rows: upper range boundary
    // NORM_MINMAX: normalization type, -1: when negative, the ouput array has the same type as src, Mat(): optional mask
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (i = 0; i < histSize; i++) {
        rectangle(histImage, Point(bin_w * i, hist_h), Point(bin_w * i+hist_w/histSize, hist_h - cvRound(hist.at<float>(i))), Scalar(0, 0, 0), -1);
        if(i % 10 == 0) rectangle(histImage, Point(hist_w * i / histSize, hist_h - 10), Point(0,hist_h), Scalar(0, 0, 255));
        if(i % 10 == 0) putText(histImage, to_string(i), Point(hist_w * i / histSize, 30), 0, 0.3, Scalar(0, 0, 0), 1, 7);
        cout << i << ": " << hist.at<float>(i) << endl;
    }

    return histImage;
}

float mean(int arr[], int n) { 
    float sum = 0, mean = 0; 
    // sum of arr 
    for (int i = 0; i < n; i++) { 
        sum += arr[i]; 
    } 
    mean = sum / n; //printf("sum : %lf, mean : %lf\n", sum, mean); 
    return mean; 
}

void leastSquare(int arr1[], int arr2[], int n) { 
    // Calculate mean of arr1, arr2
    float x_bar = mean(arr1, n);
    float y_bar = mean(arr2, n);
    
    // y = ax + b
    float a, b; 
    float sum1 = 0, sum2 = 0; 
    
    // Calculate sum1 , sum2 
    for (int i = 0; i < n; i++) { 
        sum1 += (arr1[i] - x_bar) * (arr2[i] - y_bar); sum2 += pow((arr1[i] - x_bar), 2); 
    } 
    //printf("sum1 : %lf, sum2 : %lf\n", sum1, sum2);
    // Calculate a 
    a = sum1 / sum2;
    // Calculate b 
    b = y_bar - a * x_bar; 
    printf("y = %lfx + %lf\n", a, b);
}