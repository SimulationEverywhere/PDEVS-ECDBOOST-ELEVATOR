/*
 * SensorController.hpp
 *
 *
 */

#ifndef SensorsController_HPP_
#define SensorsController_HPP_

#include <boost/any.hpp>
#include <boost/simulation/pdevs/atomic.hpp>
#include "commonH.h"
#include "SWO.h"
#include "mbed.h"

namespace boost {
namespace simulation {
namespace pdevs {
namespace basic_models {
/**
 * @brief SensorsController PDEVS Model
 *
 * SensorController PDEVS Model():
 * - X = {(start_in, {START, STOP}); (luminance_in, {CMD,VALUE}); (humidity_in, {CMD,VALUE}); (temperature_in, {CMD,VALUE}); (ir[5]_in, {CMD,VALUE})}
 *
 * - Y = {(start_out, {START, STOP}); (sctrl_lctrl_out, {CMD,VALUE}); (sctrl_ectrl_out, {CMD,VALUE}); (sctrl_wctrl_out, {CMD,VALUE});
 * 		(sctrl_pctrl_out, {CMD,VALUE}); (sctrl_wctrl_out, {CMD,VALUE});(sctrl_tctrl_out, {CMD,VALUE});}
 *
 * - S = { “WAIT_DATA”, “IDLE”,“PREP_RX”,“TX_DATA”,“PREP_STOP” }
 *

 */
template<class TIME, class MSG>
class SensorsController : public atomic<TIME, MSG>     // Classe du modèle atomique
{
	TIME _next;
	std::vector<MSG> _outvalue;
private:
	enum State {IDLE, PREP_RX, WAIT_DATA, TX_DATA, PREP_STOP};
	enum Port {sctrl_start_in, sctrl_luminance_in, sctrl_motion_in, sctrl_humidity_in,sctrl_temperature_in,sctrl_ir1_in,
		sctrl_ir2_in,sctrl_ir3_in,sctrl_ir4_in,sctrl_ir5_in,sctrl_start_out, sctrl_lctrl_out, sctrl_tctrl_out, sctrl_ectrl_out,sctrl_ectrl_in,
		sctrl_pctrl_out, sctrl_wctrl_out};
	std::string portName[17];
	State _state;
	MSG _outputMessageStart,_outputMessageLight,_outputMessageHVAC,_outputMessageElevator,_outputMessageWater,_outputMessagePark;
	//Variables:
	int sensor_temperature=0,sensor_humidity=0,sensor_luminance=0,sensor_motion=0,sensor_ir1=0,sensor_ir2=0,sensor_ir3=0,sensor_ir4=0,sensor_ir5=0 ;
	int wichSensor=0;
	TIME scTxTime = TIME(00,00,00,050);
	TIME scRxPrepTime = TIME(00,00,00,050);
	const TIME infinity=boost::simulation::model<TIME>::infinity;



public:
	/**
	 * @brief SensorController constructor.
	 */
	explicit SensorsController(const std::string &n = "sctrl") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessageStart(), _outputMessageLight(),_outputMessageHVAC(),_outputMessageElevator(),_outputMessageWater(),_outputMessagePark() {
		portName[0] = "start_in";
		portName[1] = "luminance_in";
		portName[2] = "motion_in";
		portName[3] = "humidity_in";
		portName[4] = "temperature_in";
		portName[5] = "ir1_in";portName[6] = "ir2_in";portName[7] = "ir3_in";
		portName[8] = "ir4_in";portName[9] = "ir5_in";
		portName[10] = "START_OUT";
		portName[11] = "LCTRL_OUT";
		portName[12] = "TCTRL_OUT";
		portName[13] = "SCTRL_OUT";
		portName[14] = "ECTRL_IN";
		portName[15] = "PCTRL_OUT";
		portName[16] = "WCTRL_OUT";
	}

