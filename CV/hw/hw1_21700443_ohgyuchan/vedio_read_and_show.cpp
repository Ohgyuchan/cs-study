#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat frame;
    VideoCapture cap;
    
    // check if file exists. if none program ends
    if (cap.open("background.mp4") == 0) {
        cout << "no such file!" << endl;    
        waitKey(0);
    }
    while (1) {
        cap >> frame;
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        int msec = cap.get(CAP_PROP_POS_MSEC);
        int frames = cap.get(CAP_PROP_POS_FRAMES);
        int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
        if(msec >= 3000) {
            break;
        }
        cout << "frames: " << frames <<"/" << total_frames << endl;
        imshow("video", frame);
        waitKey(1370/72);
    }
}