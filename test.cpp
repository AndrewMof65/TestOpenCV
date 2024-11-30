#include "tools.h"

int main(int argc, char** argv) {
    Mat img;
    int sm;
    char mk_video = 'n';
    VideoWriter outputVideo;
    String filename = "";
    string videofile="test.mp4";
    if(argc >1) filename = argv[1];
    if(filename.length()==0){
        cout << "Введите имя файла: " ;
        cin >> filename;
    }
    cout << "Видеофайл делаем? y/n: " ;
    cin >> mk_video;
    if(mk_video == 'y'){
        getline(stringstream(filename), videofile, '.');
        videofile += ".mp4";
        cout<<"Запись видео в файл "<<videofile<<endl;
    }
    String winName = "Test_"+filename;
    Mat channel[3],ch[3];
    Mat image = imread(filename);
    if (image.empty()){
  	cout << "Невозможно прочитать файл " << filename << endl;
  	cin.get(); //стукнем по клавише - любой
  	return -1;
    }
    namedWindow(winName, IMREAD_COLOR);
    channel[0] = CVTools::get_filter(ImgFilter::CIRCLE,image);// выделим кружок/шарик
    channel[1] = CVTools::get_filter(ImgFilter::PATH_LINES,image);//выделим направляющие
    channel[2] = CVTools::get_filter(ImgFilter::BOXES,image);//выделим ящики
    if(mk_video == 'y'){
        int codec = VideoWriter::fourcc('m', 'p', '4', 'v');  
        outputVideo.open(videofile, codec,10, Size(image.size().width,image.size().height)); 
        if (!outputVideo.isOpened()){
            cout  << "Не открывается файл для записи видео: "<< endl;
            return -1;
        }
    }
    for(int i=0;i<image.size().height;i++){
        channel[0] = CVTools::shiftImg(channel[0],0,1);//Двигаем кружок/шарик вниз
        sm = CVTools::intersection(channel[0],channel[1]);
        if(sm>0)break;
        sm = CVTools::intersection(channel[0],channel[2]);
        if(sm>0){
            CVTools::shiftImg(channel[0],3,0);
            break;
        }
        ch[0] = 255-channel[0];
        ch[1] = 255-channel[1];
        ch[2] = 255-channel[2];
        merge(ch,3,image);
        imshow(winName, image);
        if(i%4==0 && outputVideo.isOpened())outputVideo << image;
        usleep(2000);
        if(waitKey(10) >= 0)break;
    }
    Vec3i circle = CVTools::circleDetection(channel[0]);
    String coord = "Cx=";
    coord+=to_string(circle[0]);
    coord+=",Cy=";
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
    if(outputVideo.isOpened())
        for(int i=0;i<50;i++) outputVideo << image;
        outputVideo.release();
    cout << "Press ESC on Window "<< winName <<" focus" << endl;
    while((cv::waitKey() & 0xEFFFFF) != 27);
    cout<<"End Ok"<<std::endl;
    return 0;

}
