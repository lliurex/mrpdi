
#ifndef _MRPDI_BASEDRIVER_
#define _MRPDI_BASEDRIVER_

#define DEV_STATUS_STOP 0
#define DEV_STATUS_RUNNING 1

struct driver_device_info
{
	unsigned int id;
	unsigned char iface;
	unsigned char type;
	const char * name;
};

struct driver_parameter_info
{
	unsigned int mask;
	const char * name;
};

enum event_type { EVENT_POINTER, EVENT_KEY, EVENT_STATUS, EVENT_DATA};
enum status_type {STATUS_READY,STATUS_SHUTDOWN,STATUS_COMMERROR};

struct driver_event
{
	unsigned int address;
	unsigned int id;
	enum event_type type;
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			unsigned int pointer;
			unsigned int button;
		}pointer;
		
		struct
		{
			unsigned char keycode;
			unsigned char mod;
		}key;
		
		struct
		{
			enum status_type id;
		}status;
		
		struct
		{
			unsigned int type;
			unsigned char buffer[32];
		}data;
		 
	};
};

extern "C" const char * name;
extern "C" const char * version;
extern "C" driver_device_info supported_devices [];
extern "C" driver_parameter_info supported_parameters [];


extern "C" void init();
extern "C" void shutdown();

extern "C" void start(unsigned int id,unsigned int address);
extern "C" void stop(unsigned int id,unsigned int address);

extern "C" void set_parameter(const char * key,unsigned int value);
extern "C" int get_parameter(const char * key,unsigned int * value);

extern "C" unsigned int get_status(unsigned int address);

extern "C" void set_callback( void(*callback) (driver_event) );

#endif
