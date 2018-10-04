


#ifndef _MRPDI_UTILS_
#define _MRPDI_UTILS_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "BaseDriver.h"

namespace net
{
	namespace lliurex
	{
		namespace mrpdi
		{
			class Utils
			{
				public:
				static unsigned char get_iface(unsigned int id,driver_device_info * supported_devices);
				static void build_path(unsigned int address,unsigned char iface,char * out);
				static void inverse_interpolation(float x,float y,float * calibration,float * u,float * v);
				static int iabs(int v);
				static int ipow(int v,int n);
			
			};
			
			class CalibrationScreen
			{
				private:
					Display *dis;
					Window win;
					Screen * scr;
					GC gc;
					int width;
					int height;
					
					static CalibrationScreen * instance;
					
					CalibrationScreen();
					~CalibrationScreen();
					
					
				
				public:
				
					static CalibrationScreen * get_CalibrationScreen();
					static void destroy();
				
					void step(int p);
				
			};
		}
	}

}



#endif
