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

    // set background as the average of the first 10 frames.
    while(1) {
        if(!cap.read(frame)) break;

        cvtColor(frame, frame, CV_BGR2GRAY);
        
        add(frame / count, background*(count - 1) / count, background);
        
        count++;
    }

    // reset position of frame
    cap.set(CAP_PROP_POS_FRAMES, 0);
    Mat background_temp;

    while(1) {
        if(cap.grab() == 0) break;

        cap.retrieve(frame);
        int frames = cap.get(CAP_PROP_POS_FRAMES);
        
        cvtColor(frame, current_frame_as_gray, CV_BGR2GRAY);
        
        // if(frames != 1 && frames % background_avg_num == 1)
            // background = background_temp.clone();

        absdiff(current_frame_as_gray, background, result);
        
        if(frames >= 2) {
            add(current_frame_as_gray / count, background_temp * (count - 1) / count, background_temp);
        } else {
            background_temp = current_frame_as_gray.clone();
        }
        
        threshold(result, result, 20, 255, CV_THRESH_BINARY);
        morphOps(result);
        medianBlur(result, result, 71);

        foregroundImg = Scalar::all(0);
        frame.copyTo(foregroundImg, result);
        
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;
        findContours(result, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        int cout_people = 0;
        vector<Rect> boundRect(contours.size());
        for (int i = 0; i < contours.size(); i++) {
            
            if(contourArea(Mat(contours[i])) > 3000) {
                boundRect[i] = boundingRect(Mat(contours[i]));

                cout_people++;
            }
        }

        for (int i = 0; i < contours.size(); i++) {
            //draw rectangles on the contours
                rectangle(foregroundImg, boundRect[i].tl(), boundRect[i].br(), Scalar(255, 255, 255), 2, 8, 0);
            putText(foregroundImg, format("how many people: %d", cout_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        if(contours.size() == 0) {
            putText(foregroundImg, format("how many people: %d", cout_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
        }

        int fps = cap.get(CAP_PROP_FPS);
        
        imshow("Frame", frame);
        imshow("Background", background);
        imshow("Result(x, y)", foregroundImg);

        waitKey(33);
    }

    return 0;
}