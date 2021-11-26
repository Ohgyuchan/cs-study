/*
References:
https://docs.opencv.org/3.4/d1/dc5/tutorial_background_subtraction.html
*/
#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    Ptr<BackgroundSubtractor> pBackSub;
    
    pBackSub = createBackgroundSubtractorMOG2	(10, 16, false);
    
    VideoCapture capture("Quiz2 Video.mp4");
    
    Mat frame, fgMask;
    
    while (true) {
        capture >> frame;
        if (frame.empty())
            break;
        //update the background model
        pBackSub->apply(frame, fgMask);

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(fgMask, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int count_people = 0;
        vector<Rect> boundRect_people(contours.size());
        for (int i = 0; i < contours.size(); i++) {
            
            if(contourArea(Mat(contours[i])) > 2000) {
                boundRect_people[i] = boundingRect(Mat(contours[i]));

                count_people++;
            }
        }

        for (int i = 0; i < contours.size(); i++) {
            //draw rectangles on the contours
                rectangle(frame, boundRect_people[i].tl(), boundRect_people[i].br(), Scalar(255, 255, 255), 2, 8, 0);
            putText(frame, format("how many people: %d", count_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        if(contours.size() == 0) {
            putText(frame, format("how many people: %d", count_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        imshow("Frame", frame);
        
        int keyboard = waitKey(30);
        if (keyboard == 'q' || keyboard == 27)
            break;
    }
    return 0;
}