/*
 * elevator_port.hpp
 *
 *
 */

#ifndef elevator_port_HPP_
#define elevator_port_HPP_


using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;




//Port2 - ectrl_motor1_out or motor1 --> Call it MOVER_OUT

template<class TIME, class MSG>
class MOVER_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit MOVER_OUT(const std::string &n = "motor1") noexcept : port<TIME, MSG>(n) {}//printf("M1 CREATED \n");
     void print() noexcept{}//printf("MOTOR 1 \n");
     bool pDriver(int &cmd, int &v) const noexcept;

};


//Port3 - elevator_selectedFloor_in or Floor_Button --> Call it Call_Floor

template<class TIME, class MSG>
class Call_Floor : public port<TIME, MSG>
{

public:
    /**
     * @brief call floor btn constructor.
     */
     explicit Call_Floor(const std::string &n = "Floor_Button", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd, int &v) const noexcept;
};

//Port4 - elevator_position_out or Current_Position

template<class TIME, class MSG>
class CURRENT_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief current_floor_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit CURRENT_OUT(const std::string &n = "Current_Position") noexcept : port<TIME, MSG>(n) {}//printf("M2 CREATED \n");
     void print() noexcept{}//printf("MOTOR 2 \n");
     bool pDriver(int &cmd, int &v) const noexcept;

};

#endif /* elevator_port_HPP_ */
