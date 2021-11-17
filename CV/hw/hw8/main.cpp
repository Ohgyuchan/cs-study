#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("background.mp4");
    int count = 2;
    Mat background, image, gray, result;
    
    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        int frames =  cap.get(CAP_PROP_POS_FRAMES);
        int fps = cap.get(CAP_PROP_FPS);
        
        if(!cap.read(image)) break;

        cvtColor(image, image, COLOR_BGR2GRAY);
        
        add(image / count, background*(count - 1) / count, background);

        if(frames == 10) break;

        waitKey(1000/fps);
    }

    cap.set(CAP_PROP_POS_FRAMES, 0);

    while(1) {
        int fps = cap.get(CAP_PROP_FPS);
        if(cap.grab() == 0) break;

        cap.retrieve(image);
        cvtColor(image, gray, CV_BGR2GRAY);

        absdiff(background, gray, result);
        threshold(result, result, 20, 255, CV_THRESH_BINARY);
        
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;
        findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        imshow("Result(x, y)", result);


        waitKey(1000/fps);
    }

    return 0;
}