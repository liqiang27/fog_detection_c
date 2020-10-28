#include <torch/script.h> //one-stop header

#include <string>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <memory>

using namespace std;
using namespace cv;
int main(int argc, const char* argv[]){
    if (argc != 2){
        cerr << "usage: example-app <path-to-exported-script-module>\n";
	    return -1;
    }
    torch::jit::script::Module module;
    try{
        // Deserialize the scriptmodule from a file using torch::jit::load().
        module = torch::jit::load(argv[1]);
    }
    catch(const c10::Error& e){
        cerr << "error loading the model\n";
	return -1;
    }
    std::cout << "model load ok\n";
    // load image with opencv and transform.
    // 1. read image
    std::string img_name("../RGB/2019-08-10-15-13-10000.jpg");
    cv::Mat image = imread(img_name);
    // 2. convert color space, opencv read the image in BGR
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::Mat img_float;
    // convert to float format
    image.convertTo(img_float, CV_32F, 1.0/255);
    // 3. resize the image for resnet101 model
    cv::resize(img_float, img_float, cv::Size(224, 224),cv::INTER_AREA);
    // 4. transform to tensor
    auto img_tensor = torch::from_blob(img_float.data, {1,224,224,3},torch::kFloat32);
    // in pytorch, batch first, then channel
    img_tensor = img_tensor.permute({0,3,1,2}); 
    // 5. Removing mean values of the RGB channels
    // the values are from following link.
    // https://github.com/pytorch/examples/blob/master/imagenet/main.py#L202
    img_tensor[0][0] = img_tensor[0][0].sub_(0.485).div_(0.229);
    img_tensor[0][1] = img_tensor[0][1].sub_(0.456).div_(0.224);
    img_tensor[0][2] = img_tensor[0][2].sub_(0.406).div_(0.225);
    
    // Create vectors of inputs.
    std::vector<torch::jit::IValue> inputs1, inputs2;
    inputs1.push_back(torch::ones({1,3,224,224}));
    inputs2.push_back(img_tensor);
    
    // 6. Execute the model and turn its output into a tensor
    at::Tensor output = module.forward(inputs2).toTensor();
    std::cout << output.sizes() << std::endl;
    std::cout << output.slice(/*dim=*/1,/*start=*/0,/*end=*/3) << '\n';

    // // 7. Load labels
    // std::string label_file = "../synset_words.txt";
    // std::ifstream rf(label_file.c_str());
    // CHECK(rf) << "Unable to open labels file" << label_file;
    // std::string line;
    // std::vector<std::string> labels;
    // while(std::getline(rf, line)){labels.push_back(line);}
    
    // // 8. print predicted top-3 labels
    // std::tuple<torch::Tensor, torch::Tensor> result = output.sort(-1, true);
    // torch::Tensor top_scores = std::get<0>(result)[0];
    // torch::Tensor top_idxs = std::get<1>(result)[0].toType(torch::kInt32);
    
    // auto top_scores_a = top_scores.accessor<float, 1>();
    // auto top_idxs_a = top_idxs.accessor<int, 1>();
    // for(int i=0; i<3;i++){
    //     int idx = top_idxs_a[i];
	  //   std::cout << "top-" << i+1 << " label: ";
	  //   std::cout << labels[idx] << ",score: " << top_scores_a[i] << std::endl;
    // }
    return 0;
}
