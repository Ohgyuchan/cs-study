#include <iostream>
#include <stdio.h>
#include <string>
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

Mat getHist(Mat src) {
		Mat hist;
        
        // Set the number of bins to 8
        int histSize = 8;
        float range[] = { 0, 256 };
        const float* histRange = { range };
        int channels[] = {0};
        
        // Compute histogram
        calcHist(&src, 1, channels, Mat(), hist, 1, &histSize, &histRange);

		return hist;
	}

int main() {
    float range[] = { 0, 256 };
    const float* histRange = { range };
    Mat moon,  moon_hist_equalized_image;
    Mat h1, h2;
    Mat input_hist, output_hist;

    moon = imread("moon.png", 0);

    if (!moon.data)
        exit(1); //Check image

    equalizeHist(moon, moon_hist_equalized_image); //histogram equlization
    
    // Draw each histogram of the input and the result image
    h1 = drawHistogram(moon);
    h2 = drawHistogram(moon_hist_equalized_image);

    // Display each histogram of the input and the result image
    imshow("h1", h1);
    imshow("h2", h2);

    input_hist = getHist(moon);
    output_hist = getHist(moon_hist_equalized_image);

    float input_hist_sum = 0;
    float output_hist_sum = 0;

    for (int i = 0; i < 8; i++) {
        input_hist_sum += input_hist.at<float>(i);
        output_hist_sum += output_hist.at<float>(i);
    }

    //  Write all values on the input image(moon)
    for (int i = 0; i < 8; i++) {
        string result = "bin ";
        result += to_string(i+1);
        result += " = ";
        // Compute the value of each component of a normalized histogram of the input image
        result += to_string(input_hist.at<float>(i) / input_hist_sum);
        putText(moon, result, Point(10, 20 * (i + 1)), 0, 0.5, Scalar(255, 255, 255), 1, 8);
    }

    // Write all values on the input image(moon_hist_equalized_image)
    for (int i = 0; i < 8; i++) {
        string result = "bin ";
        result += to_string(i+1);
        result += " = ";
        result += to_string(output_hist.at<float>(i) / output_hist_sum);
        putText(moon_hist_equalized_image, result, Point(10, 20 * (i + 1)), 0, 0.5, Scalar(255, 255, 255), 1, 8);
    }
	
    imshow("before", moon);
    imshow("after", moon_hist_equalized_image);
	
    waitKey(0);

	return 0;
}