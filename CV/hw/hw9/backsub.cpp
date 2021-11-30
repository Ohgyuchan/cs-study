#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("Faces.mp4");
    int count = 2;
    Mat background, frame, current_frame_as_gray, result, final_result;
    
    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        if(!cap.read(frame)) break;

        cvtColor(frame, frame, CV_BGR2GRAY);
        
        add(frame / count, background*(count - 1) / count, background);

        if(cap.get(CAP_PROP_POS_FRAMES) == 20) break;
        
        count++;
    }

    // reset position of frame
    cap.set(CAP_PROP_POS_FRAMES, 0);

    Mat background_img = background.clone();
    Mat background_temp, previous_frame;

    while(1) {
        if(cap.grab() == 0) break;

        cap.retrieve(frame);
        int frames = cap.get(CAP_PROP_POS_FRAMES);
        
        cvtColor(frame, current_frame_as_gray, CV_BGR2GRAY);

        if(frames != 1 && frames % 20 == 1)
        // if(frames != 1)
            background = background_temp.clone();

        absdiff(current_frame_as_gray, background, result);
        
        if(frames >= 2) {
            add(current_frame_as_gray / count, background_temp * (count - 1) / count, background_temp);
        } else {
            background_temp = current_frame_as_gray.clone();
        }
        
        threshold(result, result, 20, 255, CV_THRESH_BINARY);
        
        final_result = result.clone();
        Mat element = getStructuringElement(MORPH_ELLIPSE, Size(10, 10));
        medianBlur(final_result, final_result, 7);
        morphologyEx(final_result, final_result, MORPH_CLOSE, element);
        // dilate(final_result, final_result, element);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(final_result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int count_400px = 0;
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++) {
            
            if(contourArea(Mat(contours[i])) > 3000) {
                boundRect[i] = boundingRect(Mat(contours[i]));

                count_400px++;
            }
        }

        for (int i = 0; i < contours.size(); i++) {
            //draw rectangles on the contours
                rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
            putText(frame, format("boundRect count bigger than 400px: %d", count_400px), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        if(contours.size() == 0) {
            putText(frame, format("boundRect count bigger than 400px: %d", count_400px), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        int fps = cap.get(CAP_PROP_FPS);
        
        imshow("final_result", frame);
        imshow("Background", background);
        imshow("Result(x, y)", result);

        waitKey(1000/fps);
    }

    return 0;
}