#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("background.mp4");
    int count = 2;
    Mat background, image, gray, result, foregroundMask,foregroundImg;
    
    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        int frames =  cap.get(CAP_PROP_POS_FRAMES);
        int fps = cap.get(CAP_PROP_FPS);
        cout << "frames: " << frames << endl;
        
        if(!cap.read(image)) break;

        cvtColor(image, image, COLOR_BGR2GRAY);
        
        add(image / count, background*(count - 1) / count, background);

        if(frames == 10) break;

        waitKey(1000/fps);
    }

    cap.set(CAP_PROP_POS_FRAMES, 0);

    while(1) {
        if(cap.grab() == 0) break;
        waitKey(0);
        cap.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);

        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 20, 255, CV_THRESH_BINARY);
        foregroundMask.copyTo(foregroundImg);
        gray.copyTo(foregroundImg, foregroundMask);

    }

    return 0;
}