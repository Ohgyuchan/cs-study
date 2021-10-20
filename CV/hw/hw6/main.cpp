#include "opencv/cv.hpp"

using namespace cv;

int main() {
    Mat lena, sobel, grad_x, grad_y, canny;
    // the different results with color, gray scale.
    lena = imread("lena.png", 0);

    imshow("Lena", lena);

    GaussianBlur(lena, sobel, Size(5,5), BORDER_DEFAULT);
    
    Sobel(sobel, grad_x, CV_16S, 1, 0, 3);
    convertScaleAbs(grad_x, grad_x);

    Sobel(sobel, grad_y, CV_16S, 0, 1, 3);
    convertScaleAbs(grad_y, grad_y);
    
    addWeighted(grad_x, 0.5, grad_y, 0.5, 0, sobel);

    Canny(lena, canny, 190, 200, 3);
    imshow("Canny", canny);

    imshow("Sobel",sobel);

    waitKey(0);
    return 0;
}