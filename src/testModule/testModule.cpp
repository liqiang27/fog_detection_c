/*
 * @Descripttion: Test whether the database transmission,
 *             image information connection and GPU are normal.
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-24 23:28:25
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:19:00
 */
#include <pqxx/pqxx>
#include "cuda_runtime.h"

#include "testModule.h"


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

