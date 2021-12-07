#include "opencv/cv.hpp"
#include <iostream>
#include <opencv2/dnn.hpp>
#include <fstream>

using namespace cv;
using namespace std;
using namespace dnn;

void morphOps_backSub(Mat &thresh);

void only_people_deep_grabCut(Mat src, Mat &dst);
void only_people_backSub(Mat src, Mat background, Mat &dst);

void face_detection(Mat src, Mat &dst);
void only_face(Mat src, Mat &dst);

int main() {
    Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(700, 20, false);
    Mat frame, onlyPeople, faceDetection, onlyFace, background, foreground, foregroundMask;

    VideoCapture cap;
    
    if (cap.open("Faces.mp4") == 0) {
        cout << "no such file!" << endl;
        waitKey(0);
    }

    int key = -1;
    int command = -1;

    while (1) {
        if(!cap.read(frame)) {
            cap.set(CAP_PROP_POS_FRAMES, 0);
            cap.read(frame);
        }
        resize(frame, frame, Size(1100, 600));
        
        if (foregroundMask.empty())
            foregroundMask.create(frame.size(), frame.type());

        bg_model->apply(frame, foregroundMask);
        GaussianBlur(foregroundMask, foregroundMask, Size(11, 11), 3.5, 3.5);
        threshold(foregroundMask, foregroundMask, 20, 255, THRESH_BINARY);

        if(key == -1 || command == -1) {
            imshow("Face", frame);
        }
        if(key != -1) {
            if(command == key)
                command = -1;
            else 
                command = key;
        }

        if(command == 'b') {
            only_people_deep_grabCut(frame, onlyPeople);
            imshow("Face", onlyPeople);
        }
        
        if(command == 'B') {
            // only_people_backSub(frame, background, onlyPeople);
            morphOps_backSub(foregroundMask);
            foreground = Scalar::all(0);
            frame.copyTo(foreground, foregroundMask);
            imshow("Face", foreground);
        }

        if(command == 'f') {
            face_detection(frame, faceDetection);
            imshow("Face", faceDetection);
        }
        
        if(command == 'g') {
            only_face(frame, onlyFace);
            imshow("Face", onlyFace);
        }
        key = waitKey(33);
        cout << key << endl;
    }

    return 0;
}

void only_people_deep_grabCut(Mat src, Mat &dst) {
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
    Mat element = getStructuringElement(MORPH_ELLIPSE, Size(11,11));

    erode(thresh, thresh, element);
    erode(thresh, thresh, element);
    
	dilate(thresh, thresh, element);

    medianBlur(thresh, thresh, 11);
}

void only_people_backSub(Mat src, Mat background, Mat &dst) {
    Mat gray, result;

    cvtColor(src, gray, CV_BGR2GRAY);
    absdiff(gray, background, result);
    
    GaussianBlur(result, result, Size(11, 11), 3.5, 3.5);
    threshold(result, result, 20, 255, CV_THRESH_BINARY);
    morphOps_backSub(result);
    medianBlur(result, result, 11);

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

void face_detection(Mat src, Mat &dst) {
    CascadeClassifier face_classifier;
    Mat grayframe;
    vector<Rect> faces;
    vector<double> face_sizes;
    int i;
    
    face_classifier.load("haarcascade_frontalface_alt.xml");
    
    cvtColor(src, grayframe, COLOR_BGR2GRAY);
    face_classifier.detectMultiScale(
                grayframe,
                faces,
                1.1, // increase search scale by 10% each pass
                3, // merge groups of three detections
                0, // not used for a new cascade
                Size(30, 30), //min size
                Size(70, 70) //max ize
    );

    for (i = 0; i < faces.size(); i++) {
        face_sizes.push_back(faces[i].area());
    }

    int neareast = max_element(face_sizes.begin(), face_sizes.end()) - face_sizes.begin();
    int farthest = min_element(face_sizes.begin(), face_sizes.end()) - face_sizes.begin();

    for (i = 0; i < faces.size(); i++) {
        Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        Point tr(faces[i].x, faces[i].y);
        if(i == neareast) 
            rectangle(src, lb, tr, Scalar(0, 255, 0), 3, 4, 0);
        
        else if(i == farthest)
            rectangle(src, lb, tr, Scalar(255, 0, 0), 3, 4, 0);

        else
            rectangle(src, lb, tr, Scalar(30, 255, 255), 3, 4, 0);
    }
    src.copyTo(dst);
}

void only_face(Mat src, Mat &dst) {
    CascadeClassifier face_classifier;
    Mat grayframe;
    vector<Rect> faces;
    Mat faceGrabCut[3];
    int i;
    
    face_classifier.load("haarcascade_frontalface_alt.xml");
    
    cvtColor(src, grayframe, COLOR_BGR2GRAY);
    face_classifier.detectMultiScale(
                grayframe,
                faces,
                1.1, // increase search scale by 10% each pass
                3, // merge groups of three detections
                0, // not used for a new cascade
                Size(30, 30), //min size
                Size(70, 70) //max ize
    );
    
    Mat mask = Mat(src.size(), CV_8UC1, Scalar(0, 0, 0));

    for (i = 0; i < faces.size(); i++) {
        Point lb(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        Point tr(faces[i].x, faces[i].y);
        Mat bgModel, fgModel, result;

        grabCut(src, result, Rect(lb, tr), bgModel, fgModel, 10, GC_INIT_WITH_RECT);
        compare(result, GC_PR_FGD, result, CMP_EQ);
        add(result, mask, mask);
        
        faceGrabCut[i] = Mat(src.size(), CV_8UC3, Scalar(0, 0, 0));
        src.copyTo(faceGrabCut[i], result);
    }
    dst = Mat(src.size(), CV_8UC3, Scalar(0, 0, 0));
    
    for(int i = 0; i < faces.size(); i++)
        add(dst, faceGrabCut[i], dst);
    
    Mat bg = imread("virtualBackground.png");
    resize(bg, bg, Size(1100, 600));
    threshold(mask, mask, 20, 255, THRESH_BINARY_INV);

    bg.copyTo(dst, mask);
    
}