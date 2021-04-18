#ifndef IMGPREPROCESS_H_
#define IMGPREPROCESS_H_
/*
 * @Descripttion: imgPreprocess
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:14:18
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:24:52
 */

#include "get_darkchanel.h"
#include "get_slice.h"


class imgProcessor {
public:
imgProcessor();
~imgProcessor();
bool setImage(cv::Mat& img);
bool setMode(int mode = 0);  //0：同时进行darkChannel和slice操作；1：仅进行darkChannel操作
IMGS getImg();
private:
    darkChanel* t_darkChanel;
    Slicer* t_slicer;
    cv::Mat t_img;
    cv::Mat d_img;
    cv::Mat rgb_img;
    cv::Mat k_img;
    int mode;
    IMGS t_vec;

    void imgprocessing();
};

#endif

