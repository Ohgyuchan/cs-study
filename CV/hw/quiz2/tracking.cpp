#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]){
    VideoCapture cap("Quiz2 Video.mp4");
    
    Mat frame, m_backproj1, m_backproj2, m_backproj3, m_backproj4, m_backproj5, m_backproj6, hsv;
    Mat m_model3d;
    
    Rect m_rc1, m_rc2, m_rc3, m_rc4, m_rc5, m_rc6;
    
    float hrange[] = { 0,180 };
    float vrange[] = { 0,255 };
    float srange[] = { 0,255 };
    const float* ranges[] = { hrange, srange, vrange }; // hue, saturation, brightness
    
    int channels[] = { 0, 1, 2 };
    int hist_sizes[] = { 16, 16, 16 };
    
    if (!cap.isOpened()){
        cout << "can't open video file" << endl;
        return 0;
    }

    cap >> frame;
    
    bool tracking = false;
    
    int count = 1;
    int x = 102, y = 135;
    int w = 100, h = 200;

    /*
    102, 135, 96, 272
    206, 158, 81, 246
    298, 134, 76, 272
    399, 126, 77, 280
    489, 143, 84, 264
    593, 139, 79, 268
    */
    
    while (true){
        cvtColor(frame, hsv, COLOR_BGR2HSV);
        
        if(count == 1)
        {
            Rect rc(102, 135, 96, 272);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc1 = rc;
        }

        if(count == 1) {
            Rect rc(206, 158, 81, 246);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc2 = rc;
        }

        if(count == 1) {
            Rect rc(298, 134, 76, 272);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc3 = rc;
        }

        if(count == 1) {
            Rect rc(399, 126, 77, 280);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc4 = rc;
        }

        if(count == 1) {
            Rect rc(489, 143, 84, 264);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc5 = rc;
        }

        if(count == 1) {
            Rect rc(593, 139, 79, 268);
            Mat mask = Mat::zeros(rc.height, rc.width, CV_8U);
            ellipse(mask, Point(rc.width / 2, rc.height / 2), Size(rc.width / 2, rc.height / 2), 0, 0, 360, 255, CV_FILLED);
            Mat roi(hsv, rc);
            calcHist(&roi, 1, channels, mask, m_model3d, 3, hist_sizes, ranges);
            m_rc6 = rc;
            
            count = 0;
        }
        
        tracking = true;

        cap >> frame;
        if (frame.empty()) break;
        
        // image processing
        if (tracking){
        
            //histogram backprojection
            calcBackProject(&hsv, 1, channels, m_model3d, m_backproj1, ranges);
            // calcBackProject(&hsv, 1, channels, m_model3d, m_backproj2, ranges);
            // calcBackProject(&hsv, 1, channels, m_model3d, m_backproj3, ranges);
            // calcBackProject(&hsv, 1, channels, m_model3d, m_backproj4, ranges);
            // calcBackProject(&hsv, 1, channels, m_model3d, m_backproj5, ranges);
            // calcBackProject(&hsv, 1, channels, m_model3d, m_backproj6, ranges);
            
            // tracking
            meanShift(m_backproj1, m_rc1, TermCriteria(TermCriteria::EPS, 10, 1));
            rectangle(frame, m_rc1, Scalar(0, 255, 0), 3);
            
            // meanShift(m_backproj2, m_rc2, TermCriteria(TermCriteria::EPS, 10, 1));
            // rectangle(frame, m_rc2, Scalar(0, 255, 0), 3);

            // meanShift(m_backproj3, m_rc3, TermCriteria(TermCriteria::EPS, 10, 1));
            // rectangle(frame, m_rc3, Scalar(0, 255, 0), 3);

            // meanShift(m_backproj4, m_rc4, TermCriteria(TermCriteria::EPS, 10, 1));
            // rectangle(frame, m_rc4, Scalar(0, 255, 0), 3);

            // meanShift(m_backproj5, m_rc5, TermCriteria(TermCriteria::EPS, 10, 1));
            // rectangle(frame, m_rc5, Scalar(0, 255, 0), 3);

            // meanShift(m_backproj6, m_rc6, TermCriteria(TermCriteria::EPS, 10, 1));
            // rectangle(frame, m_rc6, Scalar(0, 255, 0), 3);
        }
        
        // image display
        imshow("Tracker", frame);
        
        // user input
        char ch = waitKey(33);
        if (ch == 27) break; // ESC Key (exit)

        else if (ch == 32){ // SPACE Key (pause)
            while ((ch = waitKey(33)) != 32 && ch != 27);
            if (ch == 27) break;
        }
    }
    return 0;
}