#include "SimpleUdp.h"
#include "Callback.h"

Callback* SimpleUdp::pCallback = nullptr;

SimpleUdp::SimpleUdp()
    :dp(INVALID_SOCKET),errorat(ERROR_NO),errorno(0)
{
    WSADATA wdata = {0};

	if (WSAStartup(MAKEWORD(2,2), &wdata) == 0)
	{
		dp = socket(AF_INET6,SOCK_DGRAM,0);
		if (dp != INVALID_SOCKET) pb = new char[DEFAULT_BUFFER_SIZE];
		else errorat = ERROR_CREATE,errorno = WSAGetLastError();
	}
	else
	{
		errorat = ERROR_CREATE,errorno = WSAGetLastError();
	}
}

void SimpleUdp::bindPort(int port)
{
	sockaddr_in6 name;
	memset(&name,0,sizeof (name)); //without this you will get WSAEADDRNOTAVAIL

	if (!isValid()) return;
	name.sin6_family = AF_INET6;
    name.sin6_addr = in6addr_any;
    name.sin6_port = htons(port);

	int iret = bind(dp, (SOCKADDR*)&name, sizeof (name));
	if (iret != 0) errorat = ERROR_BIND,errorno = WSAGetLastError();
}

void SimpleUdp::sendToPeer(sockaddr_in6* pname, Callback* pcbFill)
{
	if (!isValid()) return;
	
	if (pname != nullptr) peer = *pname;
	int isend = DEFAULT_BUFFER_SIZE;
	(*pcbFill)(pb,&isend);
	isend = sendto(dp, pb, isend, 0, (SOCKADDR *) &peer, sizeof (peer));
	if (isend < 0 ) errorat = ERROR_SEND,errorno = WSAGetLastError();
}

DWORD SimpleUdp::recvFunc(void* pvoid)
{
	int ilen = sizeof(peer);
	int irecv = 0;
	SimpleUdp* pinstance = reinterpret_cast<SimpleUdp*>(pvoid);
	while (true)
	{
		irecv = recvfrom(pinstance->dp, pinstance->pb, DEFAULT_BUFFER_SIZE, 0, (SOCKADDR *) &(pinstance->peer), &ilen);
		if (irecv > 0) (*SimpleUdp::pCallback)(pinstance->pb,&irecv);
	}
	return 0;
}

void SimpleUdp::startRecvProc(Callback* pcbFetch)
{
	pCallback = pcbFetch;
	CreateThread(NULL, 0, SimpleUdp::recvFunc, (void*)this, 0, NULL);
}

SimpleUdp::~SimpleUdp()
{
	if (errorat != ERROR_CREATE) closesocket(dp);
	WSACleanup();
	delete [] pb;
}

