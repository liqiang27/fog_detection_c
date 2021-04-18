#ifndef VENET_H_
#define VENET_H_
/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2021-03-25 19:18:07
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:19:46
 */

#include "my_common.h"
#include <torch/script.h>
#include <ATen/ATen.h>

class VENet_Processor{
    public:
        VENet_Processor();
        void init(int gpu_id);
        void set_model(const char* model_name);
        void set_input(at::Tensor input_1, at::Tensor input_2);
        std::vector<result_format> get_result();
    
    private:

        void modelProcess();
        std::vector <torch::jit::IValue> inputs; 
        std::vector<int> result;
        std::string* model_name;
        at::Tensor output;
        torch::jit::script::Module module;
};

#endif
