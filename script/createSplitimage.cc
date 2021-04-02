#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"

#include "get_slice.h"

#include "boost/algorithm/string.hpp"


using namespace std;
int main(int argc, char** argv) {
    if(argc < 4) {
        cout << "参数不足" << endl;
        return 1;
    }

    string data_path(argv[1]);
    string txt_file(argv[2]);
    string dst_path(argv[3]);

    string line;
    ifstream file(txt_file);
    Slicer* object = new Slicer();
    while(getline(file, line)) {
       vector <string> fields;
        boost::algorithm::split(
            fields,
            line,
            boost::is_any_of("/"), 
            boost::algorithm::token_compress_mode_type::token_compress_on
        );
        string img_path = line;
        cv::Mat src_img = cv::imread(img_path.c_str());
        object->setImg(src_img);
        object->sliceProcess();
        cv::Mat img = object->getSliceimg();
        cv::imwrite(dst_path + "/" + *(fields.rbegin()), img);
    }
    return 0;
}