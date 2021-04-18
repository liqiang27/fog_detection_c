#include <memory.h>
#include <pthread.h>

#include "my_common.h"
#include "testServer.h"
#include "taskQueue.h"
#include "testModule.h"
#include "imgPreprocess.h"
#include "get_tensor.h"
#include "VENet.h"
#include "writeDatabase.
#include "readConfig.h"

using namespace std;

/*
 * @Descripttion: The main program of fog visibility estimation system.
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2020-12-26 01:22:36
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 22:25:28
 */

//global variable
taskQueue<img_instance> g_task_queue;
taskQueue<result_format> g_result_queue;
const char* model_path = "";

//Checking every module whether it could connect to device.
void checkAllmodules() {
    for(int i = 0; i < CAMERA_NUMS; ++i) {
        if(!checkCamera(i)) return false;
    }
    if(!checkGPU()) return false;
    if(!checkDatabase()) return false;
    return true;
}

//capture image from server
void recvImg(void* args) {
    camera_info* param = (camera_info*)args;
    testServer t_server;
    t_server.setCamid(param->cam_id);
    if(!t_server.readSocketParam()) {
        printf("[ERRPR] read server params failed!\n");
        exit();
    }
    if(t_server.listenClient()) {
        while(1) {
            if(t_server.receiveData()) {
                if(t_server.outputDataProcessing()) {
                    g_task_queue.insertInstance(t_server.returnImginstance());
                }
            }
            else {
                printf("[ERROR]: Server recv img data failed!\n");
                break;
            }
        }
    }
    t_server.disconnectListen();
    return;
}

//write result to database
void writeResult(void* args) {
    std::unique_ptr<Database> t_database(new Database());
    t_database->set_database_param(g_database);
    const char* table_name = "";
    
    //连接数据库
    if(!t_database->connect()) {
        printf("[ERROR]: connect database failed!\n");
        exit();
    }
    while(1) {
        if(g_result_queue.getSize() >= 20) {
            std::vector<result_format> result_list;
            for(int i= 0; i < 20; i++) {
                result_list.push_back(g_result_queue.getInstance());
            }
            t_database->write_result(result_list);
        }
    }
}

//VENet process
void singleThread() {
    std::unique_ptr<imgProcessor> t_processor(new imgProcessor();
    std::unique_ptr<TensorCreator> t_tensor_creator(new TensorCreator());
    std::unique_ptr<VENet_Processor> t_venet(new VENet_Processor());

    //载入模型并初始化
    t_venet->set_model(model_path);
    t_venet->init();
    while(1) {
        //从taskQueue中获取图像
        img_instance t_img  = g_task_queue.getInstance();
        
        //进行图像预处理
        t_processor->setImage(t_img.img);
        //t_processor->setMode(1); //设置获取slice_img
        IMGS t_imglist = t_processor->getImg();

        //获取tensor
        t_tensor_creator->setIMGS(t_imglist);
        at::Tensor global_feature = t_tensor_creator->getInput1();
        
        //使用VENet进行处理
        t_venet->set_input_1(global_feature);
        auto result = t_venet->get_result();
        g_task_queue.insertInstance(result);
    }
}

int main(int argc, char* argv[]) {
    //获取配置参数
    if(!checkConfigfile()) {
        exit();
    }
    readConfig();

    //测试连接
    if(!checkAllmodules()){
        exit();
    }
    
    pthread_t server_thread;
    pthread_t process_thread;
    pthread_t database_thread;

    int ret1 = pthread_create(&server_thread, NULL, recvImg, void*);
    int ret2 = pthread_create(&process_thread, NULL, singleThread, void*);
    int ret2 = pthread_create(&database_thread, NULL, writeResult, void*);

    pthread_join(server_thread);
    pthread_join(process_thread);
    pthread_join(database_thread);
    
    return 0;
}




