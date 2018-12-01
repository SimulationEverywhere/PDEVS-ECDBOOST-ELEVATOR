/*

 * userbtn_port.hpp
 *
 *
 */

#ifndef sensors_port_HPP_
#define sensors_port_HPP_


using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

template<class TIME, class MSG>
class START_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief startbtn constructor.
     */
     explicit START_IN(const std::string &n = "start_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class LUMINANCE_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief luminance sensor constructor.
     */
     explicit LUMINANCE_IN(const std::string &n = "luminance_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};
template<class TIME, class MSG>
class TEMPERATURE_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief temperature sensor constructor.
     */
     explicit TEMPERATURE_IN(const std::string &n = "temperature_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class HUMIDITY_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief humidity sensor constructor.
     */
     explicit HUMIDITY_IN(const std::string &n = "humidity_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class MOTION_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief motion sensor constructor.
     */
     explicit MOTION_IN(const std::string &n = "motion_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};


template<class TIME, class MSG>
class IR1_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit IR1_IN(const std::string &n = "ir1_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};

template<class TIME, class MSG>
class IR2_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit IR2_IN(const std::string &n = "ir2_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};
template<class TIME, class MSG>
class IR3_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit IR3_IN(const std::string &n = "ir3_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};
template<class TIME, class MSG>
class IR4_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit IR4_IN(const std::string &n = "ir4_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};
template<class TIME, class MSG>
class IR5_IN : public port<TIME, MSG>
{

public:
    /**
     * @brief IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit IR5_IN(const std::string &n = "ir5_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};

template<class TIME, class MSG>
class START_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief motor1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit START_OUT(const std::string &n = "START_OUT") noexcept : port<TIME, MSG>(n) {}//printf("M1 CREATED \n");
     void print() noexcept{}//printf("MOTOR 1 \n");
     bool pDriver(int &cmd, int &v) const noexcept;

};
#endif /* sensors_port_HPP_ */
