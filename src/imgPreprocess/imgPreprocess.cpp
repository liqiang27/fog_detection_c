/*
 * @Descripttion: imgPreprocess
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:14:30
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-30 16:09:57
 */

#include "imgPreprocess.h"

imgProcessor::imgProcessor(){
    t_darkChanel = new darkChanel();
    t_slicer = new Slicer();
    mode = 1;
}

imgProcessor::~imgProcessor() {
    delete t_tensor;
    delete t_slicer;
    delete t_darkChanel;
}

bool imgProcessor::setImage(cv::Mat& img) {
    if(img.empty()) {
        printf("[ERROR]: img processing error, image is empty!\n");
        return false;
    }
    t_img = img.clone(); //深度拷贝
    /*
    t_img = img //浅拷贝
    */
}

void imgProcessor::setMode(int mode) {
    this->mode = mode;
}

void imgProcessor::imgprocessing() {
    //获取暗通道图像
    t_darkChanel->setImg(t_img);
    t_darkChanel->getDarkchanel();
    d_img = t_darkChanel->getDarkchanel_img().clone();

    //对原图进行resize
    rgb_img = t_img.clone()
    cv::resize(rgb_img, rgb_img, Size(448, 448));

    //获取key_local image 
    if(mode == 0) {
        t_slicer->setImg(t_img);
        t_slicer->sliceProcess();
        k_img = t_slicer->getSliceimg().clone();
    }
}

IMGS imgProcessor::getImg() {
    this->imgprocessing();
    t_vec.push_back(rgb_img);
    t_vec.push_back(d_img);
    if(mode == 1) return t_vec;
    t_vec.push_back(k_img);
    return t_vec;
}