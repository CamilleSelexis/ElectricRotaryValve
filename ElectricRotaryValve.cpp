#include "ElectricRotaryValve.h"

/*base::base(int a, int b){
	_a = a;
	_b = b;
}
void base::hello_world(){
	Serial.println("Hello world");
	Serial.print("A is equal to ");Serial.println(_a);
	Serial.print("B is equal to ");Serial.println(_b);
}

subclass::subclass(int a, int b, int c) : base(a,b){
	_a = a;
	_b = b;
	_c = c;
}

void subclass::sub(){
	Serial.print("A is equal to ");Serial.println(_a);
	Serial.print("B is equal to ");Serial.println(_b);
	Serial.print("C is equal to ");Serial.println(_c);
}*/
ERV::ERV(uint8_t home_pin, uint8_t port_pin, uint8_t CS_pin, uint8_t TGT_pin) : TMC4361A(CS_pin,TGT_pin){
	//Controller = new TMC4361A(CS_pin,TGT_pin);
	_home = home_pin;
	_port = port_pin;
}

bool ERV::init_ERV(){
	TMC4361A::begin();
	TMC4361A::setCurrentScale(8);//Set current Scale for a NEMA 17 motor
	TMC4361A::setVMAX(45,2);//Set speed to 45 RPM
	TMC4361A::setAMAX(0x000FFF);//Set AMAX to a lower value

	TMC4361A::setTargetRelative(51200);//1 full turn at 256 usteps
	while(!TMC4361A::isTargetReached()){
		if(!digitalRead(_home)){
			TMC4361A::setTargetRelative(0);
			TMC4361A::setCurrentPos(0);
			return true;
		}
	}

	Serial.println("Couldn't find the home position");

	return false;
}

bool ERV::openPort(int index){
	if(index<0 || index > 8)
		return false;
	long target = index*25*256;
	TMC4361A::setTarget(target); //Set absolute target
	while(!TMC4361A::isTargetReached());//wait for the motor to finish its move
	if(digitalRead(_port))
		return false; //Return false if after the move the port is not open
	return true;
}

bool ERV::openHome(){
	TMC4361A::setTarget(0);
	while(!TMC4361A::isTargetReached());
	if(digitalRead(_home))
		return false;
	return true;
}

int ERV::getOpenPort(){
	if(digitalRead(_port))
		return -1;
	float port = TMC4361A::getCurrentPos()/(25*256);
	return  round(port);
}