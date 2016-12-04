#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv; 

int colortogray(int argc, char* argv){
    Mat image;
    Mat grayImage; 

    if(!argv[1]){
        std::cerr << "No image data!" << std::endl;
        return -1; 
    }

    image = imread(argv, 1);
        while(image.empty()){
            printf("cannot access image.....empty!!! :(");
        }
    cvtColor(image, grayImage, CV_BGR2GRAY);
    imwrite("Gray_Image.jpg", grayImage);

    namedWindow(argv, CV_WINDOW_AUTOSIZE);
    namedWindow("Gray Image", CV_WINDOW_AUTOSIZE);

    imshow(argv, image);
    imshow("Gray Image", grayImage);

    waitKey(0);
    return 0;
}