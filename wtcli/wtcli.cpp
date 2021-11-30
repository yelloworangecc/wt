#include <Ws2tcpip.h>
#include <cstring>
#include "../shared/SimpleUdp.h"
#include "../shared/Callback.h"
#include "../shared/command.h"
#include "../shared/ConfigureReader.h"
#include <iostream>
#include <windows.h>
#include <string>

class CBFill : public Callback
{
public:
    CBFill(unsigned char _cmd, char* _data):cmd(_cmd),data(_data){}
    ~CBFill(){}
    virtual void operator()(char*pbuffer,int* psize) override
    {
		pbuffer[0] = (char)cmd;
		if (data != nullptr) 
		{
			strcpy(pbuffer+1,data);
			*psize = 1 + strlen(data);
		}
		else 
		{
			pbuffer[1] = '\0';
			*psize = 1;
		}
    }
private:
	unsigned char cmd;
	char* data;
};

int main(int argc,char*argv[])
{
	ConfigureReader conf("E:\\wt\\build\\wtcli\\Debug\\wt.json");
	std::string ip;
	int port;
	conf.getOptionValue("browser.ip", ip);
	conf.getOptionValue("browser.port", port);

	std::cout << ip <<' '<< port << std::endl;
    SimpleUdp udpSender;
    sockaddr_in6 name;
    memset(&name,0,sizeof (name)); //without this you will get WSAEADDRNOTAVAIL
    name.sin6_family = AF_INET6;
    inet_pton(AF_INET6,ip.c_str(),(PVOID)&name.sin6_addr);
    name.sin6_port = htons(port);
	
    CBFill cbFillHide(BROWSER_HIDE,nullptr);
    udpSender.sendToPeer(&name,&cbFillHide);
	
	Sleep(1000);
	
    CBFill cbFillShow(BROWSER_SHOW,nullptr);
	udpSender.sendToPeer(&name,&cbFillShow);
	
    return 0;
}
