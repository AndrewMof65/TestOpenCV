#include <opencv2/core.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <unistd.h>
#include <iostream>


using namespace cv;
using namespace std;

enum class ImgFilter{
    CIRCLE,
    PATH_LINES,
    BOXES
};

Mat get_filter(ImgFilter type,Mat &image){
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

Mat shiftImg(Mat &image, int offsetX, int offsetY){
    Mat shiftMat = (Mat_<double>(2,3) << 1, 0, offsetX, 0, 1, offsetY);
    warpAffine(image,image,shiftMat,image.size());
    return image;
}

int intersection(Mat &img1,Mat &img2){
        Mat img;
        bitwise_and(img1,img2,img);
        int sm=sum(img).val[0];
        for(int i=0;i<2;i++){
            if(sm>0){
                img1 = (i==0)?shiftImg(img1,1,-1):shiftImg(img1,-3,0);
                bitwise_and(img1,img2,img);
                sm=sum(img).val[0];
            }
        }
        return sm;
}


Vec3i circleDetection(Mat &image) {
    Vec3i c;
    Mat thr;
    threshold(image, thr, 128, 255, cv::THRESH_BINARY);
    // Размываем изображение для уменьшения шума
    GaussianBlur(128-thr, image, Size(21, 21), 3, 3);
    // Поиск кругов с использованием преобразования Хафа (на сером фоне)
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, 1, image.rows / 8, 50, 50, 0, 0);
    cv::Mat result = Mat::zeros(image.rows, image.cols, CV_8UC1);
    std::cout<< "Circles=" << circles.size()<<endl;
    for (size_t i = 0; i < circles.size(); i++) {
        c = circles[i];
        break;
    }
    return c;
}



int main(int argc, char** argv) {
    
    const String filename = "2.png";
    String winName = "Test "+filename;
    Mat channel[3],ch[3];
    
    namedWindow(winName, IMREAD_COLOR);
    Mat image = imread(filename);
    if (image.empty()){
  	cout << "Could not open or find the image" << endl;
  	cin.get(); //wait for any key press
  	return -1;
    }
    channel[0] = get_filter(ImgFilter::CIRCLE,image);
    channel[1] = get_filter(ImgFilter::PATH_LINES,image);
    channel[2] = get_filter(ImgFilter::BOXES,image);

    Mat img;
    int sm;
    cout<<"Height = " << image.size().height<<std::endl;
    for(int i=0;i<image.size().height;i++){
        channel[0] = shiftImg(channel[0],0,1);
        sm = intersection(channel[0],channel[1]);
        if(sm>0)break;
        sm = intersection(channel[0],channel[2]);
        if(sm>0){
            shiftImg(channel[0],3,0);
            break;
        }
        ch[0] = 255-channel[0];
        ch[1] = 255-channel[1];
        ch[2] = 255-channel[2];
        merge(ch,3,image);
        imshow(winName, image);
        usleep(2000);
        if(waitKey(10) >= 0)break;
    }
    cout<<"End"<<std::endl;
    Vec3i circle = circleDetection(channel[0]);
    String coord = "X=";
    coord+=to_string(circle[0]);
    coord+=",Y=";
    coord+=to_string(circle[1]);
    coord+=",D=";
    coord+=to_string(circle[2]);
    putText(image,coord,
            Point(15,50),
            FONT_HERSHEY_PLAIN,
            3,
            Scalar(0,0,0),
            4);
    imshow(winName, image);
    waitKey(0);
    return 0;

}
