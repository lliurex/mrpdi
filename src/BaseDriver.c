
#include "BaseDriver.h"
#include <iostream>

using namespace std;

const char * name="BaseDriver";
unsigned int supportedDevices [] = {0xdeadbeef,0xffffffff};/*use 0xffffffff for eof*/
const char * deviceNames [] = {"Unnamed device"};

void init(unsigned int device)
{
	cout<<"base driver init()"<<endl;
}

void run()
{
	cout<<"base driver run()"<<endl;
}

int is_running()
{
	cout<<"base driver is_running()"<<endl;
	return 0;
}

void shutdown()
{
	cout<<"base driver shutdown()"<<endl;
}


