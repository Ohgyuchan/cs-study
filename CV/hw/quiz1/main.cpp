#include "opencv/cv.hpp"

using namespace cv;
using namespace std;

int main() {
    Mat milky, milky_filtered;
    Mat milky_laplacian, milky_abs;

    milky = imread("milky.png");

    Laplacian(milky, milky_laplacian, CV_16S);
	convertScaleAbs(milky_laplacian, milky_abs);
	milky_filtered = milky_abs + milky;

    imshow("milky", milky);
	imshow("milky_filtered", milky_filtered);

    waitKey(0);

    return 0;
}