#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_
/*
 * @Descripttion:  Capture image from HikSDK
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:20:20
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:18:39
 */

#include <queue>
#include <mutex>
#include "my_common.h"
#include "testServer.h"


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

#endif




