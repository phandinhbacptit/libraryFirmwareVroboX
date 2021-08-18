/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \brief   Driver for Vbot Servo Motor.
 * \file    VnServo.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/10/29     
 * @brief   Driver for Vbot Servo Motor.
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2020, Vrobotx. Use is subject to license \n
 * conditions. The main licensing options available are GPL V2 or Commercial: \n
 *
 * @ Open Source Licensing GPL V2
 * This is the appropriate option if you want to share the source code of your \n
 * application with everyone you distribute it to, and you also want to give them \n
 * the right to share who uses it. If you wish to use this software under Open \n
 * Source Licensing, you must contribute all your source code to the open source \n
 * community in accordance with the GPL Version 2 when your application is \n
 * distributed. See http://www.gnu.org/copyleft/gpl.html
 *
 * @Brief :
 * This file is Hardware adaptation layer between Vbot board and all
 * Vrobotx drives
 * 
 * @ Method List:
 *
 *    1. void VnServo::move(int direction, int speed);
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/10/29      1.0.0            Build the first library.
 * </pre>
 */

#include "VnServo.h"

/**
 * Alternate Constructor which can call your own function to map the MBot DCMotor to arduino port,
 * the slot2 pin will be used here since specify slot is not be set.
 * @Param : port - RJ25 port from PORT_1 to M2
 */
#ifdef VN_PORT_DEFINED
VnServo::VnServo(void) : VnPort(0)
{

}

VnServo::VnServo(uint8_t port) : VnPort(port)
{

}

/**
 * @Brief :  MBot DCMotor moves with the speed and direction.
 * @Param :  direction - The direction of the MBot DCMotor's movement
 *           speed - The speed of MBot DCMotor's movement.
 * @Retval : None
 * @Others : None
 */
void VnServo::attach(uint8_t channel)
{
	_channel = channel;
	
	ledcSetup(_channel, 50, 16);     // 50 hz, 16-bit width 1736 (0 degree) -> 7897 (180 degree)
	ledcAttachPin(s1, _channel);
	Serial.print("S1: ");
	Serial.println(s1);
    Serial.print("Channel: ");
	Serial.println(_channel);
}

void VnServo::detach(void)
{
	ledcDetachPin(s1);
	
}

#else
VnServo::VnServo(uint8_t pin, uint8_t channel) 
{
	_pin = pin;
	_channel = channel;
}

void VnServo::attach(void) 
{
	ledcSetup(_channel, 50, 16);     // 50 hz, 16-bit width 
	ledcAttachPin(_pin, _channel);
}

void VnServo::detach(void)
{
	ledcDetachPin(_pin);
	
}
#endif //VN_PORT_DEFINED

void VnServo::write(int value)
{
	ledcWrite(_channel, value);
	
}
#define MIN_PERIOD		1736 //(0.53ms <=> 0 degree)
#define MAX_PERIOD 		7897 //(2.41ms <-> 180 degree)
#define FULL_RANGLE		180 // degree
void VnServo::rotate(int degree)
{
	uint16_t val = 0;
	
	val = MIN_PERIOD + degree * (MAX_PERIOD -  MIN_PERIOD) / FULL_RANGLE;
	write (val);
	Serial.println(val);
}


