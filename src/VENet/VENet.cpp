/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2021-03-25 19:18:15
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-02 19:55:42
 */

#include "VENet.h"
#include "testModule.h"
#include "torch/torch.h"
#include <memory>

using namespace std;
using namespace at;

VENet_Processor::FC_Processor(){

}

void VENet_Processor::init(int gpu_id){
    if(!checkGPU()) {
        return;
    }
    cudaSetDevice(gpu_id);
    module = torch::jit::load(*model_name);
    module.to(at::kCUDA);
}

void VENet_Processor::set_input_2(Tensor input_1, Tensor input_2) {
    at::Tensor data_1 = input_1.permute({0, 3, 1, 2});
    inputs.push_back(data_1.to(at::kCUDA));
    at::Tensor data_2 = input_2.permute({0, 3, 1, 2});
    inputs.push_back(data_2.to(at::kCUDA));
}

void VENet_Processor::set_input_1(Tensor input_1) {
    at::Tensor data_1 = input_1.permute({0, 3, 1, 2});
    inputs.push_back(data_1.to(at::kCUDA));
}

vector<result_format> VENet_Processor::get_result() {
    this->modelProcess();

}

void VENet_Processor::modelProcess() {
    this->output = module.forward(inputs_1).toTensor();
}

void VENet_Processor::set_model(const char* model_name){
    this->model_name = new string(model_name);
}
