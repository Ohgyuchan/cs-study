#include <iostream>
#include "opencv/cv.hpp"
/*
C: 23
blockSize: 123
*/

using namespace cv;
using namespace std;

float mean(int arr[], int n) { 
    float sum = 0, mean = 0; 
    // sum of arr 
    for (int i = 0; i < n; i++) { 
        sum += arr[i]; 
    } 
    mean = sum / n; //printf("sum : %lf, mean : %lf\n", sum, mean); 
    return mean; 
}

void leastSquare(int arr1[], int arr2[], int n) { 
    // Calculate mean of arr1, arr2
    float x_bar = mean(arr1, n);
    float y_bar = mean(arr2, n);
    
    // y = ax + b
    float a, b; 
    float sum1 = 0, sum2 = 0; 
    
    // Calculate sum1 , sum2 
    for (int i = 0; i < n; i++) { 
        sum1 += (arr1[i] - x_bar) * (arr2[i] - y_bar); sum2 += pow((arr1[i] - x_bar), 2); 
    } 
    //printf("sum1 : %lf, sum2 : %lf\n", sum1, sum2);
    // Calculate a 
    a = sum1 / sum2;
    // Calculate b 
    b = y_bar - a * x_bar; 
    printf("y = %lfx + %lf\n", a, b);
}

int main() {
    Mat finger_print, adaptive_1, adaptive, result1, result2;

    finger_print = imread("finger_print.png", 0);
    adaptive_1 = imread("adaptive_1.jpg", 0);
    adaptive = imread("adaptive.png", 0);

    result1 = adaptive.clone();
    result2 = adaptive.clone();
    
    int blockSize = 3;
    int C = 0;
    threshold(result1, result1, 0, 255, THRESH_BINARY | THRESH_OTSU);
    threshold(result2, result2, 0, 255, THRESH_BINARY | THRESH_OTSU);

    while(1) {
        // OTSU Algorithm

        // imshow("finger_print", finger_print);
        imshow("original", adaptive);
        imshow("adaptive_1_G", result1);
        imshow("adaptive_1", result2);

        
        int key = waitKey();
        if(key == 'a') {
            blockSize += 2;
            cout << blockSize << endl;
        }
        if(key == 's') {
            if(blockSize > 3) blockSize -= 2;;
            cout << blockSize << endl;
        }
        if(key == 'r') {
            blockSize = 3;
            C = 0;
        }
        if(key == 'f') {
            blockSize = 27475;
            cout << blockSize << endl;
        }
        
        if(key == 'p') {
            cout << "blockSize: " << blockSize << endl;
            cout << C << endl;
        }

        if(key == 'c') {
            C++;
            cout << C << endl;
        }

        if(key == 'C') {
            C--;
            cout << C << endl;
        }
        adaptiveThreshold(adaptive, result1, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, blockSize, C);
        adaptiveThreshold(adaptive, result2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, blockSize, C);

        // adaptiveThreshold(adaptive, result2, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);
    }


    return 0;
}