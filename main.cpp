/*
 * @Descripttion: The main program of fog visibility estimation system.
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2020-12-26 01:22:36
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-01 18:44:32
 */

#include "my_common.h"
#include "testServer.h"
#include "testModule.h"
#include "imgCapture.h"
#include "imgPreprocess.h"
#include "get_tensor.h"
#include "VENet.h"
#include "writeDatabase.h"
#include "readConfig.h"

//Checking every module whether it could connect to device.
void checkAllmodules() {
    for(int i = 0; i < CAMERA_NUMS; ++i) {
        if(!checkCamera(i)) return false;
    }
    if(!checkGPU()) return false;
    if(!checkDatabase()) return false;
    return true;
}

void singleThread() {
    std::unique_ptr<imgCapturer> t_imgcapture(new imgCapturer());
    std::unique_ptr<imgProcessor> t_processor(new imgProcessor())��
    std::unique_ptr<Database> t_database(new Database());
    std::unique_ptr<VENet_Processor> t_venet(new VENet_Processor());
    
    //���������
    if(!t_imgcapture->connectCamera()) {
        printf("[ERROR]: connect camera failed!\n");
        exit();
    }

    //�������ݿ�
    if(!t_database->connect()) {
        printf("[ERROR]: connect database failed!\n");
        exit();
    }

    

    
}

int main(int argc, char* argv[]) {
    //��ȡ���ò���
    if(!checkConfigfile()) {
        exit();
    }
    readConfig();

    //��������
    if(!checkAllmodules()){
        exit();
    }
    
    //�����豸
    imgCapturer* 
    
    

}




