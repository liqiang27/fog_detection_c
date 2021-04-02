/*
 * @Descripttion: Retain the img_instance.
 * @version: 
 * @Author: Lstron
 * @Date: 2021-03-25 19:20:32
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-02 20:11:56
 */

#include "taskQueue.h"
template<class T>
bool taskQueue::insertInstance(T t_instance){
    if(t_instance.img.empty()) {
        return false;
    }
    t_mutex.lock();
    t_queue.push(t_instance);
    t_mutex.unlock();
    return true;
}

bool taskQueue::getInstance(T& t_instance) {
    if(t_queue.empty())
    {
        return false;
    }
    t_mutex.lock();
    t_instance = t_queue.front();
    t_queue.pop();
    t_mutex.unlock()
    return true;
}

int taskQueue::getSize() {
    int size = 0;
    t_mutex.lock();
    size = t_queue.size();
    t_mutex.unlock();
    return size;
}




