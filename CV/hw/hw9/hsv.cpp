#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void morphOps(Mat &thresh) {
	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	erode(thresh,thresh,erodeElement);
	erode(thresh,thresh,erodeElement);

	dilate(thresh,thresh,dilateElement);
	dilate(thresh,thresh,dilateElement);
}


int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat frame, foregroundImg, foregroundMask, backgroundImg;
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
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }

        
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
            Mat HSV;
            cvtColor(frame, HSV, COLOR_BGR2HSV);

            if (foregroundMask.empty())
                foregroundMask.create(frame.size(), frame.type());

            bg_model->apply(frame, foregroundMask);
            threshold(foregroundMask, foregroundMask, 20, 255, THRESH_BINARY);
            morphOps(foregroundMask);

            foregroundImg = Scalar::all(0);
            frame.copyTo(foregroundImg, foregroundMask);
            bg_model->getBackgroundImage(backgroundImg);

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