#include "tools.h"

int main(int argc, char** argv) {
    Mat img;
    int sm;
    String filename = "";
    CVTools tools;
    if(argc >1) filename = argv[1];
    if(filename.length()==0){
        cout << "Введите имя файла: " ;
        cin >> filename;
    }
    String winName = "Test "+filename;
    Mat channel[3],ch[3];
    Mat image = imread(filename);
    if (image.empty()){
  	cout << "Невозможно прочитать файл " << filename << endl;
  	cin.get(); //стукнем по клавише - любой
  	return -1;
    }
    namedWindow(winName, IMREAD_COLOR);
    channel[0] = tools.get_filter(ImgFilter::CIRCLE,image);// выделим кружок/шарик
    channel[1] = tools.get_filter(ImgFilter::PATH_LINES,image);//выделим направляющие
    channel[2] = tools.get_filter(ImgFilter::BOXES,image);//выделим ящики
    
    for(int i=0;i<image.size().height;i++){
        channel[0] = tools.shiftImg(channel[0],0,1);//Двигаем кружок/шарик вниз
        sm = tools.intersection(channel[0],channel[1]);
        if(sm>0)break;
        sm = tools.intersection(channel[0],channel[2]);
        if(sm>0){
            tools.shiftImg(channel[0],3,0);
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
    Vec3i circle = tools.circleDetection(channel[0]);
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
    cout<<"Координаты шарика - " << coord <<std::endl;
    imshow(winName, image);
    while((cv::waitKey() & 0xEFFFFF) != 27);//Press ESC on window focus
    return 0;

}
