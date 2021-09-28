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

    Rect lena_rect(0, 0, lena.cols/2, lena.rows);
    Mat lena_rect_roi = lena(lena_rect);
    
	blur(lena_rect_roi, lena_filtered, Size(7, 7));

    Rect moon_rect(moon.cols/2, 0, moon.cols/2, moon.rows);
    Mat moon_rect_roi = moon(moon_rect);
    
    Rect moon_rect2(0, 0, moon.cols/2, moon.rows);
    Mat moon_rect_roi2 = moon(moon_rect2);
	
    Laplacian(moon_rect_roi, moon_filtered, CV_16S);
	convertScaleAbs(moon_filtered, moon_filtered);
	moon_filtered = moon_filtered + moon_rect_roi;

    medianBlur(saltnpepper, saltnpepper_filtered, 9);

	// imshow("lena", lena);
    // imshow("lena_filtered", lena_filtered);

    imshow("moon", moon);
	imshow("moon_filtered", moon_filtered);
	imshow("moon_filtered2", moon_rect_roi2);

	// imshow("saltnpepper", saltnpepper);
	// imshow("saltnpepper_filtered", saltnpepper_filtered);
	
	waitKey(0);

	return 0;
}