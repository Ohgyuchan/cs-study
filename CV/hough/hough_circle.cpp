#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;

int main(int ac, char** av)
{
	Mat img = imread("circles.png", 0);

	medianBlur(img, img, 5);

	Mat img_houghC;
	img.copyTo(img_houghC);
	
	vector<Vec3f> circles;
	HoughCircles(img_houghC, circles, HOUGH_GRADIENT, 1, 100, 50, 35, 0, 0);
	
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center(c[0], c[1]);
		int radius = c[2];

		circle(img_houghC, center, radius, Scalar(0, 255, 0), 2);
		circle(img_houghC, center, 2, Scalar(0, 0, 255), 3);
	}


	imshow("img_houghC", img_houghC);
	waitKey(0);
	return 0;
}