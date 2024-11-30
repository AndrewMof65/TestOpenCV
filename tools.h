
#ifndef TOOLS_H
#define TOOLS_H
#endif

#include <opencv2/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"

#include <unistd.h>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

enum class ImgFilter{
    CIRCLE,
    PATH_LINES,
    BOXES
};

class CVTools{
public:
    CVTools(){}
    static Mat get_filter(ImgFilter type,Mat &image);
    static Mat shiftImg(Mat &image, int offsetX, int offsetY);
    static int intersection(Mat &img1,Mat &img2);
    static Vec3i circleDetection(Mat &image);
};