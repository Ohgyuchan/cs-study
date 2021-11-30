#include "opencv/cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

void morphOps_deep(Mat &thresh);
void morphOps_backSub(Mat &thresh);

void only_people_deep(Mat src, Mat &dst);
void only_people_backSub(Mat src, Mat background, Mat &dst);

void fadeDetection(Mat src, Mat &dst);
void onlyFace(Mat src, Mat &dst);

int main() {
    Mat frame, onlyPeople, faceDetection, onlyFace, background;
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(11, 11));

    VideoCapture cap;
    
    if (cap.open("Faces.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
    }

    int count = 2;

    cap >> background;
    cvtColor(background, background, COLOR_BGR2GRAY);

    // set background as the average of the first 10 frames.
    while(1) {
        if(!cap.read(frame)) break;

        cvtColor(frame, frame, CV_BGR2GRAY);
        
        add(frame / count, background*(count - 1) / count, background);
        
        count++;
    }

    cap.set(CAP_PROP_POS_FRAMES, 0);

    int key = -1;
    int command = 0;

    while (1) {
        if(!cap.read(frame)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }

        
        if(key == -1) {
            imshow("Face", frame);
        }
        if(key != -1) {
            if(command == key)
                command = 0;
            else 
                command = key;
        }
        if(command == 'b') {
            only_people_deep(frame, onlyPeople);
            while(1) {
                imshow("Face", onlyPeople);
                if(waitKey(0) == 'b') {
                    break;
                }
            }
            continue;
        }
        
        if(command == 'B') {
            only_people_backSub(frame, background, onlyPeople);
            while(1) {
                imshow("Face", onlyPeople);
                if(waitKey(0) == 'B') {
                    break;
                }
            }
            continue;
        }

        if(command == 'f') {
            
            while(1) {
                imshow("Face", onlyFace);
                if(waitKey(0) == 'f') {
                    break;
                }
            }
            continue;
        }
        
        key = waitKey(33);
    }

    return 0;
}

void morphOps_deep(Mat &thresh) {
	Mat dilateElement = getStructuringElement(MORPH_CROSS, Size(5,5));

	dilate(thresh,thresh,dilateElement);
}

void only_people_deep(Mat src, Mat &dst) {
    Mat people[5];

    String modelConfiguration = "deep/yolov2-tiny.cfg";
    String modelBinary = "deep/yolov2-tiny.weights";
    Net net = readNetFromDarknet(modelConfiguration, modelBinary);
    vector<String> classNamesVec;
    ifstream classNamesFile("deep/coco.names");

    if (classNamesFile.is_open()) {
        string className = "";
        while (std::getline(classNamesFile, className)) classNamesVec.push_back(className);
    }
        
    if (src.channels() == 4) cvtColor(src, src, COLOR_BGRA2BGR);
    
    // Convert Mat to batch of images
    Mat inputBlob = blobFromImage(src, 1 / 255.F, Size(416, 416), Scalar(), true, false);
    net.setInput(inputBlob, "data"); //set the network input
    Mat detectionMat = net.forward("detection_out"); //compute output
    
    float confidenceThreshold = 0.6;
    int count_people = 0;
    for (int i = 0; i < detectionMat.rows; i++) {
        const int probability_index = 5;
        const int probability_size = detectionMat.cols - probability_index;
        float *prob_array_ptr = &detectionMat.at<float>(i, probability_index);
        size_t objectClass = max_element(prob_array_ptr, prob_array_ptr + probability_size) -
        prob_array_ptr;
        // prediction probability of each class
        float confidence = detectionMat.at<float>(i, (int)objectClass + probability_index);
        // for drawing labels with name and confidence
        if (confidence > confidenceThreshold) {
            float x_center = detectionMat.at<float>(i, 0) * src.cols;
            float y_center = detectionMat.at<float>(i, 1) * src.rows;
            float width = detectionMat.at<float>(i, 2) * src.cols;
            float height = detectionMat.at<float>(i, 3) * src.rows;
            
            Point p1(cvRound(x_center - width / 2), cvRound(y_center - height / 2));
            Point p2(cvRound(x_center + width / 2), cvRound(y_center + height / 2));
            Rect object(p1, p2);
            Scalar object_roi_color(0, 255, 0);
            
            String className = objectClass < classNamesVec.size() ? classNamesVec[objectClass] : format("unknown(%d)", objectClass);
            if(className.compare("person?")) count_people++;
            
            Mat bgModel, fgModel, result;
            grabCut(src, result, object, bgModel, fgModel, 10, GC_INIT_WITH_RECT);
            compare(result, GC_PR_FGD, result, CMP_EQ);
            morphOps_deep(result);
    
            people[count_people - 1] = Mat(src.size(), CV_8UC3, Scalar(0, 0, 0));
            src.copyTo(people[count_people - 1], result);
        }
    }
    dst = Mat(src.size(), CV_8UC3, Scalar(0, 0, 0));
    
    for(int i = 0; i < count_people; i++)
        add(dst, people[i], dst);

    putText(dst, format("how many people: %d", count_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
}

void morphOps_backSub(Mat &thresh) {
    Mat element = getStructuringElement(MORPH_CROSS, Size(27,27));
	Mat delement = getStructuringElement(MORPH_CROSS, Size(8,45));

    erode(thresh,thresh,element);
    erode(thresh,thresh,element);
    
	dilate(thresh,thresh,delement);
}

void only_people_backSub(Mat src, Mat background, Mat &dst) {
    Mat gray, result;

    cvtColor(src, gray, CV_BGR2GRAY);
    absdiff(gray, background, result);
    
    threshold(result, result, 20, 255, CV_THRESH_BINARY);
    morphOps_backSub(result);
    medianBlur(result, result, 71);

    dst = Scalar::all(0);
    src.copyTo(dst, result);
    
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
        putText(dst, format("how many people: %d", cout_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
    }

    if(contours.size() == 0) {
        putText(dst, format("how many people: %d", cout_people), Point(50, 80), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 4);
    }
}