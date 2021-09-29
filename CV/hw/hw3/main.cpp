#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

int main() {
	Mat lena, lena_filtered; 
    Mat moon, moon_filtered;
    Mat saltnpepper, saltnpepper_filtered;

	lena = imread("lena.png");
    moon = imread("moon.png");
    saltnpepper = imread("saltnpepper.png");

    lena_filtered = lena.clone();
    Rect lena_rect(0, 0, lena_filtered.cols/2, lena_filtered.rows);
    Mat lena_rect_roi = lena_filtered(lena_rect);
    
	blur(lena_rect_roi, lena_rect_roi, Size(7, 7));
    
    moon_filtered = moon.clone();
    Rect moon_rect(moon_filtered.cols/2, 0, moon_filtered.cols/2, moon_filtered.rows);
    Mat moon_rect_roi = moon_filtered(moon_rect);
    Mat moon_rect_roi_laplacian, moon_rect_roi_abs;
	
    Laplacian(moon_rect_roi, moon_rect_roi_laplacian, CV_16S);
	convertScaleAbs(moon_rect_roi_laplacian, moon_rect_roi_abs);
	moon_rect_roi = moon_rect_roi + moon_rect_roi_abs;

    medianBlur(saltnpepper, saltnpepper_filtered, 9);

	imshow("lena", lena);
    imshow("lena_filtered", lena_filtered);

    imshow("moon", moon);
	imshow("moon_filtered", moon_filtered);

	imshow("saltnpepper", saltnpepper);
	imshow("saltnpepper_filtered", saltnpepper_filtered);
	
	waitKey(0);

	return 0;
}