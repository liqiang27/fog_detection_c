#include "torch/torch.h"
#include <iostream>

struct Net : torch::nn::Module {
    Net() {
        fc1 = register_module("fc1", torch::nn::Linear(784, 64));
        fc2 = register_module("fc2", torch::nn::Linear(64, 32));
        fc3 = register_module("fc3", torch::nn::Linear(32, 10));
    }

    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(fc1->forward(x.reshape({x.size(0), 784})) );
        x = torch::dropout(x, 0.5, 1);
        x = torch::relu(fc2->forward(x));
        x = torch::log_softmax(fc3->forward(x), 1);
        return x;
    }

    torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};

int main() {
    std::shared_ptr<struct Net> net = std::make_shared<Net>();
    // auto data_loader = torch::data::make_data_loader(
    //     torch::data::datasets::MNIST("../data").map(
    //         torch::data::transforms::Stack<>()
    //     ), 64
    // );
    // torch::optim::SGD optimizer(net->parameters(), 0.01);

    // for (size_t epoch = 1; epoch <= 10; ++epoch) {
    //     size_t batch_index = 0;
    //     for(auto& batch : *data_loader) {
    //         optimizer.zero_grad();
    //         torch::Tensor prediction = net->forward(batch.data);
    //         torch::Tensor loss = torch::nll_loss(prediction, batch.target);
    //         loss.backward();
    //         optimizer.step();

    //         if(++batch_index % 100 == 0) {
    //             std::cout << "Epoch: " << epoch << " | Batch: " << batch_index << " | Loss: " << loss.item<float>() << std::endl;
    //             torch::save(net, "net.pt");
    //         }
    //     }
    // }
}