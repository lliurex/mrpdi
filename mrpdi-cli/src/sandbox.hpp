
#include <mrpdi/Core.h>
#include <mrpdi/Input.h>
#include <mrpdi/BaseDriver.h>
#include <X11/Xlib.h>

using namespace net::lliurex::mrpdi;

class Sandbox : public input::BaseInputHandler
{
	private:
		Core * core;
		unsigned int id,address;
		
		Display * dis;
		Window win;
		GC gc;
		XFontStruct * font;
		
		int px,py;
		int c1,c2;
		int width1,width2;
		float angle1,angle2;
		
	public:
	
		Sandbox();
		~Sandbox();
		
		void pointer_callback(driver_event event);
		void start(unsigned int id,unsigned int address);
		void stop(unsigned int id,unsigned int address);
		void calibrate(unsigned int address);
		
		void refresh();
};
