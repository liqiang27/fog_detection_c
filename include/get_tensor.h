/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2020-10-29 01:47:08
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:19:25
 */
#ifndef GET_TENSOR_H_
#define GET_TENSOR_H_


#include "my_common.h"
#include <torch/script.h>
#include <ATen/ATen.h>


class TensorCreator{
    public:
        TensorCreator();
        bool setRGBImg(IMGS& imgs);
        bool setDarkImg(IMGS& imgs);
        bool setSliceImg(IMGS& imgs);
        bool setIMGS(IMGS &imgs);
        void setBatchsize(int batchsize = 1);
        void processTensor();
        at::Tensor getInput1();
        at::Tensor getInput2();
    private:
        at::Tensor tensor;
        IMGS rgb_imgs;
        IMGS dark_imgs;
        IMGS slice_imgs;
        int batchsize;
        at::Tensor input_1;
        at::Tensor input_2;
};

#endif