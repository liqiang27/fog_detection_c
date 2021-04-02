
#include "get_slice.h"

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"


using namespace std;
using namespace cv;

static Mat slice_img_random(Mat& img){
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

static Mat slice_img(Mat& img){
    int cols = img.cols;
    int rows = img.rows;
    
    
    Mat img_gray(img.cols, img.rows, CV_8UC1);
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    blur(img_gray,img_gray,Size(3,3));
    Canny(img_gray, img_gray, 10, 20);
    // imshow("canny", img_gray);

    int x_pos;
    int y_pos;
    int count = -1;
    for(int i = 0; i< 200; i++) {
        srand((unsigned int)time(NULL)+ i*100);
        int temp_count = 0;
        int temp_x_pos = rand() % (cols- 448);
        int temp_y_pos = rand() % (rows - 448);
        while (temp_y_pos < 100  || temp_y_pos > 980-448) {
            temp_y_pos = rand() % (rows - 448);
        }
        // cout << temp_x_pos << ":" << temp_y_pos << endl;
        for(int x = temp_x_pos; x  < temp_x_pos + 448 ; x++){
            for(int y = temp_y_pos; y < temp_y_pos + 448; y++){
                if(img_gray.at<uchar>(y, x) == 255){
                    temp_count ++;
                }
            }
        }
        if(temp_count > count)
        {
            x_pos = temp_x_pos;
            y_pos = temp_y_pos;
            count = temp_count;
            // cout <<"count: " << count <<endl;
        }
    }
    // cout << "yes" << endl;
    Rect slice(x_pos, y_pos, 448, 448);
    Mat slice_img = img(slice);
    return slice_img;
}

static Mat sliceByhistogram(Mat& img) {
    vector<int> u_list(1920, 0), v_list(1080, 0);
    int cols = img.cols;
    int rows = img.rows;
    
    cout <<cols <<"; " <<rows<< endl;
    Mat img_gray(img.cols, img.rows, CV_8UC1);
    cvtColor(img, img_gray, COLOR_BGR2GRAY);
    blur(img_gray,img_gray,Size(3,3));
    Canny(img_gray, img_gray, 5, 12);
    for(int  u= 0; u<cols; u++) {
        for(int v = 0; v< rows; v++) {
            //遍历是先行后列
            if (img_gray.at<uchar>(v, u) ==255) {
                u_list[u] +=1;
                v_list[v] +=1;
            }
        }
    }
    int max_u = 0, max_v = 0;
    int sum = -1;
    for(int u = 0; u < 1920-448; u++) {
        int tmp = 0;
        for (int t = 0; t < 448; t++) {
            tmp += u_list[u + t];
        }
        if (tmp > sum) {
            max_u = u;
            sum = tmp;
            // cout << "sum1:" << sum << endl;
        }
    }
    int sum_ = -1;
    for(int v = 100; v < 1080-548; v++) {
        int tmp = 0;
        for (int t = 0; t < 448; t++) {
            tmp += v_list[v + t];
        }
        if (tmp > sum_) {
            max_v = v;
            sum_ = tmp;
            // cout << "sum2:" << sum_ << endl;
        }
    }

    // cout << "yes" << endl;
    //在point 或 rec中，先列后行
    Rect slice(max_u, max_v, 448, 448);
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
    src_img = img.clone();
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
        sliced_img = sliceByhistogram(src_img);
    }
}

