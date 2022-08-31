#include "TMC4361A.h"
#include "Arduino.h"

class ERV : public TMC4361A
{

	private:
		int _home;
		int _port;
		
	public:
		ERV(home_pin,port_pin);
		bool init_ERV();
		bool openPort(int index);
		bool openHome();
		int getOpenPort();


}