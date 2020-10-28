#ifndef GET_SLICE_H_
#define GET_SLICE_H_

#include <iostream>
#include <memory.h>

#include "opencv2/opencv.hpp"

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

#endif
