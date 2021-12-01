#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void morphOps(Mat &thresh) {
    Mat element = getStructuringElement(MORPH_CROSS, Size(27,27));
	Mat delement = getStructuringElement(MORPH_CROSS, Size(8,45));

    erode(thresh,thresh,element);
    erode(thresh,thresh,element);
    
	dilate(thresh,thresh,delement);
}

int main() {
    VideoCapture cap("Faces.mp4");
    int count = 2;
    int background_avg_num = 50;
    Mat background, frame, current_frame_as_gray, result, foregroundImg;
    
    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    Mat background_temp;

    while(1) {
        if(cap.grab() == 0) break;

        cap.retrieve(frame);
        int frames = cap.get(CAP_PROP_POS_FRAMES);
        
        cvtColor(frame, current_frame_as_gray, CV_BGR2GRAY);
        
        // if(frames != 1 && frames % background_avg_num == 1)
        //     background = background_temp.clone();

        absdiff(current_frame_as_gray, background, result);
        
        if(frames % 10 == 0) {
            cvtColor(frame, background, COLOR_BGR2GRAY);
        }
        
        threshold(result, result, 20, 255, CV_THRESH_BINARY);
        morphOps(result);
        medianBlur(result, result, 71);

        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg, result);
        
        imshow("Frame", frame);
        imshow("Background", background);
        imshow("Result(x, y)", foregroundImg);

        waitKey(100);
    }

    return 0;
}