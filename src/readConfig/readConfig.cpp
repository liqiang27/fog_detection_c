/*
 * @Descripttion:  read config.json
 * @version: v1.0
 * @Author: lstron
 * @Date: 2021-03-24 20:29:14
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 15:50:24
 */

#include<jsoncpp/json/json.h>
#include "readConfig.h"

bool checkConfigfile() {
    char* file_name = "../../config.json";
    if(access(file_name, 0) == -1) {
        printf("[ERROR] : The config file is not exists!");
        return false;
    }
    return true;
}

bool readConfig() {
    Json::Reader reader;
    Json::Value root;
    
    std::ifstream in("../../config.json", std::ios::binary);
    if(!in.is_open()) {
        printf("[ERROR]: Open config.json failed!");
        return false;
    }
    
    if(reader.parse(in, root)) {
        g_imgpath = root["IMG_PATH"].asString();
        g_modelchoose = root["MODEL_CHOOSE"].asInt();
        g_maxthread = root["MAX_THREADS"].asInt();

        g_database.db_name = root["DATABASE"]["db_name"].asString();
        g_database.host_address = root["DATABASE"]["host_address"].asString();
        g_database.password = root["DATABASE"]["password"].asString();
        g_database.port = root["DATABASE"]["port"].asString();
        g_database.user = root["DATABASE"]["user"].asString();

        
        for(int i = 0; i<=CAMERA_NUMS; i++) {
            char cam_name[10];
            memset(cam_name, 0, 10);
            sprintf(cam_name, "cam0%d", i);
            g_caminfo[i].cam_ip = root["CAMERAS"][cam_name]["IP"].asString();
            g_caminfo[i].user_name = root["CAMERAS"][cam_name]["User"].asString();
            g_caminfo[i].password = root["CAMERAS"][cam_name]["Password"].asString();
            g_caminfo[i].is_open = root["CAMERAS"][cam_name]["Available"].asBool();
        }

        for(int i = 0; i < MODEL_NUMS; i++) {
            char model_name[10];
            memset(model_name, 0, 10);
            sprintf(model_name, "model0%d", i);
            g_modelinfo[i].model_path = root["MODELS"][model_name]["path"].asString();
            g_modelinfo[i].discription = root["MODELS"][model_name]["discription"].asString();
        }
    }
    else {
        printf("[ERROR]:Parsing json file failed!\n");
        return false;
    }

    printf("[SUCCESS]: read config.json success!\n");
    return true;
}

