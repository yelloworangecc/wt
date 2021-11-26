#ifndef _CALLBACK_H_
#define _CALLBACK_H_

class Callback
{
public:
	virtual void operator()(char* buffer, int* size) = 0;
};

#endif