#include <iostream>
#include <fstream>
#include "opencv2/opencv.hpp"
#include "boost/filesystem.hpp"
#include "get_darkchanel.h"

#include "boost/algorithm/string.hpp"


using namespace std;
int main(int argc, char** argv) {
    if(argc < 4) {
        return 1;
    }

    string data_path(argv[1]);
    string txt_file(argv[2]);
    string dst_path(argv[3]);

    string line;
    ifstream file(txt_file);
    darkChanel* object = new darkChanel();
    while(getline(file, line)) {
        vector <string> fields;
        boost::algorithm::split(
            fields,
            line,
            boost::is_any_of("/"), 
            boost::algorithm::token_compress_mode_type::token_compress_on);
        string img_path = line;
        object->readImg(img_path.c_str());
        object->getDarkchanel();
        cv::Mat img = object->getDarkchanel_img();
        cv::imwrite(dst_path + "/" + *(fields.rbegin()), img);
    }
    return 0;
}