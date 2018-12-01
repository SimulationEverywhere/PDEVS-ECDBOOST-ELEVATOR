/*
 * ElevatorController.hpp
 *
 *
 *
 */

#ifndef ElevatorController_HPP_
#define ElevatorController_HPP_

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
 * @brief ElevatorController PDEVS Model
 *
 * ElevatorController PDEVS Model():
 * - X = {(ectrl_sctrl_in, {1,2,3}); {(selectedFloor_in, {1,2,3})}
 * - Y = {(ectrl_motor1_out, {up, down, stop}); **posi}
 * - S = {"PREP_START," "WAIT_DATA," “PREP_MOVE_UP,” “MOVE_UP,”  “PREP_MOVE_DOWN,” “MOVE_DOWN,” “PREP_STOP,” "IDLE"}
 * - internal -> See DEVS Spec Doc
 * - external -> See DEVS Spec Doc
 * - out      -> See DEVS Spec Doc
 * - advance  -> See DEVS Spec Doc
*/
template<class TIME, class MSG>
class ElevatorController : public atomic<TIME, MSG>
{
    //initialize time for next state and message that will be outputted
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    //initialize states, ports,
    enum State {PREP_START, WAIT_DATA, PREP_MOVE_UP, PREP_MOVE_DOWN, MOVE_UP, MOVE_DOWN, PREP_STOP, IDLE};
    enum Port {ectrl_sctrl_in,ectrl_sctrl_out, ectrl_motor1_out, elevator_selectedFloor_in, elevator_position_out};
    std::string portName[5];
    const TIME infinity = boost::simulation::model<TIME>::infinity;

    State _state;
    MSG _outputMessage1;// Variables
    int sctrl_input = 0;
    int serial_input = 0;
    int curr = 0;
	// Prep time
    TIME movePrepTime = TIME(00,00,0,50);
    TIME moveTime = TIME(00,00,01,0);


public:
    /**
     * @brief ElevatorController constructor.
     *
     */
    explicit ElevatorController(const std::string &n = "ectrl") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::WAIT_DATA), _outputMessage1() {
    	portName[0] = "SCTRL_OUT";
    	portName[1] = "ECTRL_OUT";
    	portName[2] = "motor1";
    	portName[3] = "Floor_Button";
    	portName[4] ="Current_Position";
    	printf("ECTRL CREATED \n");
    }

    /**
     * @brief internal function.
     */
    void internal() noexcept {
    	switch (_state){
    		case IDLE:
    			_state = WAIT_DATA;
    			_next = infinity;
    			break;

		case MOVE_UP:
			curr=curr+1;
			if(curr< sctrl_input){
				_state = PREP_MOVE_UP;
				_next = movePrepTime;
			}
			else{
				_state = WAIT_DATA;
				_next = infinity;
			}

			break;

		case PREP_MOVE_UP:
			_state = MOVE_UP;
			_next = moveTime;
			break;

		case MOVE_DOWN:
			curr=curr-1;
			if(curr > sctrl_input){
				_state = PREP_MOVE_DOWN;
				_next = movePrepTime;
			}
			else{
			_state = WAIT_DATA;
			_next = infinity;
			}
			break;

		case PREP_MOVE_DOWN:
			_state = MOVE_DOWN;
			_next = moveTime;
			break;

		case PREP_STOP:
    			_state = WAIT_DATA;
    			_next = infinity;
    			break;

    		default:
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
     * @return MSG defined below.
     */
    std::vector<MSG> out() const noexcept {
    	if (_state==PREP_MOVE_UP)
    	{
			_outputMessage1 = MSG(portName[ectrl_motor1_out],CMD,UP);
			return std::vector<MSG>{_outputMessage1};

    	}

    	else if(_state== PREP_STOP || _state== MOVE_UP || _state== MOVE_DOWN )
    	{
			_outputMessage1 = MSG(portName[ectrl_motor1_out],CMD,STOP);
			return std::vector<MSG>{_outputMessage1};
    	}

    	else if (_state== PREP_MOVE_DOWN)
    	{
			_outputMessage1 = MSG(portName[ectrl_motor1_out],CMD,DOWN);
			return std::vector<MSG>{_outputMessage1};
    	}

    	return std::vector<MSG>{};
    }
    /**
     * @brief external function will set the new state depending on the value of the input.
     * @param msg external input message.
     * @param t time the external input is received.
     */
    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

    	MSG msg = mb.back();
    	if (msg.port == portName[ectrl_sctrl_in]) {

		if(_state == WAIT_DATA ) {
			sctrl_input = static_cast<int>(msg.val);
			//check if going up or down + change state
			if (sctrl_input - curr > 0) {
				_state = PREP_MOVE_UP;
				_next = movePrepTime;

			}
			else if (sctrl_input - curr < 0) {
				_state = PREP_MOVE_DOWN;
				_next = movePrepTime;

			}
		      else {
				//print invalid
			}
		}
		if(msg.val == STOP_PROC){
			_state = PREP_STOP;
			_next = Time::Zero;
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
    }

    void print()  noexcept {
    	SWO_PrintString("ectrl");
    }

};

}
}
}
}


#endif /* ElevatorController_HPP_ */


