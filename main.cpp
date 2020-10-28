#include <iostream>
#include <memory>
#include <stdlib.h>
#include "get_slice.h"
#include "get_darkchanel.h"
#include "get_tensor.h"

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
    if (argc != 3){
        cerr << "usage: example-app <path-to-exported-script-module>\n";
	    return -1;
    }
    std::unique_ptr<darkChanel>dark_object(new darkChanel());
    std::unique_ptr<Slicer> slice_object(new Slicer());
    std::unique_ptr<TensorCreator> tensor_object(new TensorCreator());


    Mat img = imread(argv[1]); 
    string model_path(argv[2]);

    cout << "create object success!" << endl;
    dark_object->setImg(img);
    dark_object->getDarkchanel();
    Mat dark_img =  dark_object->getDarkchanel_img().clone();
    cout << "create dark_channel_img success!" << endl;
    Mat img2 = imread(argv[1]); 
    slice_object->setImg(img2);
    slice_object->sliceProcess();
    Mat slice_img = slice_object->getSliceimg().clone();

    Mat rgb_img;
    Mat img3 = imread(argv[1]); 
    resize(img3, rgb_img, cv::Size(448, 448));

    vector<Mat> rgb_imgs, dark_imgs, slice_imgs;

    for(int i = 0; i < 32; ++i) {
        rgb_imgs.emplace_back(rgb_img);
        dark_imgs.emplace_back(dark_imgs);
        slice_imgs.emplace_back(slice_img);
    }

   tensor_object->setDarkImg(dark_imgs);
   tensor_object->setRGBImg(rgb_imgs);
   tensor_object->setSliceImg(slice_imgs);

   tensor_object->processTensor();
   cout << tensor_object->getInput1().size<< endl;
   cout << tensor_object->getInput2().size << endl;

   torch::jit::script::Module module;
   try {
       module = torch::jit::load(model_path);
   }
   catch(const c10::Error& e) {
       cerr << "error loading the model\n";
       return 1;
   }

   cout << "model load success!\n";

    vector <torch::jit::IValue> inputs1; 
    inputs1.push_back(tensor_object->getInput1().to(at::kCUDA));
    inputs1.push_back(tensor_object->getInput2().to(at::kCUDA));

    at::Tensor output = module.forward(inputs1).toTensor();
    std::cout << output.sizes() << std::endl;
    cout <<output.data.max_values(1)[1] << endl;


}