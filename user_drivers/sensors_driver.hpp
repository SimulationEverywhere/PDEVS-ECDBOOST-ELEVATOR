/*
 * robocart_driver.hpp
 *
 *
 */

#ifndef sensorscontroller_driver_HPP_
#define sensorscontroller_driver_HPP_

#include "mbed.h"
#include <iostream>
#include <fstream>
#include <string>
#include "SeeedStudioShieldBot.h"
#include "sensors_port.hpp"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

DigitalIn hwbtn(PC_13);
DigitalIn btn1(D6);
DigitalIn btn2(D3);
SeeedStudioShieldBot bot(
    D8, D9, D11,              // Left motor pins
    D12, D10, D13,            // Right motor pins
    A0, A1, A2, A3, D4        // Sensors pins
);

int ir1_position=0;
int ir2_position=0;
int ir3_position=0;
int ir4_position=0;
int ir5_position=0;
int temperature_position=0;
int humidity_position=0;
int luminance_position=0;
int motion_position=0;



bool isStarted = false;

/* INPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool START_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	  if(!hwbtn){
		if(!isStarted){
			isStarted = true;
			v = -10;
		}
		else{
			isStarted = false;
			v = -11;
		}
		//printf("Button Pressed %d \n",v);
		return true;
	  }
	  else{
		return false;
	  }
}

template<class TIME, class MSG>
bool IR1_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.leftSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}



template<class TIME, class MSG>
bool IR2_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=btn1;
	return true;
}


template<class TIME, class MSG>
bool IR3_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.getCentreSensor() == 0){
		v=1;
	}
	else v=0;
	return true;
}

template<class TIME, class MSG>
bool IR4_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=btn2;
	return true;
}


template<class TIME, class MSG>
bool IR5_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.rightSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}


template<class TIME, class MSG>
bool TEMPERATURE_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
return true;
}

template<class TIME, class MSG>
bool LUMINANCE_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
return true;
}
template<class TIME, class MSG>
bool HUMIDITY_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
return true;
}
template<class TIME, class MSG>
bool MOTION_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
return true;
}



#endif /* robocart_driver_HPP_ */
