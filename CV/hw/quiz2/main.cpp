#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("Quiz2 Video.mp4");
    Mat background, frame, current_frame_as_gray, result, final_result;
    int count = 1;
    
    cap >> frame;
    
    // while(1) {
    //     if(cap.grab() == 0) break;
        
    //     cap.retrieve(background);
        
    //     if(count == cap.get(CV_CAP_PROP_FRAME_COUNT)) break;
        
    //     count++;
    // }

    // imshow("123", background);
    cvtColor(frame, frame, COLOR_BGR2GRAY);
    GaussianBlur(frame, frame, Size(7, 7), 0);
    imshow("1", frame);

    waitKey(0);
    
    cvtColor(background, background, COLOR_BGR2GRAY);

    cap.set(CAP_PROP_POS_FRAMES, 0);


    Mat background_img = background.clone();
    Mat background_temp;
    double previous_frame = 0;

    while(1) {
        if(cap.grab() == 0) break;

        cap.retrieve(frame);
        double frames = cap.get(CAP_PROP_POS_FRAMES);
        
        cvtColor(frame, current_frame_as_gray, CV_BGR2GRAY);
        
        if(frames != 1 && ((frames - previous_frame) == 1)) {
            background = background_temp.clone();
        }

        absdiff(current_frame_as_gray, background, result);
        threshold(result, result, 20, 255, CV_THRESH_BINARY);
        
        final_result = result.clone();
        Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
        medianBlur(final_result, final_result, 7);
        dilate(final_result, final_result, element);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(final_result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int count_people = 0;
        vector<Rect> boundRect_people(contours.size());
        vector<Rect> boundRect_white_people(contours.size());
        for (int i = 0; i < contours.size(); i++) {
            
            if(contourArea(Mat(contours[i])) > 2500) {
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
            putText(frame, format("boundRect_people count bigger than 400px: %d", count_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        int fps = cap.get(CAP_PROP_FPS);
        
        imshow("final_result", background);

        waitKey(33);
        previous_frame = frames;
    }

    return 0;
}