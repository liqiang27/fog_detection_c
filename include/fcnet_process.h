#ifndef FCNET_PROCESS_H_
#define FCNET_PROCESS_H_

#include <iostream>
#include <vector>
#include <torch/script.h>
#include <ATen/ATen.h>

class FC_Processor{
    public:
        FC_Processor();
        void init();
        void fc_process();
        void set_model(const char* model_name);
        void set_input(at::Tensor input_1, at::Tensor input_2);
        std::vector<int> get_result();
    
    private:
        at::Tensor data_1;
        at::Tensor data_2;
        std::vector<int> result;
        std::string* model_name;
        at::Tensor output;
        std::vector<torch::jit::IValue> inputs_1;
        std::vector<torch::jit::IValue> inputs_2;
};

#endif
