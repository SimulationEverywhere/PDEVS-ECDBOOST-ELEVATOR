#include <stdio.h>

#include <chrono>
#include <algorithm>
#include <boost/simulation.hpp>
#include <boost/rational.hpp>
#include <boost/lexical_cast.hpp>



// Atomic models
#include "SensorsController.hpp"
#include "ElevatorController.hpp"
//Port models
#include "eTime.h"
#include "eMessage.hpp"
#include "user_drivers/sensors_driver.hpp"
#include "user_drivers/sensors_port.hpp"
#include "user_drivers/elevator_driver.hpp"
#include "user_drivers/elevator_port.hpp"

using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;
using namespace std;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[])
{
	printf("Nucleo Board - Embedded CD-Boost \n\n");

	// Atomic models definition
	printf("Creating atomic models ... \n");
	auto sctrl = make_atomic_ptr<SensorsController<Time, Message>>();
	auto ectrl = make_atomic_ptr<ElevatorController<Time, Message>>();

	//Coupled model definition
		printf("Creating Coupled models ... \n");
		shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{sctrl,ectrl}, {sctrl}, {{sctrl,ectrl}}, {ectrl}});

		//Top I/O port definition
	printf("Defining top I/O ports ... \n");

	// Input ports
	auto start = make_port_ptr<START_IN<Time, Message>>();
	auto ir1 = make_port_ptr<IR1_IN<Time, Message>>();
	auto btn1 = make_port_ptr<IR2_IN<Time, Message>>();
	auto ir3 = make_port_ptr<IR3_IN<Time, Message>>();
	auto ir5 = make_port_ptr<IR5_IN<Time, Message>>();
	auto btn2 = make_port_ptr<IR4_IN<Time, Message>>();

    // Output ports
	auto motorright = make_port_ptr<MOVER_OUT<Time, Message>>();

    // Execution parameter definition
	printf("Preparing runner \n");
	Time initial_time{Time::currentTime()};
	erunner<Time, Message> root{ControlUnit, {{start,sctrl},{btn1,sctrl},{btn2,sctrl},{ir1,sctrl},{ir3,sctrl},{ir5,sctrl}} , {{motorright,ectrl}}};
	Time end_time{Time(0,30,0,0)};

	printf(("Starting simulation until time: seconds " + end_time.asString() + "\n").c_str());
	end_time = root.runUntil(end_time);


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
