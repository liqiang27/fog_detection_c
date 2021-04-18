#ifndef GET_SLICE_H_
#define GET_SLICE_H_
/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2020-10-29 01:47:08
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:09:52
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

#endif

