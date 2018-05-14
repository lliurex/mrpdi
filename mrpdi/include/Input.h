

#ifndef _MRPDI_INPUT_
#define _MRPDI_INPUT_

#include "BaseDriver.h"
#include <string>
#include <vector>
#include <map>
#include <linux/uinput.h>
#include <linux/input.h>

using namespace std;

namespace net
{
	namespace lliurex
	{
		namespace mrpdi
		{
			namespace input
			{
				
				namespace PointerFlags
				{ 
					enum e
					{
						Simple=0,
						Pressure=1
					};
				}
				
				
				class DeviceSettingsEntry
				{
					public:
					
					string name;
					unsigned int id;
					float calibration[8];
					map<string,unsigned int> params;
					
					DeviceSettingsEntry()
					{
						//Safe default settings
						name="Unknown";
						id=0x00000000;
						calibration[0]=0.0f;
						calibration[1]=0.0f;
						calibration[2]=0.0f;
						calibration[3]=0.0f;
						calibration[4]=0.0f;
						calibration[5]=0.0f;
						calibration[6]=0.0f;
						calibration[7]=0.0f;
					}
				};
				
				class AbsolutePointer
				{
					protected:
						int fd_uinput;
						struct uinput_user_dev uidev;
						
						unsigned int id;
						unsigned int address;
						unsigned char pointer;
										
						string name;
						
						float x,y;
						float z;
						int button[6];
						int button_state[6];
						
						float calibration[8];
						bool use_calibration;
						bool has_pressure;
						
						int set_uinput(unsigned long int property,unsigned int value);
						int send_uinput(input_event * ev);
					
					public:
						AbsolutePointer(string name,unsigned int id,unsigned int address,unsigned char pointer,unsigned int flags);
						~AbsolutePointer();
						
						void start();
						void stop();
						void set_position(float x,float y);
						void set_button(int num,int state);
						void set_pressure(float z);
						void update();
						unsigned int get_id();
						unsigned int get_address();
						unsigned char get_pointer();
						
						void set_calibration(float * calibration);
					
				};
					
				
				class BaseInputHandler
				{
					public:
						
						virtual void pointer_callback(driver_event event) = 0;
						virtual void start(unsigned int id,unsigned int address) = 0;
						virtual void stop(unsigned int id,unsigned int address) = 0;
						
						virtual void calibrate(unsigned int address) = 0;
				};			
				
				class InputHandler : public BaseInputHandler
				{
					private:
						vector<AbsolutePointer *> devices;
						map<unsigned int,DeviceSettingsEntry> settings_map;
						
						int calibration_step;
						float calibration_points[8];
						unsigned int calibration_address;
						int calibration_press;
						
					public:
						
						
						InputHandler();
						~InputHandler();
						
						void set_settings(map<unsigned int,DeviceSettingsEntry> settings);
						map<unsigned int,DeviceSettingsEntry> get_settings();
						
						void pointer_callback(driver_event event);
						void start(unsigned int id,unsigned int address);
						void stop(unsigned int id,unsigned int address);
						
						void calibrate(unsigned int address);
				};
				
			}
		}
	}
}

#endif
