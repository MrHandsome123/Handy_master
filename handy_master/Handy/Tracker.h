#pragma once

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;
#define DRAWTRACK 1
vector<Point> Track;
int state;
int dgBlue = 255, dgGreen = 255, dgRed = 0;
int thick = 0;

bool operator!=(Point a, Point b)
{
    if (abs(a.x - b.x) <= 10 && abs(a.y - b.y) <= 10)
    {
        return false;
    }
    return true;
}

void printTrack(Point curPoint, Mat &srcImage)
{
    if (state == DRAWTRACK)
    {
        circle(srcImage, curPoint, 0, Scalar(dgBlue, dgGreen, dgRed), thick + 1);
        if (Track.empty() || curPoint != Track.back())
            Track.push_back(curPoint);
    }
}