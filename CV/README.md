# CV
컴퓨터비전이란...
## Image Read
```c++
#include "opencv/cv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat frame;
    VideoCapture cap;
    
    if (cap.open("background.mp4") == 0) {
        cout << "no such file!" << endl;    
        waitKey(0);
    }

    while (1) {
        cap >> frame;
        if (frame.empty()) {
            cout << "end of video" << endl;
            break;
        }
        int msec = cap.get(CAP_PROP_POS_MSEC);
        int frames = cap.get(CAP_PROP_POS_FRAMES);
        int total_frames = cap.get(CAP_PROP_FRAME_COUNT);
        int fps = cap.get(CAP_PROP_FPS);

        if(msec >= 3000) {
            waitKey(0);
            break;
        }

        cout << "frames: " << frames <<"/" << total_frames << endl;

        imshow("Input Vedio", frame);

        //fps: 24, 1000/24: 41.6666666667
        waitKey(1000/fps);
    }
    
    return 0;
}
```
## Video read
## 밝기 조정
네거티브
로그
감마

## 필터링
