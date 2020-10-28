#ifndef GET_TENSOR_H_
#define GET_TENSOR_H_

#include <iostream>
#include <vector>
#include <torch/script.h>
#include <ATen/ATen.h>

#include "opencv2/opencv.hpp"

class TensorCreator{
    public:
        TensorCreator();
        bool setRGBImg(std::vector<cv::Mat>& imgs);
        bool setDarkImg(std::vector<cv::Mat>& imgs);
        bool setSliceImg(std::vector<cv::Mat>& imgs);
        void processTensor();
        at::Tensor getInput1();
        at::Tensor getInput2();
    private:
        at::Tensor tensor;
        std::vector<cv::Mat> rgb_imgs;
        std::vector<cv::Mat> dark_imgs;
        std::vector<cv::Mat> slice_imgs;
        at::Tensor input_1;
        at::Tensor input_2;
};

#endif