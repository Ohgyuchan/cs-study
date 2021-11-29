#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("Faces.mp4");
    Mat result, bgModel, fgModel, image, foreground;
    cap >> image;

    //inner rectangle which includes foreground
    Rect rectangle(65, 0, 170, 230);
    
    grabCut(image, result, rectangle, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);
    
    foreground = Mat(image.size(), CV_8UC3, Scalar(255, 255, 255));
    image.copyTo(foreground, result);
    
    imshow("original", image);
    imshow("Result", result);
    imshow("Foreground", foreground);
    
    waitKey(0);
    return 0;
}