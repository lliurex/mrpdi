

#include <iostream>
#include <cstring>
#include <sstream>
#include <signal.h>
#include <cmath>
#include <mrpdi/Core.h>
#include <mrpdi/Input.h>
#include <mrpdi/BaseDriver.h>
#include <X11/Xlib.h>
#include "sandbox.hpp"
#include <unistd.h>

using namespace std;
using namespace net::lliurex::mrpdi;


bool quit_request=false;

void quit_handler(int sig)
{
	quit_request=true;
}

Sandbox::Sandbox()
{
		cout<<"[Sandbox]:Constructor"<<endl;
		vector<connected_device_info> list;
	
		core = new Core();
		core->init();
		core->set_input_handler(this);
		
		core->update_devices(&list);
		
		id=0;
		address=0;
		
		if(list.size()>0)
		{
			id = list[0].id;
			address = list[0].address;
			core->start(id,address);
			
			//smart dvit
			if(id==0x0b8c000e)
			{
				unsigned int ret;
				core->get_parameter(id,"dvit.method",&ret);
				cout<<"DViT driver is using method: "<<ret<<endl;
			}
		}
		
		dis = XOpenDisplay(NULL);
		win = XCreateSimpleWindow(dis, XDefaultRootWindow(dis), 0, 0, 600, 600, 0, WhitePixel (dis, 0), WhitePixel(dis, 0));
		XMapWindow(dis, win);
		gc= XCreateGC(dis, win, 0, NULL);
		
		px=0;
		py=0;
		c1=0;
		c2=0;
		angle1=0.0f;
		angle2=0.0f;
		width1=1;
		width2=2;
		
}
		
Sandbox::~Sandbox()
{
	cout<<"[Sandbox]:Destructor"<<endl;
	if(id!=0)
	{
		core->stop(id,address);
	}
	
	core->shutdown();
	
	delete core;
	
	XDestroyWindow(dis,win);
}

void Sandbox::refresh()
{
		XClearWindow(dis,win);
		
		XSetForeground(dis,gc,(unsigned long)0x00666666);
		XDrawLine(dis, win, gc, 200, 0, 200, 599);
		XDrawLine(dis, win, gc, 400, 0, 400, 599);
		
		XDrawLine(dis, win, gc, 0, 200, 599, 200);
		XDrawLine(dis, win, gc, 0, 400, 599, 400);
		
		XSetForeground(dis,gc,(unsigned long)0x00FF0000);
				
		
		XDrawLine(dis, win, gc, px, 0, px, 599);
		XDrawLine(dis, win, gc, 0, py, 599, py);
		
		//smart dvit
		if(id==0x0b8c000e)
		{
			float f;
			float c1x,c1y;
			float c2x,c2y;
			float w;
			
			
			
				
			f=c1/640.0;
			w=width1/640.0;
			XSetForeground(dis,gc,(unsigned long)0x0000FF00);
			XDrawLine(dis, win, gc, 600*f, 560, 600*f, 599);
			XDrawRectangle(dis,win,gc,600*(f-(w/2.0)),580,600*w,599);
			
			f=c2/640.0;
			w=width2/640.0;
			XSetForeground(dis,gc,(unsigned long)0x00FF00FF);
			XDrawLine(dis, win, gc, 600*f, 560, 600*f, 599);
			XDrawRectangle(dis,win,gc,600*(f-(w/2.0)),580,600*w,599);
			
			
			c1x = cos( (angle1)*M_PI/180.0 );
			c1y = sin( (angle1)*M_PI/180.0 );
			
			XSetForeground(dis,gc,(unsigned long)0x0000FF00);
			XDrawLine(dis, win, gc, 0, 0, c1x*800, c1y*800);
			
			c2x = cos( (angle2)*M_PI/180.0 );
			c2y = sin( (angle2)*M_PI/180.0 );
			
			XSetForeground(dis,gc,(unsigned long)0x00FF00FF);
			XDrawLine(dis, win, gc, 599, 0, 599-(c2x*800), c2y*800);
		}
		
		XFlush(dis);
}


void Sandbox::pointer_callback(driver_event event)
{
	
	
	switch(event.type)
	{
		case EVENT_POINTER:
			px = 600 * event.pointer.x;
			py = 600 * event.pointer.y;
			
			if(id==0x0b8c000e)
			{
				//v280 dimesions are:
				//156x118 cm
				cout<<"Table position: "<<(event.pointer.x * 156.0)<<","<<(event.pointer.y * 118.0)<<endl;
			
			}
			
			refresh();
			
		break;
		
		case EVENT_KEY:
			cout<<"event: key"<<endl;
		break;
		
		case EVENT_DATA:
			//cout<<"event: data"<<endl;
			
			//smart dvit
			if(id==0x0b8c000e)
			{
				
				
				switch(event.data.type)
				{
					case 1:
						c1=*((int *)(event.data.buffer));
						c2=*((int *)(event.data.buffer)+1);		
					break;
					
					case 2:
						angle1=*((float *)(event.data.buffer));
						angle2=*((float *)(event.data.buffer)+1);
					break;
					
					case 3:
						width1=*((int *)(event.data.buffer));
						width2=*((int *)(event.data.buffer)+1);		
					break;
					
				}
				
			}
			
		break;
		
		case EVENT_STATUS:
			cout<<"event: status"<<endl;
		break;
		
		default:
			cout<<"event: unknown"<<endl;
		
	}
}


void Sandbox::start(unsigned int id,unsigned int address)
{
}

void Sandbox::stop(unsigned int id,unsigned int address)
{
	
}

void Sandbox::calibrate(unsigned int address)
{
	
}


int main(int argc,char * argv[])
{
		
	Sandbox * sandbox;
	
	signal(SIGABRT,&quit_handler);
    signal(SIGTERM,&quit_handler);
	signal(SIGINT,&quit_handler);
	
	sandbox = new Sandbox();
    
	 while(!quit_request)
	 {
		 sleep(1);
	 }
	 
	 delete sandbox;
	return 0;
}
