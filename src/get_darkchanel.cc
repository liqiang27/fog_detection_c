#include "get_darkchanel.h"

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace cv;
using namespace cv;
using namespace std;

typedef struct Pixel 
{
    int x, y;
    int data;
}Pixel;

bool structCmp(const Pixel &a, const Pixel &b) 
{
    return a.data > b.data;//descending降序
}

//minimun  filter

static Mat minFilter(Mat srcImage, int kernelSize = 5){
    int radius = kernelSize / 2;
    int srcType = srcImage.type();
    int targetType = 0;
    if (srcType % 8 == 0) 
    {
        targetType = 0;
    }
    else 
    {
        targetType = 5;
    }
    Mat ret(srcImage.rows, srcImage.cols, targetType);
    Mat parseImage;
    copyMakeBorder(srcImage, parseImage, radius, radius, radius, radius, BORDER_REPLICATE);
    for (unsigned int r = 0; r < srcImage.rows; r++) 
    {
        float *fOutData = ret.ptr<float>(r);
        uchar *uOutData = ret.ptr<uchar>(r);
        for (unsigned int c = 0; c < srcImage.cols; c++) 
        {
            Rect ROI(c, r, kernelSize, kernelSize);
            Mat imageROI = parseImage(ROI);
            double minValue = 0, maxValue = 0;
            Point minPt, maxPt;
            minMaxLoc(imageROI, &minValue, &maxValue, &minPt, &maxPt);
            if (!targetType) 
            {
                *uOutData++ = (uchar)minValue;
                continue;
            }
            *fOutData++ = minValue;
        }
    }
    return ret;
}

//format transform to float32
static void makeDepth32f(Mat& source, Mat& output){
    if ((source.depth() != CV_32F) > FLT_EPSILON) {
        source.convertTo(output, CV_32F);
    }
    else {
        output = source;
    }
        
}

darkChanel::darkChanel(){
}

bool darkChanel::readImg(const char* img_path){
    if(img_path == nullptr){
        cout << "img_path is nullptr!" << endl;
        return false;
    }
    src_img = imread(img_path);
    if(src_img.empty()) {
        cout << "[error]: image is empty!" << endl;
        return false;
    }
    return true;
}

bool darkChanel::setImg(Mat& img){
    if(img.empty()){
        cout << "[error]: image is empty!" << endl;
        return false;
    }
    src_img = img.clone();
    return false;
}

Mat darkChanel::getDarkchanel_img(){
    if(darkChanel_img.empty()) {
        cout<< "[error]: dark chanel image is empty!" << endl;
        return darkChanel_img;
    }
    else {
        return darkChanel_img;
    }
    
}

void darkChanel::getDarkchanel(size_t width, size_t hight){
    Mat resized_img;
    resize(src_img,resized_img, Size(width,hight));
    Mat converted_img;
    resized_img.convertTo(converted_img, CV_32FC3, 1 / 255.0, 0);
        //int kernelSize = 15;
    Mat darkChannel(width, hight, CV_8UC1);
    int nr = width;
    int nl = hight;
    float b, g, r;
    cout << "generating dark channel image." << endl;
    if (resized_img.isContinuous()) 
    {
        nl = nr * nl;
        nr = 1;
    }
    for (int i = 0; i < nr; i++) 
    {
        float min;
        const uchar* inData = resized_img.ptr<uchar>(i);
        uchar* outData = darkChannel.ptr<uchar>(i);
        for (int j = 0; j < nl; j++) 
        {
            b = *inData++;
            g = *inData++;
            r = *inData++;
            min = b > g ? g : b;
            min = min > r ? r : min;
            *outData++ = min;
        }
    }
    darkChanel_img = minFilter(darkChannel);
}

void darkChanel::showImg(){
    imshow("darkChanel_img", darkChanel_img);
    waitKey(0);
}


