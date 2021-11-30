#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void morphOps(Mat &thresh) {
	Mat element = getStructuringElement(MORPH_CROSS, Size(22,22));
	Mat delement = getStructuringElement(MORPH_CROSS, Size(31,31));

	// morphologyEx(thresh, thresh, MORPH_CLOSE, element);
    // morphologyEx(thresh, thresh, MORPH_OPEN, element);
    erode(thresh,thresh,element);
    erode(thresh,thresh,element);

	dilate(thresh,thresh,delement);
	dilate(thresh,thresh,delement);
}

void equalizeHistogram(Mat scr, Mat &dst) {
    Mat channels[3];
    cvtColor(scr, dst, CV_BGR2YUV);
    split(dst,channels); 
    equalizeHist(channels[0], channels[0]); 
    merge(channels, 3, dst);
    cvtColor(dst, dst, CV_YUV2BGR); 
}

int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2();
    Mat frame, foregroundMask, backgroundImg, foregroundImg, HSV;
    VideoCapture cap("Faces.mp4");

    while (true) {
        cap >> frame;
        
        if (foregroundMask.empty())
            foregroundMask.create(frame.size(), frame.type());
        
        bg_model->apply(frame, foregroundMask);
        threshold(foregroundMask, foregroundMask, 20, 255, THRESH_BINARY);
        morphOps(foregroundMask);
        medianBlur(foregroundMask, foregroundMask, 55);
        
        
        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg, foregroundMask);
        // backgroundImg: The output background frame.
        bg_model->getBackgroundImage(backgroundImg);

        imshow("foreground frame", foregroundImg);
        imshow("foreground mask", foregroundMask);
        
        if (!backgroundImg.empty()) {
            // imshow("mean background frame", backgroundImg);
        }

        waitKey(1);
        if (cap.get(CAP_PROP_POS_FRAMES) == 300)
            cap.set(CAP_PROP_POS_FRAMES, 1);
    }
}