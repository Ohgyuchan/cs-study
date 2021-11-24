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
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        if(!cap.read(frame)) break;
        cvtColor(frame, frame, CV_BGR2GRAY);

        add(frame / count, background*(count - 1) / count, background);

        if(cap.get(CAP_PROP_POS_FRAMES) == cap.get(CAP_PROP_FRAME_COUNT)) break;
        
        count++;
    }

    int key = -1;
    int command = 0;
    cap.set(CAP_PROP_POS_FRAMES, 0);
    
    int blockSize = 3;
    int c = 1;

    while (1) {
        if(!cap.read(frame)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }
        
        cvtColor(frame, gray, CV_BGR2GRAY);
        absdiff(gray, background, foregroundMask);
        threshold(foregroundMask, foregroundMask, 10, 255, THRESH_BINARY);
        erode(foregroundMask, foregroundMask, element);
        adaptiveThreshold(foregroundMask, foregroundMask, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, 11);
        
        if(key == -1) {
            imshow("Face", foregroundMask);
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

        if(command == 'c') {
            blockSize += 2;
        }
        if(command == 'C') {
            blockSize -= 2;
        }
        key = waitKey(33);
    }

    return 0;
}