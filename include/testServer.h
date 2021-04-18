#ifndef TESTSERVER_H_
#define TESTSERVER_H_
/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2021-04-01 18:03:05
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-18 23:55:46
 */
#include "my_common.h"





using namespace std;

#define INVALID_SOCKET -1
#define FILENAME "setting.txt"
#define OUTPUTFILENAME "output.txt"

class testServer
{
public:
    testServer(void);
    ~testServer(void);

    bool readSocketParam(std::string fileName);
    bool listenClient(void);
    bool disconnectListen(void);
    void setCamid();
    bool receiveData(void);
    bool outputDataProcessing();
    img_instance returnImginstance();

protected:
    int s_socket_fd;
    int cam_id;
    std::string ipAddr;
    uint16_t portNum;
    char r_buf[IMAGE_SIZE];
    std::string oustr;
    img_instance t_instance;

};

#endif
