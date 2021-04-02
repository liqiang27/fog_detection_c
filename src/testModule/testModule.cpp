/*
 * @Descripttion: Test whether the database transmission,
 *             image information connection and GPU are normal.
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-24 23:28:25
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-29 16:16:31
 */

#include "testModule.h"


bool checkCamera(const int cam_id) {
    if(g_caminfo[cam_id].is_open == false) {
        printf("[ERROR]: The camera %d is not open!\n", cam_id);
        return false;
    }
    NET_DVR_Init();
    long lUserID;
    //login
    NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};
    struLoginInfo.bUseAsynLogin = false;

    struLoginInfo.wPort = 8000;
    memcpy(struLoginInfo.sDeviceAddress, g_caminfo[cam_id].cam_ip.c_str(), NET_DVR_DEV_ADDRESS_MAX_LEN);
    memcpy(struLoginInfo.sUserName, g_caminfo[cam_id].user_name.c_str(), NAME_LEN);
    memcpy(struLoginInfo.sPassword, g_caminfo[cam_id].password.c_str(), NAME_LEN);

    lUserID = NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);

    if (lUserID < 0)
    {
        printf("[ERROR] pyd1---Login error, %d\n", NET_DVR_GetLastError());
        return false;
    }

    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 9;
    bool iRet;
    char img_path[128];
    memset(img_path, 0, 128);
    sprintf(img_path, "%s/test.jpeg", g_imgpath.c_str());
    iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, img_path);
    if (!iRet)
    {
        printf("[ERROR] pyd1---NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
        return false;
    }

    bool iRet2;
    char img[IMAGE_SIZE];
    memset(img, 0, IMAGE_SIZE);
    LPDWORD tmp;
    iRet2 = NET_DVR_CaptureJPEGPicture_NEW(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, img, IMAGE_SIZE, tmp);
    cv::Mat image = char2Mat(img);
    cv::imshow("test_img", image);
    cv::waitKey(0);
    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();

    return true;

}

bool checkDatabase() {
    pqxx::connection* my_conn;
    pqxx::work* my_work;

    char str[64];
    memset(str, 0, 64*sizeof(char));
    sprintf(str, "dbname=%s user=%s password=%s hostaddr=%s port=%s", g_database.db_name, g_database.user,g_database.password, g_database.host_address, g_database.port);
    my_conn = new pqxx::connection(str);
    if(my_conn->is_open()) {
        printf("[SUCCESS]: Open database success!\n");
        return true;
    }
    else {
        printf("[ERROE]: Open database failed!\n");
        return false;
    }
    my_conn->disconnect();
}

bool checkGPU() {
    cudaDeviceProp deviceProp;
    int deviceCount = 0;
    cudaError_t cudaError;
    cudaError = cudaGetDeviceCount(&deviceCount);
    if(cudaError != cudaSuccess) {
        printf("[ERROR] Get gpu device failed!\n");
        return false;
    }
    else {
        printf("[SUCCESS] : GET %d gpu servcie available!\n", deviceCount);
    }
    for(int i = 0; i < deviceCount; i++) {
        cudaError = cudaGetDeviceProperties(&deviceProp, i);
        if(cudaError != cudaSuccess) {
            printf("[ERROR] Get gpu device properties failed!\n");
            return false;
        }
        std::cout << "设备 " << i + 1 << " 的主要属性： " << std::endl;
		std::cout << "设备显卡型号： " << deviceProp.name << std::endl;
		std::cout << "设备全局内存总量（以MB为单位）： " << deviceProp.totalGlobalMem / 1024 / 1024 << std::endl;
		std::cout << "设备上一个线程块（Block）中可用的最大共享内存（以KB为单位）： " << deviceProp.sharedMemPerBlock / 1024 << std::endl;
		std::cout << "设备上一个线程块（Block）种可用的32位寄存器数量： " << deviceProp.regsPerBlock << std::endl;
		std::cout << "设备上一个线程块（Block）可包含的最大线程数量： " << deviceProp.maxThreadsPerBlock << std::endl;
		std::cout << "设备的计算功能集（Compute Capability）的版本号： " << deviceProp.major << "." << deviceProp.minor << std::endl;
		std::cout << "设备上多处理器的数量： " << deviceProp.multiProcessorCount << std::endl;
    }
    
        printf("[SUCCESS] Ckeck gpu device success!\n");
    return true;
}

