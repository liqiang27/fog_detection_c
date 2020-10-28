
#include "get_slice.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace cv;

static Mat slice_img_random(Mat img){
    cout << "start slice!" << endl;
    int cols = img.cols;
    int rows = img.rows;

    srand((unsigned int)time(NULL));
    int x_pos = rand() % (cols- 448);
    int y_pos = rand() % (rows - 448);

    Rect slice(x_pos, y_pos, 448, 448);
    Mat slice_img =  img(slice);
    return slice_img;
}

static Mat slice_img(Mat img){
    int cols = img.cols;
    int rows = img.rows;
    
    Mat img_gray(img.cols, img.rows, CV_8UC1);
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    blur(img_gray,img_gray,Size(3,3));
    Canny(img_gray, img_gray, 10, 20);
    imshow("canny", img_gray);

    int x_pos;
    int y_pos;
    int count = -1;
    for(int i = 0; i< 20 ; i++) {
        srand((unsigned int)time(NULL)+ i*100);
        int temp_count = 0;
        int temp_x_pos = rand() % (cols- 448);
        int temp_y_pos = rand() % (rows - 448);
        for(int x = temp_x_pos; x  < temp_x_pos + 448 ; x++){
            for(int y = temp_y_pos; y < temp_y_pos + 448; y++){
                if(img_gray.at<uchar>(x, y) == 255){
                    // cout <<int(img_gray.at<uchar>(x, y)) << endl;
                    temp_count ++;
                }
            }
        }
        if(temp_count > count)
        {
            x_pos = temp_x_pos;
            y_pos = temp_y_pos;
            count = temp_count;
            cout << count << endl;
            
        }
    }

    Rect slice(x_pos, y_pos, 448, 448);
    Mat slice_img = img(slice);
    return slice_img;
}

Slicer::Slicer(){

    mode = 1;
};

bool Slicer::setImg(Mat& img){
    if(img.empty()){
        cout << "[error]: the img is empty!" << endl;
        return false;
    }
    img.copyTo(src_img);
    return true;
}

Mat Slicer::getSliceimg(){
    if(sliced_img.empty()) {
        cout << "[error]: slice img is empty!" << endl;
        return sliced_img;
    }
    else {
        return sliced_img;
    } 
}

void Slicer::setMode(int mode){
    this->mode = mode;
}

void Slicer::sliceProcess() {
    if(mode == 0){
        sliced_img = slice_img_random(src_img);
    }
    else {
        sliced_img = slice_img(src_img);
    }
}

