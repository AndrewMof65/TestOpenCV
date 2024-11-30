#include "tools.h"

Mat CVTools::get_filter(ImgFilter type,Mat &image){
    int hmin;//фильтруем красный кружок
    int hmax;
    int vmax;
    int smin = 0;
    int vmin = 0;
    int smax = 255;
    Mat HSV,threshold;
    cvtColor(image, HSV, COLOR_BGR2HSV);
    switch (type){
        case ImgFilter::CIRCLE://фильтруем красный кружок
            hmin = 175;
            hmax = 180;
            vmax = 255;
            break;  
        default:
        case ImgFilter::PATH_LINES://фильтруем черные линии
            hmin = 0;
            hmax = 180;
            vmax = 0;
            break;    
        case ImgFilter::BOXES://фильтруем синие ящики
            hmin = 90;
            hmax = 110;
            vmax = 255;
            break;
    }
    inRange(HSV, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), threshold);
    return threshold;
}

Mat CVTools::shiftImg(Mat &image, int offsetX, int offsetY){
    Mat shiftMat = (Mat_<double>(2,3) << 1, 0, offsetX, 0, 1, offsetY);
    warpAffine(image,image,shiftMat,image.size());
    return image;
}

int CVTools::intersection(Mat &img1,Mat &img2){
        Mat img;
        bitwise_and(img1,img2,img);
        int sm_prev=sum(img).val[0];
        int sm_next = sm_prev;
        int i=0;
        while(sm_next>0 and i<2){
                img1 = (i==0)?shiftImg(img1,1,0):shiftImg(img1,-3,0);
                bitwise_and(img1,img2,img);
                sm_next=sum(img).val[0];
                if(sm_next<sm_prev){
                    if(sm_next>0){
                        shiftImg(img1,0,-1);
                        sm_next = 0;
                    }
                }
                i++;
        }
        return sm_next;
}


Vec3i CVTools::circleDetection(Mat &image) {
    Vec3i c;
    Mat thr;
    threshold(image, thr, 128, 255, THRESH_BINARY);
    // Размываем изображение для уменьшения шума
    GaussianBlur(128-thr, image, Size(21, 21), 3, 3);
    // Поиск кругов с использованием преобразования Хафа (на сером фоне)
    vector<cv::Vec3f> circles;
    HoughCircles(image, circles, HOUGH_GRADIENT, 1, image.rows / 8, 50, 50, 0, 0);
    Mat result = Mat::zeros(image.rows, image.cols, CV_8UC1);
    cout<< "Circles=" << circles.size()<<endl;
    for (size_t i = 0; i < circles.size(); i++) {
        c = circles[i];
        break;
    }
    return c;
}
