#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

Mat drawHistogram(Mat src){
    Mat hist, histImage;
    // establish the number of bins
    int i, hist_w, hist_h, bin_w, histSize;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    int channels[] = {0};

    // Set the number of bins to 16
    histSize = 16;
    hist_w = 512;
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
    }

    return histImage;
}

int main() {
    Mat finger_print, adaptive_1, adaptive;

    finger_print = imread("finger_print.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    Mat finger_hist, adaptive_1_hist, adaptive_hist;
    finger_hist = drawHistogram(finger_print);
    adaptive_1_hist = drawHistogram(adaptive_1);
    adaptive_hist = drawHistogram(adaptive);

    imshow("finger_hist", finger_hist);
    imshow("adaptive_1_hist", adaptive_1_hist);
    imshow("adaptive_hist", adaptive_hist);

    // OTSU Algorithm
    threshold(finger_print, finger_print, 0, 255, THRESH_BINARY | THRESH_OTSU);

    adaptiveThreshold(adaptive_1, adaptive_1, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 7, 10);

    adaptiveThreshold(adaptive, adaptive, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 0);

    imshow("finger_print", finger_print);
    imshow("adaptive_1", adaptive_1);
    imshow("adaptive", adaptive);

    waitKey(0);

    return 0;
}