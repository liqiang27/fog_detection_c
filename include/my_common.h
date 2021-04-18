#ifndef MY_COMMON_H_
#define MY_COMMON_H_
/*
 * @Descripttion: Some public tools function.
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-28 17:00:31
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-19 00:06:29
 */

#include <iostream>
#include "opencv2/opencv.hpp"

#define IMAGE_SIZE 6220800
#define CAMERA_NUMS 3
#define MODEL_NUMS 2


/**
 * camera info
 **/
typedef struct camera_info_{
    int cam_id;
    bool is_open;
    std::string cam_ip;
    std::string user_name;
    std::string password;
}camera_info;

/**
 * database info
**/
typedef struct database_info_{
    std::string db_name;
    std::string host_address;
    std::string password;
    std::string port;
    std::string user;
}database_info;

/**
 * model info
**/
typedef struct model_info_{
    std::string  model_path;
    std::string discription;
}model_info;

typedef struct result_format_
{
    std::string img_name;
    int fog_level;
    double visibility;
    result_format_& operator=(result_format_ t_result) {
        this->img_name.assign(t_result.img_name);
        this->fog_level = t_result.fog_level;
        this->visibility = t_result.visibility;
    }
}result_format;

typedef struct img_instance_{
    cv::Mat img;
    int cam_id;
    std::string times;
    img_instance_& operator=(img_instance_ t_instance) {
        this->cam_id = t_instance.cam_id;
        this->img  =t_instance.img.clone();
        this->times.assign(t_instance.times);
    };
}img_instance;

using IMGS = std::vector<cv::Mat>;
using IMGS_LIST = std::vector<std::vector<cv::Mat>>;


camera_info g_caminfo[CAMERA_NUMS]; 
database_info g_database;
model_info g_modelinfo[MODEL_NUMS];
std::string g_imgpath;
int g_modelchoose;
int g_maxthread;

/**
 * @name: 
 * @msg: 
 * @param {const int} cam_id
 * @return {*}
 */
std::string createID(const int cam_id);

/**
 * @name: 
 * @msg: 
 * @param {const int} IMAGE_SIZE
 * @return {*}
 */
cv::Mat char2Mat(char* modelImage);

/**
 * @name: getFilenames
 * @msg: Return all the files in a folder, and return in the form of absolute path
 * @param {const} std
 * @return {The number of filnames, filenames.size()}
 */
std::int getFilenames(const std::string& dir, std::vector<std::string>& filenames);


#endif