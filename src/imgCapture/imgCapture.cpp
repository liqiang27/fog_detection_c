/*
 * @Descripttion: Capture image from HikSDK
 * @version: v1.0
 * @Author: Lstron
 * @Date: 2021-03-25 19:17:14
 * @LastEditors: Lstron
 * @LastEditTime: 2021-03-29 16:20:09
 */

#include "imgCapture.h"
#include "HK_Camera/incCn/HCNetSDK.h"

imgCapturer::~imgCapturer() {
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();
    delete raw_img;
}

bool imgCapturer::connectCamera() {
     if(g_caminfo[cam_id].is_open == false) {
        printf("[ERROR]: The camera %d is not open!\n", cam_id);
        return false;
    }
    NET_DVR_Init();
    
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
    printf("[SUCCESS] pyd1---Login success!\n");
    return true;
}

cv::Mat imgCapturer::captureImgWithoutsave() {
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 0;
    strPicPara.wPicSize = 9;
    bool iRet2;
    memset(raw_img, 0, IMAGE_SIZE);
    LPDWORD tmp;
    iRet2 = NET_DVR_CaptureJPEGPicture_NEW(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, raw_img, IMAGE_SIZE, tmp);
    if(iRet2) {
        cv::Mat image = char2Mat(raw_img);
        return image;
    }
    else {
        printf("[ERROR]: Capture image failed!");
        return cv::Mat();
    }
}

cv::Mat imgCapturer::captureImgWithsave()  {
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 0;
    strPicPara.wPicSize = 9;
    bool iRet2;
    memset(raw_img, 0, IMAGE_SIZE);
    LPDWORD tmp;
    iRet2 = NET_DVR_CaptureJPEGPicture_NEW(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, raw_img, IMAGE_SIZE, tmp);
    if(iRet2) {
        cv::Mat image = char2Mat(raw_img);
        std::string img_id = createID(cam_id);
        std::string img_name = g_imgpath +  img_id+ ".jpg";
        cv::imwrite(img_name, image);
        return image;
    }
    else {
        printf("[ERROR]: Capture image failed!");
        return cv::Mat();
    }
}

bool imgCapturer::captureImgOnlysave() {
    NET_DVR_JPEGPARA strPicPara = {0};
    strPicPara.wPicQuality = 2;
    strPicPara.wPicSize = 9;
    bool iRet;
    std::string img_id = createID(cam_id);
    std::string img_name = g_imgpath +  img_id+ ".jpeg";
    iRet = NET_DVR_CaptureJPEGPicture(lUserID, struDeviceInfoV40.struDeviceV30.byStartChan, &strPicPara, img_name.c_str());
    if (!iRet)
    {
        printf("[ERROR] pyd1---NET_DVR_CaptureJPEGPicture error, %d\n", NET_DVR_GetLastError());
        return false;
    }
    return true;
}


