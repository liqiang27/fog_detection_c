#include "fcnet_process.h"
#include "torch/torch.h"
#include <memory>

using namespace std;
using namespace at;

FC_Processor::FC_Processor(){

}

void FC_Processor::init(){

}

void FC_Processor::set_input(Tensor input_1, Tensor input_2) {
    data_1 = input_1.permute({0, 3, 1, 2});
    inputs_1.push_back(data_1.to(at::kCUDA));
    data_2 = input_1.permute({0, 3, 1, 2});
    inputs_1.push_back(data_2.to(kCUDA));
}

vector<int> FC_Processor::get_result() {

}

void FC_Processor::fc_process() {
    torch::jit::script::Module module = torch::jit::load(*model_name);
    module.to(at::kCUDA);
    output = module.forward(inputs_1).toTensor();
}

void FC_Processor::set_model(const char* model_name){
    this->model_name = new string(model_name);
}

