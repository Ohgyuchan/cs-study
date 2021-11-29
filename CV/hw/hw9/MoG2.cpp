#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat image, foregroundMask, backgroundImg, foregroundImg;
    VideoCapture cap("Faces.mp4");
    while (true) {
        cap >> image;
        resize(image, image, Size(640, 480));
        
        if (foregroundMask.empty())
            foregroundMask.create(image.size(), image.type());
        
        bg_model->apply(image, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 51, 11);
        threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);
        foregroundImg = Scalar::all(0);
        image.copyTo(foregroundImg, foregroundMask);
        // backgroundImg: The output background image.
        bg_model->getBackgroundImage(backgroundImg);
        imshow("foreground mask", foregroundMask);
        imshow("foreground image", foregroundImg);
        if (!backgroundImg.empty()) {
            imshow("mean background image", backgroundImg);
        }
        waitKey(33);
    }
}