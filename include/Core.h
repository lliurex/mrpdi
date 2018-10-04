
#include "Input.h"
#include "Driver.h"
#include <vector>
#include <string>


#ifndef _MRPDI_CORE_
#define _MRPDI_CORE_

using namespace std;

namespace net
{
	namespace lliurex
	{
		namespace mrpdi
		{
		

			struct connected_device_info
			{
				unsigned int id;
				unsigned int address;
				unsigned char type;
				unsigned int status;
				string name;
			};

			struct parameter_conf_entry
			{
				string driver_name;
				string parameter_name;
				unsigned int value;
			};
			
			class Core
			{
				private:
				vector<Driver*> drivers;			
				input::BaseInputHandler * inputhandler;
				
				void load_drivers();
				
				public:
				static Core * instance;
				static Core * getCore();
				
				Core();
				~Core();
				
				void init();
				void shutdown();
				
				void set_input_handler(input::BaseInputHandler * handler);
				input::BaseInputHandler * get_input_handler();
				
				void update_devices(vector<connected_device_info> * out_list);
				void get_parameter_list(unsigned int id,vector<string> * out_list);
				
				string get_device_name(unsigned int id);
				
				void start(unsigned int id,unsigned int address);
				void stop(unsigned int id,unsigned int address);
				
				void set_parameter(unsigned int id,const char * key,unsigned int value);
				int get_parameter(unsigned int id,const char * key,unsigned int * value);

			};
			
		}
	}
}

#endif