	/**
	 * @brief internal function.
	 */
	void internal() noexcept {
		switch (_state){
		case PREP_STOP:
			_state = IDLE;
			_next = infinity;
			break;

		case PREP_RX:
		case TX_DATA:
			_state = WAIT_DATA;
			_next = infinity;
			break;
		}

	}
	/**
	 * @brief advance function.
	 * @return Time until next internal event.
	 */
	TIME advance() const noexcept {
		return _next;
	}
	/**
	 * @brief out function.
	 * @return MSG defined in construction.
	 */
	std::vector<MSG> out() const noexcept {
		switch (_state){

		case PREP_STOP:
			//_outputMessageStart = MSG(portName[sctrl_start_out],CMD,STOP_PROC); //Stop All Sensors
			//_outputMessageLight = MSG(portName[sctrl_lctrl_out],CMD, STOP_PROC); //Stop Lighting Ctrl
			//_outputMessageHVAC = MSG(portName[sctrl_tctrl_out],CMD, STOP_PROC); //Stop HVAC Ctrl
			//_outputMessagePark = MSG(portName[sctrl_pctrl_out],CMD, STOP_PROC); //Stop Parking Occupancy Ctrl
			//_outputMessageWater = MSG(portName[sctrl_wctrl_out],CMD, STOP_PROC); //Stop WaterCtrl
			_outputMessageElevator = MSG(portName[sctrl_ectrl_out],CMD, STOP_PROC); //Stop Elevator Ctrl
			return std::vector<MSG>{/*_outputMessageStart,_outputMessageLight,_outputMessageHVAC,_outputMessagePark,*/_outputMessageElevator,/*_outputMessageWater*/};

		case PREP_RX:
			_outputMessageStart = MSG(portName[sctrl_start_out],CMD, START_PROC); //Start All Sensors
			return std::vector<MSG>{_outputMessageStart};

		case TX_DATA: {
			switch(wichSensor){
			/*case 1: _outputMessageLight = MSG(portName[sctrl_lctrl_out],MOUV, sensor_motion); //Send feedback to Lighting Ctrl
			_outputMessageHVAC = MSG(portName[sctrl_tctrl_out],MOUV, sensor_motion); //Send feedback to HVAC Ctrl
			return std::vector<MSG>{_outputMessageLight,_outputMessageHVAC};
			break;
			case 2:_outputMessageLight = MSG(portName[sctrl_lctrl_out],LUMI, sensor_luminance); //Send feedback to Lighting Ctrl
			return std::vector<MSG>{_outputMessageLight};
			break;
			case 3:_outputMessageHVAC = MSG(portName[sctrl_tctrl_out],HUMI, sensor_humidity); //Send feedback to HVAC Ctrl
			return std::vector<MSG>{_outputMessageHVAC};
			break;
			case 4:_outputMessageHVAC = MSG(portName[sctrl_tctrl_out],TEMP, sensor_temperature); //Send feedback to HVAC Ctrl
			_outputMessageWater = MSG(portName[sctrl_wctrl_out],TEMP, sensor_temperature); //Send feedback to Water Ctrl
			return std::vector<MSG>{_outputMessageHVAC,_outputMessageWater};
			break;
			*/case 5:_outputMessageElevator = MSG(portName[sctrl_ectrl_out],FLOOR, 0); //Send feedback to Elevator Ctrl
			return std::vector<MSG>{_outputMessageElevator};
			break;
			case 6:_outputMessageElevator = MSG(portName[sctrl_ectrl_out],FLOOR, 4); //Send feedback to Elevator Ctrl
			return std::vector<MSG>{_outputMessageElevator};
			break;
			case 7:_outputMessageElevator = MSG(portName[sctrl_ectrl_out],FLOOR, 1); //Send feedback to Elevator Ctrl
			return std::vector<MSG>{_outputMessageElevator};
			break;
			case 8:_outputMessageElevator = MSG(portName[sctrl_ectrl_out],FLOOR, 3); //Send feedback to Elevator Ctrl
			return std::vector<MSG>{_outputMessageElevator};
			break;
			case 9:_outputMessageElevator = MSG(portName[sctrl_ectrl_out],FLOOR, 2); //Send feedback to Elevator Ctrl
			return std::vector<MSG>{_outputMessageElevator};
			break;
			}

		}
		};
		return std::vector<MSG>{};

	}
	/**
	 * @brief external function
	 * @param msg external input message.
	 * @param t time the external input is received.
	 */
	void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

		MSG msg = mb.back();

		if (msg.port == portName[sctrl_start_in]){
			if(_state == IDLE && msg.val == START_PROC){
				_state = PREP_RX;
				_next = scRxPrepTime;
			}

			else if (msg.val == STOP_PROC) {
				_state = PREP_STOP;
				_next = Time::Zero;
			}
		}
		/*else if (msg.port == portName[sctrl_motion_in]){
			if(_state == WAIT_DATA) {

				sensor_motion = static_cast<int>(msg.val);
				wichSensor=1;
				_state = TX_DATA;
				_next = scTxTime;

			}
		}

		else if (msg.port == portName[sctrl_luminance_in]){
			if(_state == WAIT_DATA) {
				sensor_luminance = static_cast<int>(msg.val);
				wichSensor=2;
				_state = TX_DATA;
				_next = scTxTime;

			}
		}
		else if (msg.port == portName[sctrl_temperature_in]){
			if(_state == WAIT_DATA) {
				sensor_temperature = static_cast<int>(msg.val);
				wichSensor=4;
				_state = TX_DATA;
				_next = scTxTime;

			}
		}
		else if (msg.port == portName[sctrl_humidity_in]){
			if(_state == WAIT_DATA) {
				sensor_humidity = static_cast<int>(msg.val);
				wichSensor=3;
				_state = TX_DATA;
				_next = scTxTime;

			}
		}*/
		else if (msg.port == portName[sctrl_ir1_in]){
			if(_state == WAIT_DATA) {
				sensor_ir1 = static_cast<int>(msg.val);
				if(sensor_ir1==1){
				wichSensor=5;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[sctrl_ir2_in]){
			if(_state == WAIT_DATA) {
				sensor_ir2 = static_cast<int>(msg.val);
				if(sensor_ir2==1){
				wichSensor=6;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}\
		}
		else if (msg.port == portName[sctrl_ir3_in]){
			if(_state == WAIT_DATA) {
				sensor_ir3 = static_cast<int>(msg.val);
				if(sensor_ir3==1){
				wichSensor=7;
				_state = TX_DATA;
				_next = scTxTime;
				}

			}
		}
		else if (msg.port == portName[sctrl_ir4_in]){
			if(_state == WAIT_DATA) {
				sensor_ir4 = static_cast<int>(msg.val);
				if(sensor_ir4==1){
				wichSensor=8;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[sctrl_ir5_in]){
			if(_state == WAIT_DATA) {
				sensor_ir5 = static_cast<int>(msg.val);
				if(sensor_ir5==1){
				wichSensor=9;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
	}

	/**
	 * @brief confluence function.
	 * Execute the internal.
	 *
	 * @param msg
	 * @param t time the external input is confluent with an internal transition.
	 */
	void confluence(const std::vector<MSG>& mb, const TIME& t)  noexcept  {
		internal();
		//external(mb,t);
	}

	void print()  noexcept {SWO_PrintString("sctrl");}

};

}
}
}
}


#endif /* SensorsController_HPP_ */
