/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2020-10-29 01:47:08
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-30 20:20:37
 */
#include "get_tensor.h"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;
using namespace at;

TensorCreator::TensorCreator(){
    batchsize  = 1;
}

bool TensorCreator::setRGBImg(vector<Mat>& imgs) {
    if(imgs.empty()){
        cout << "[error]: imgs is empty!" << endl;
        return false;
    }
    if(imgs.size() != batchsize) {
        cout << "[error]: imgs' size is not right!" << endl;
    }
    rgb_imgs = imgs;
}

bool TensorCreator::setDarkImg(vector<Mat>& imgs) {
    if(imgs.empty()){
        cout << "[error]: imgs is empty!" << endl;
        return false;
    }
    if(imgs.size() != batchsize) {
        cout << "[error]: imgs' size is not right!" << endl;
    }
    dark_imgs = imgs;
}

bool TensorCreator::setSliceImg(vector<Mat>& imgs) {
    if(imgs.empty()){
        cout << "[error]: imgs is empty!" << endl;
        return false;
    }
    if(imgs.size() != batchsize) {
        cout << "[error]: imgs' size is not right!" << endl;
    }
    slice_imgs = imgs;
}

bool TensorCreator::setIMGS(IMGS& imgs) {
    if(imgs.size() == 2) {
        rgb_imgs.push_back(imgs[0]);
        dark_imgs.push_back(imgs[1]);
        return true;
    }
    else {
        rgb_imgs.push_back(imgs[0]);
        dark_imgs.push_back(imgs[1]);
        slice_imgs.push_back(imgs[2]);
        return true;
    }
}

void TensorCreator::setBatchsize(int batchsize) {
    this->batchsize = batchsize;
}

void TensorCreator::processTensor(){

    for(int i = 0; i < batchsize; i++) {
        Mat rgb = rgb_imgs.at(i);
        Mat dark = dark_imgs.at(i);
        
        cvtColor(rgb, rgb, CV_BGR2RGB);
        
        rgb.convertTo(rgb, CV_32F, 1.0/255.0);
        dark.convertTo(dark, CV_32F, 1.0/255.0);
        
        at::Tensor tensor_1 = from_blob(rgb.data, {1, 448, 448, 3});
        tensor_1 = tensor_1.permute({0, 3, 1, 2});
        tensor_1[0][0] = tensor_1[0][0].sub_(0.485).div_(0.229);
        tensor_1[0][1] = tensor_1[0][1].sub_(0.456).div_(0.224);
        tensor_1[0][2] = tensor_1[0][2].sub_(0.406).div_(0.225);
        
        at::Tensor tensor_2 = from_blob(dark.data, {1, 448, 448, 1});
        tensor_2 = tensor_2.permute({0, 3, 1, 2});
        tensor_2[0][0] = tensor_2[0][0].sub_(0.485).div_(0.229);
        at::Tensor tensor_4 = cat(TensorList{tensor_1, tensor_2},1);
        if(i == 0){
            input_1 = tensor_4;
        }
        else {
            input_1 = cat(TensorList{input_1, tensor_4}, 0);
        }
        if(slice_imgs.size() !=0) {
            Mat slice = slice_imgs.at(i);
            cvtColor(slice, slice, CV_BGR2RGB);
            slice.convertTo(slice, CV_32F, 1.0/255.0);
            at::Tensor tensor_3 = from_blob(slice.data, {1, 448, 448, 3});
            tensor_3 = tensor_3.permute({0, 3, 1, 2});
            tensor_3[0][0] = tensor_3[0][0].sub_(0.485).div_(0.229);
            tensor_3[0][1] = tensor_3[0][1].sub_(0.456).div_(0.224);
            tensor_3[0][2] = tensor_3[0][2].sub_(0.406).div_(0.225);
            if(i == 0){
                input_2 = tensor_3;
            }
            else {
                input_2 = cat(TensorList{input_2, tensor_3}, 0);
            }
        }
    }
}

at::Tensor TensorCreator::getInput1(){
    return input_1;
}

at::Tensor TensorCreator::getInput2() {
    return input_2;
}