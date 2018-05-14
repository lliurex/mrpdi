


#ifndef _MRPDI_DRIVER_
#define _MRPDI_DRIVER_


#include <vector>
#include <string>


using namespace std;

namespace net
{
	namespace lliurex
	{
		namespace mrpdi
		{
			struct device_info
			{
				unsigned int id;
				unsigned char iface;
				unsigned char type;
				char * name;
			};
			
			struct parameter_info
			{
				unsigned int mask;
				char * name;
			};
			
			class Driver
			{
				public:
					
					void * handle;
					string name;
					string filename;
					vector<device_info> supported_devices;
					vector<parameter_info> supported_parameters;
				
			};
		}
	}
}
#endif
