/*
 * robocart_driver.hpp
 *
 *
 */

#ifndef elevatorcontroller_driver_HPP_
#define elevatorcontroller_driver_HPP_

#include "mbed.h"

#include <iostream>
#include <fstream>
#include <string>


#include "elevator_port.hpp"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

bool startLeft = true;


/* OUTPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool MOVER_OUT<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept{
	// This will be moved into the initHardware function
	if(startLeft){
		bot.enable_left_motor();
		startLeft = false;
	}
	if(cmd==CMD){
		switch(v){
		case -7:
			bot.left_motor(0.2);

			break;
		case -8:
			bot.left_motor(-0.2);

			break;
		case -9:
			bot.left_motor(0);

			break;
		}}

	return true;
}


template<class TIME, class MSG>
bool CURRENT_OUT<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept{


return true;
}


#endif /* robocart_driver_HPP_ */
