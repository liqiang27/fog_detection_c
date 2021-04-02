/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2020-10-29 01:47:08
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 15:42:10
 */
#ifndef GET_DARKCHANEL_H_
#define GET_DARKCHANEL_H_

#include "my_common.h"

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