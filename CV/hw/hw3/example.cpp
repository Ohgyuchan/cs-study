#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

int main() {
	Mat image, AvgImg, GaussianImg;
	image = imread("lena.png");

	// Blurs an image using the normalized box filter
	// image: input image, AvgImg: output image, Size(7, 7): blurring kernel(filter) size
	blur(image, AvgImg, Size(7, 7));

	// Blurs an image using a Gaussian filter
	// image: input image, GaussianImg: output image, Size(7, 7): Gaussian kernel(filter) size
	// 1.5: Gaussian kernel standard deviation in X direction (중심 가중치)
	GaussianBlur(image, GaussianImg, Size(7, 7), 1.5);

	imshow("Input image", image);
	imshow("Average image", AvgImg);
	imshow("Gaussian blurred image", GaussianImg);
	waitKey(0);
	return 0;
}