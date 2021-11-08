#include <iostream>
#include "opencv/cv.hpp"
/*
C: 23
blockSize: 123
*/

using namespace cv;
using namespace std;

int main() {
    Mat finger_print, adaptive_1, adaptive, result1, result2;

    finger_print = imread("finger_print.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    result1 = adaptive_1.clone();
    result2 = adaptive_1.clone();
    
    int blockSize = 3;
    int C = 5;

    while(1) {
        // OTSU Algorithm
        threshold(finger_print, finger_print, 0, 255, THRESH_BINARY | THRESH_OTSU);

        // imshow("finger_print", finger_print);
        imshow("adaptive_1_G", result1);
        imshow("adaptive_1", result2);

        
        int key = waitKey();
        if(key == 'a') {
            blockSize += 2;
            cout << blockSize << endl;
        }
        if(key == 's') {
            blockSize -= 2;;
            cout << blockSize << endl;
        }
        if(key == 'r') {
            blockSize = 3;
            C = 1;
        }
        if(key == 'f') {
            blockSize = 27475;
            cout << blockSize << endl;
        }

        if(key == 'c') {
            C += 2;
            cout << C << endl;
        }
        if(key == 'C') {
            C -= 2;
            cout << C << endl;
        }
        if(key == 'p') {
            cout << "C: " << C << endl;
            cout << "blockSize: " << blockSize << endl;
        }
        adaptiveThreshold(adaptive_1, result1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, C);
        adaptiveThreshold(adaptive_1, result2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);

        // adaptiveThreshold(adaptive, result2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);
    }


    return 0;
}