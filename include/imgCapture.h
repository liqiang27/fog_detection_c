#pragma once
/*
 * @Descripttion: Capture image from Hik camera.
 * @version: 
 * @Author: Lstron
 * @Date: 2021-03-25 19:16:59
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-31 16:25:03
 */

#include "my_common.h"
#include "testModule.h"
#include "readConfig.h"


class imgCapturer {
public:
    explicit imgCapturer(const int cam_id) {
        struLoginInfo = {0};
        struDeviceInfoV40 = {0};
        this->cam_id = cam_id;
        raw_img = new char[IMAGE_SIZE];
    }
    ~imgCapturer();
    cv::Mat captureImgWithoutsave();
    cv::Mat captureImgWithsave();
    bool captureImgOnlysave();
    bool connectCamera();
private:

    char* raw_img;
    int cam_id;
    long lUserID;
    NET_DVR_USER_LOGIN_INFO struLoginInfo;
    NET_DVR_DEVICEINFO_V40 struDeviceInfoV40;
};