/*
 * @Descripttion: 
 * @version: 
 * @Author: Lstron
 * @Date: 2021-04-01 18:03:24
 * @LastEditors: Lstron
 * @LastEditTime: 2021-04-01 18:42:49
 */

#include "testServer.h"

/*
 *  @brief Contructor
 */
testServer::testServer(void)
{
	s_socket_fd = INVALID_SOCKET;
	ipAddr = "";
    portNum = 0;
    memset(r_buf, 0 , (size_t)IMAGE_SIZE);
	oustr = "";

}

/*
 *  @brief Destructor
 */
testServer::~testServer(void){}

/*
 *  @brief read setting file(load socket param) 
 *  @param [in] FileName
 *  @return[in] result (ture:success  false:failure)
 */
bool testServer::readSocketParam(std::string FileName)
{
    ifstream input(FileName.c_str());
	std::string line;
    std::vector<string> IPinfo;

	if(!input) 
	{ 
		ipAddr = "";
        portNum = 0;
        cout <<"load file error : error = no such file" << endl;
        return false;
	}
	else 
	{
        input.seekg(0, ios::end);
        streampos fp = input.tellg(); 
        if(int(fp) == 0)
        {
            cout <<"read parameter error : error = file is empty" << endl;
            return false;
        }

        input.seekg(std::ios::beg);
        while (getline (input, line)) 
		{ 
            IPinfo.push_back(line);
		}
        ipAddr = IPinfo[0];
        portNum = static_cast<uint16_t>(std::stol(IPinfo[1]));
		if(portNum > 1023 && portNum < 65536)
		{
        	cout << "[load IPaddrs]:"<< ipAddr << endl;
        	cout << "[load portNum]:"<< portNum << endl;
        	return true;
		}
		else
		{
			cout <<"read parameter error : error = invlid port number" << endl;
			return false;	
		}
			
	}
}

/*
 *  @brief Listen for client requests  
 *  @return [in] result (ture:success  false:failure)
 */
bool testServer::listenClient(void)
{    
	// step1:构造通讯SOCKET	
    //AF_INET:ipv4; AF_INET6:ipv6
    if((s_socket_fd = socket(AF_INET, SOCK_STREAM,0)) == -1)
    {
        cout <<"create socket error,errno=" << errno << endl;
        return false;
    }
	else
		cout <<"create socket successed " << endl;

	// step2:绑定套接字到配置好的一个IP地址和一个端口上
    // 配置监听地址和端口
	struct sockaddr_in sAddr;
	memset(&sAddr, 0, sizeof(sAddr)); 
    sAddr.sin_family = AF_INET;
    sAddr.sin_addr.s_addr = inet_addr(ipAddr.c_str());
    sAddr.sin_port = htons(portNum);
	
	if(bind(s_socket_fd,(struct sockaddr *)&sAddr, sizeof(sAddr)) == -1)
	{
		cout <<"bind socket error,errno=" << errno << endl;
		return false;
	}
	else
		cout <<"bind socket successed " << endl;

	// step3:将套接字设置为监听模步等待连接请求
	if(listen(s_socket_fd, 2) == -1) 
	{
		cout <<"listen socket error,errno=" << errno << endl;
		return false;
	}
	else
	{
		cout<<"======= start listen ======="<<endl;
		return true;
	}
}

/*
 *  @brief disconnect listen
 *  @return [in] result (ture:success  false:failure)
 */
bool testServer::disconnectListen(void)
{
    if(s_socket_fd == INVALID_SOCKET)
    {
        cout << "Listen disconnected" << endl;
        return true; 
    }
    // 关闭相应的socket描述字
    if(close(s_socket_fd) != INVALID_SOCKET)
    {
        s_socket_fd = INVALID_SOCKET;
        cout << "Listen disconnected" << endl;
        return true;
    }
    else
    {
        cout << "disconnect Listen error,errno = " << errno << endl; 
        return false;
    }   
}

bool testServer::receiveData(void)
{
	int new_socket_fd;
	struct sockaddr_in cAddr;
	socklen_t clen  = sizeof(cAddr);
	memset(r_buf, 0 , (size_t)SIZE);//清空缓冲区的内容

	// step4:请求到来后，接受连接请求，返回一个新的对应于此次连接的套接字"new_socket_fd"
	cout << "listening..." << endl;
	if((new_socket_fd = accept(s_socket_fd,(struct sockaddr*)&cAddr,&clen)) == -1)
	{
		cout << "accept error,errno = " << errno << endl;
		return false;
	}
	else
	{
		cout << "listened to the client" << endl;
	}
		
	// 用返回的套接字和客户端进行通信
	if(recv(new_socket_fd, r_buf, (size_t)SIZE, 0) == -1){
		cout << "receive failed : receive function error" << endl;
		return false;
	} 
	else
	{
		cout << "received data : <" << r_buf << ">" << endl;
	}
	close(new_socket_fd); 
	return true;
}

/*
 *  @brief processing the data to be sent
 *  @return [in] result (ture:success  false:failure)
 */
bool testServer::outputDataProcessing(void)
{
	std::string times, hostName, recvData;
	
	// get timestamp
	time_t timep;
    time (&timep);
	char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y/%m/%d %H:%M:%S",localtime(&timep));
	times = timestamp;
	if(times == "")
	{
		cout << "data processing error:[time] is empty" << endl;
		return false;
	}
	
	// get host name
	char name[64];
	gethostname(name, sizeof(name));
	hostName = name;
	if(hostName == "")
	{
		cout << "data processing error:[hostName] is empty" << endl;
		return false;
	}

	// get recv data
	cv::revImg = char2Mat(r_buf);
    t_instance.cam_id = cam_id;
    t_instance.img = revImg.clone();
    t_instance.times = times;

}

cv::Mat testServer::outputDataProcessing() {
    std::string img_id = createID(cam_id);
    std::string img_name = g_imgpath + img_id;
    cv::Mat t_img = char2Mat(r_buf);
    cv::imwrite(img_name, t_img);
    return t_img;
}

void testServer::setCamid(int cam_id) {
    this->cam_id = cam_id;
}

img_instance testServer::returnImginstance () {
    return t_instance;
}

/***********************  main  **************************/


// int main()
// {
// 	testServer tcpServer;

// 	if(tcpServer.readSocketParam(FILENAME))
// 	{
// 		if(tcpServer.listenClient())
// 		{
// 			while (1)
// 			{
// 				if(tcpServer.receiveData())
// 				{
// 					if(tcpServer.outputDataProcessing())
// 					{
// 						tcpServer.writeFile(OUTPUTFILENAME);
// 					}
// 					else
// 						continue;
// 				}
// 				else
// 					break;
// 			}
// 		}
// 		else
// 			cout << " run [func: listenClient] fail" << endl;
// 	}
// 	else
// 		cout << " run [func: readSocketParam] fail" << endl;

// 	tcpServer.disconnectListen();
//     return 0;
// }

// g++ -Wall -o server test_server.cpp -std=c++11 -lpthread

