#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat frame, gray, foregroundMask, background;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
    VideoCapture cap;
    
    if (cap.open("Faces.mp4") == 0) {
        cout << "no such file!" << endl;    
        waitKey(0);
    }

    int count = 2;
    cap >> background;

    // set background as the average of the first 10 frames.
    while(1) {
        if(!cap.read(frame)) break;
        
        add(frame / count, background*(count - 1) / count, background);

        if(cap.get(CAP_PROP_POS_FRAMES) == cap.get(CAP_PROP_FRAME_COUNT)) break;
        
        count++;
    }

    int key = -1;
    int command = 0;
    cap.set(CAP_PROP_POS_FRAMES, 0);

    while (1) {
        if(!cap.read(frame)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }
        
        cvtColor(frame, gray, CV_BGR2GRAY);
        absdiff(background, gray, foregroundMask);
        threshold(foregroundMask, foregroundMask, 30, 255, CV_THRESH_BINARY);
        erode(foregroundMask, foregroundMask, element);
        adaptiveThreshold(foregroundMask, foregroundMask, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 51, 15);
        
        if(key == -1) {
            imshow("Face", background);
        }
        if(key != -1) {
            if(command == key)
                command = 0;
            else 
                command = key;
        }
        if(command == 98) {
            imshow("Face", foregroundMask);
        }
        key = waitKey(33);
    }

    return 0;
}