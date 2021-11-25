#include <Ws2tcpip.h>
#include <iostream>
#include "../shared/SimpleUdp.h"
#include "../shared/Callback.h"

class CBFill : public Callback
{
public:
    CBFill(){};
    ~CBFill(){};
    void operator()(char*data,int size)
    {
	strcpy(data,"hello");
    }
};

int main(int argc,char*argv[])
{
    SimpleUdp udpSender;
    CBFill cbFill;
    sockaddr_in6 name;
    memset(&name,0,sizeof (name)); //without this you will get WSAEADDRNOTAVAIL
    name.sin6_family = AF_INET6;
    name.sin6_addr = in6addr_loopback;
    name.sin6_port = htons(8081);
    udpSender.sendToPeer(&name,&cbFill);
  
    return 0;
}
