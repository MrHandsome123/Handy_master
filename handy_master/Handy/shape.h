#pragma once
#include "opencv2/opencv.hpp"
#include <string>

using namespace cv;
using namespace std;

void getContours(Mat picDil, Mat pic_after){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(picDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    for(int i=0; i<contours.size(); i++){
        string shape;
        vector<vector<Point>> conPoly(contours.size()); //储存拐点
        vector<Rect> boundRect(contours.size());

        float perimeter = arcLength(contours[i], true);
        approxPolyDP(contours[i], conPoly[i], 0.05 * perimeter, true);
        drawContours(pic_after, conPoly, i, Scalar(255, 0, 255), 2);
        boundRect[i] = boundingRect(conPoly[i]);

        int num = (int)conPoly[i].size();
        if(num == 3){
            shape = "Triangle";
        }
        if(num == 4){
//            float ratio = (float) boundRect[i].width/(float)boundRect[i].height; //长宽�??
//            if(ratio > 0.95 && ratio < 1.05){
//                shape = "Square";
//            } else {
//                shape = "Rectangle";
//            }
            shape = "Quadrilateral";
        }
        if(num > 4){
            shape = "Circle";
        }
        putText(pic_after, shape, {boundRect[i].x, boundRect[i].y - 5}, FONT_HERSHEY_DUPLEX, 0.75, Scalar(0,69,255), 2);
    }
}

void shape_analysis(vector<Point> arr){
    Mat pic(800, 800, CV_8UC3, Scalar(255, 255, 255));
    Mat pic_after(800, 800, CV_8UC3, Scalar(255, 255, 255));
    for(int i=0; i<arr.size()-1; i++){
        line(pic, arr[i], arr[i+1],Scalar(255, 0, 0));
    }
    line(pic, arr[arr.size()-1], arr[0],Scalar(255, 0, 0));
    Mat picGray; //转为灰度
    cvtColor(pic, picGray, COLOR_BGR2GRAY);
    Mat picBlur; //添加高斯模糊
    GaussianBlur(picGray, picBlur, Size(3,3), 3, 0);
    Mat picCanny; //坎尼边缘检�??
    Canny(picBlur, picCanny, 25, 75);
    Mat picDil;   //进行膨胀操作
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(picCanny, picDil, kernel);

    getContours(picDil, pic_after);
    imshow("Shape Testing", pic_after);
    waitKey(0);
}