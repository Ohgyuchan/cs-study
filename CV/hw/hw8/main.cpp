#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("background.mp4");
    int count = 2;
    Mat background, frame, current_frame_as_gray, result, final_result;
    
    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        int frames =  cap.get(CAP_PROP_POS_FRAMES);
        int fps = cap.get(CAP_PROP_FPS);
        
        if(!cap.read(frame)) break;

        cvtColor(frame, frame, COLOR_BGR2GRAY);
        
        add(frame / count, background*(count - 1) / count, background);

        if(frames == 10) break;

        waitKey(1000/fps);
    }

    cap.set(CAP_PROP_POS_FRAMES, 0);

    while(1) {
        int fps = cap.get(CAP_PROP_FPS);
        if(cap.grab() == 0) break;

        cap.retrieve(frame);
        cvtColor(frame, current_frame_as_gray, CV_BGR2GRAY);

        absdiff(current_frame_as_gray, background, result);
        final_result = result.clone();
        medianBlur(final_result, final_result, 11);
        threshold(final_result, final_result, 20, 255, CV_THRESH_BINARY);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(final_result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int count_400px = 0;
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++)
            if(contourArea(Mat(contours[i])) >= 400) {
                boundRect[i] = boundingRect(Mat(contours[i]));
                count_400px++;
            }
            
        //draw rectangles on the contours
        for (int i = 0; i < contours.size(); i++) {
            rectangle(final_result, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
            putText(final_result, format("contour count: %d", count_400px), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(128), 4);
        }

        imshow("Background", background);
        imshow("Result(x, y)", result);
        imshow("final_result", final_result);

        waitKey(1000/fps);
    }

    return 0;
}