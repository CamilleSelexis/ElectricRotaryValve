#ifndef _ELECTRICROTARYVALVE_H
#define _ELECTRICROTARYVALVE_H

#include "TMC4361A.h"
#include "Arduino.h"

/*class base {
	public:
		int _a;
		int _b;
		base(int a,int b);
		void hello_world();
};
class subclass : public base
{
	public:
		int _a;
		int _b;
		int _c;
		subclass(int a, int b, int c);
		void sub();
};*/

class ERV : public TMC4361A
{

	private:
		uint8_t _home;
		uint8_t _port;

	public:
		ERV(uint8_t home_pin,uint8_t port_pin, uint8_t cs_pin, uint8_t tgt_pin);
		bool init_ERV();
		bool openPort(int index);
		bool openHome();
		int getOpenPort();


};

#endif