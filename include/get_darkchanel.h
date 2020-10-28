#ifndef GET_DARKCHANEL_H_
#define GET_DARKCHANEL_H_

#include <iostream>
#include <memory.h>
#include "opencv2/opencv.hpp"

class darkChanel
{
    public:
        darkChanel();
        bool readImg(const char* img_path);
        bool setImg(cv::Mat& img);
        cv::Mat getDarkchanel_img();
        void getDarkchanel(size_t width = 448, size_t hight= 448);
        void showImg();
    private:
        cv::Mat src_img;
        cv::Mat darkChanel_img;
        float* data;
};

#endif