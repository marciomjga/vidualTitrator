#include    <opencv2/core/core.hpp>
#include    <opencv2/highgui/highgui.hpp>
#include    <opencv2/videoio.hpp>
#include    <opencv2/imgproc/imgproc.hpp>
#include    <vector>
#include    <iostream>
#include    <sstream>
#include    <fstream>
#include    <string>
#include    <math.h>

using namespace cv;
using namespace std;
// g++ main5.cpp -l opencv_core -l opencv_highgui -l opencv_videoio -o ex5
struct myPoint2d{
    int x;
    double y;
};
int main(int argc, char** argv){
    cv::VideoCapture cap("Video1C.mp4");
    if(!cap.isOpened()){
        std::cout<<"Vídeo não pode ser aberto"<<std::endl;
        return -1;
    }
    myPoint2d point;
    std::vector<myPoint2d>  meansT(10000);
    int i = 0, col_means = 1, col_indexes = 0;
    cv::Mat frame;
    cap >> frame;
    Mat croppedImage, smoothedCroppedImage, hsvImage;
    while(!frame.empty()){
        Mat ROI(frame, Rect(820,561,1108-820,902-561));
        ROI.copyTo(croppedImage);
        GaussianBlur(croppedImage, smoothedCroppedImage,Size(5,5), 0,0);
        cvtColor(smoothedCroppedImage,hsvImage, CV_RGB2HSV);
        cv::Scalar means = mean(hsvImage);
        myPoint2d aux;
        aux.x = i;
        aux.y = means.val[0];
        meansT.push_back(aux);
        i++;
        cap >> frame;
    }
    stringstream aux;
    aux << "[";
    for(int j=0;j<meansT.size();j++){
        if(meansT[j].x >0){
            aux << meansT[j].x;
            aux << ",";
            aux << meansT[j].y;
            aux << ";";
        }
    }
    aux << "]";
    ofstream myfile ("example.txt");
    if(myfile.is_open()){
        myfile << aux.str();
        myfile.close();
    } else{
        cout << "Unable to open file";
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
// 820 561
// 1108 902