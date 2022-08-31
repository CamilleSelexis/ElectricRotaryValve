#include "ElectricRotaryValve.h"


ERV(home_pin,port_pin,CS_pin,TGT_pin){
	TMC4361A(CS_pin,TGT_pin);
	_home = home_pin;
	_port = port_pin;
}

bool init_ERV(){
	this.begin();
	this.setCurrentScale(8);//Set current Scale for a NEMA 17 motor
	this.setVMAX(45,2);//Set speed to 45 RPM
	this.setAMAX(0x000FFF);//Set AMAX to a lower value

	this.setTargetRelative(51200);//1 full turn at 256 usteps
	while(!this.isTargetReached()){
		if(!digitalRead(_home)){
			this.setTargetRelative(0);
			this.setCurrentPos(0);
			return true;
		}
	}

	Serial.println("Couldn't find the home position");

	return false;
}

bool openPort(int index){
	if(index<0 || index > 8)
		return false;
	long target = index*25*256;
	this.setTarget(target); //Set absolute target
	while(!this.isTargetReached());//wait for the motor to finish its move
	if(digitalRead(_port))
		return false; //Return false if after the move the port is not open
	return true;
}

bool openHome(){
	this.setTarget(0);
	while(!this.isTargetReached());
	if(digitalRead(_home))
		return false;
	return true;
}

int getOpenPort(){
	if(digitalRead(_port))
		return -1;
	float port = this.getCurrentPos()/(25*256);
	return  round(port);
}