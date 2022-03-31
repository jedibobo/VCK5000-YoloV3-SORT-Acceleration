#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    VideoCapture cap;
    String vidPath = "walking_humans.nv12.1920x1080.h264";
    // open the default camera, use something different from 0 otherwise;
    if (!cap.open(vidPath))
        return 0;
    // Create mat with alpha channel
    Mat mat(480, 640, CV_8UC4);
    int i = 0;
    int delay = 1;
    while (1)
    { // forever
        Mat frame;
        cap >> frame;
        if (frame.empty())
            break; // end of video stream
        imshow("this is you, smile! :)", frame);
        if ((waitKey(delay) == 113))//q to exit
			break;
    }
    return 0;
}