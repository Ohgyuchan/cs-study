#include "opencv/cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat frame, gray, foregroundImg, foregroundMask, backgroundImg;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(11, 11));

    VideoCapture cap;
    
    if (cap.open("Faces.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
    }

    int key = -1;
    int command = 0;
    
    while (1) {
        if(!cap.read(frame)) {
            break;
        }

        if (foregroundMask.empty())
            foregroundMask.create(frame.size(), frame.type());
        
        bg_model->apply(frame, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 81, 11);
        threshold(foregroundMask, foregroundMask, 20, 255, THRESH_BINARY);
        erode(foregroundMask, foregroundMask, element);
        morphologyEx(foregroundMask, foregroundMask, MORPH_OPEN, element);

        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg, foregroundMask);
        // backgroundImg: The output background image.
        bg_model->getBackgroundImage(backgroundImg);
    }

    while (1) {
        if(!cap.read(frame)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }

        if (foregroundMask.empty())
            foregroundMask.create(frame.size(), frame.type());
        
        bg_model->apply(frame, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 81, 11);
        threshold(foregroundMask, foregroundMask, 20, 255, THRESH_BINARY);
        erode(foregroundMask, foregroundMask, element);
        morphologyEx(foregroundMask, foregroundMask, MORPH_OPEN, element);

        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg, foregroundMask);
        // backgroundImg: The output background image.
        bg_model->getBackgroundImage(backgroundImg);
        
        if(key == -1) {
            imshow("Face", frame);
        }
        if(key != -1) {
            if(command == key)
                command = 0;
            else 
                command = key;
        }
        if(command == 'b') {
            // foreground = Mat(frame.size(), CV_8UC3, Scalar(255, 255, 255));
            // make_foreground(frame, foreground);
            while(1) {
                imshow("Face", foregroundImg);
                if(waitKey(0) == 'b') {
                    break;
                }
            }
            continue;
        }
        key = waitKey(33);
    }

    return 0;
}