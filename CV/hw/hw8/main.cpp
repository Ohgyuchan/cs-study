#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("background.mp4");
    int count = 2;
    Mat background, image, gray, result, foregroundMask,foregroundImg;
    
    cap >> background;

    while(1) {
        if(!cap.read(image)) break;
        add(image / count, background*(count - 1) / count, background);

        imshow("avg", background);
        if(count == 10) break;
        count++;
        waitKey(33);
    }
    
    while(1) {
        if(cap.grab() == 0) break;
        cap.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);

        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 50, 255, CV_THRESH_BINARY);
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);

    }

    return 0;
}