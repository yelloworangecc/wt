#include <winsock2.h>
#include <Ws2tcpip.h>
class Callback;

#define DEFAULT_BUFFER_SIZE 1024

enum UdpErrorAt
{
	ERROR_NO = 0,
	ERROR_CREATE,
	ERROR_BIND,
	ERROR_SEND
};

class SimpleUdp
{
public:
	SimpleUdp();
	~SimpleUdp();
	bool isValid(){return errorat == ERROR_NO;}
	UdpErrorAt getErrorAt(){return errorat;}
	int getErrorNo(){return errorno;}
	void bindPort(int port);
	void sendToPeer(sockaddr_in6* pname, Callback* pcbFill);
	static DWORD recvFunc(void* pvoid);
	void startRecvProc(Callback* pcbFetch);

	static Callback* pCallback;
private:
	SOCKET dp;//socket descriptor
	char * pb;//point to buffer
	sockaddr_in6 peer;//peer address
	UdpErrorAt errorat;//error at
	int errorno;//return value sock2
};
