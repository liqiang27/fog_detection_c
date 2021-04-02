#pragma once
/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2020-10-29 01:47:08
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 15:43:47
 */
#include "my_common.h"

class Slicer{
    public:
        Slicer();
        bool setImg(cv::Mat& img);
        cv::Mat getSliceimg();
        void sliceProcess();
        void setMode(int mode);
    private:
        cv::Mat src_img;
        cv::Mat sliced_img;
        int mode;
};

