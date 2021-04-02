#pragma once
/*
 * @Descripttion:  Capture image from HikSDK
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:20:20
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-02 20:11:37
 */


#include "my_common.h"
#include "testServer.h"
#include <queue.h>
#include <mutex>

template<class T>
class taskQueue {
public:
    taskQueue();
    ~taskQueue();
    bool insertInstance(img_instance t_instance);
    bool getInstance(img_instance& t_instance);
    int getSize();
private:
    std::queue<T> t_queue;
    std::mutex t_mutex;
};



