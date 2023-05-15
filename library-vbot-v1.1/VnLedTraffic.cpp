/**
 * @ Copyright (C), 2018-2020, VrobotX
 * \class   VnLedTraffic
 * \brief   Driver for Traffic led module.
 * @file    VnLedTraffic.cpp
 * @author  VrobotX
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Driver for Traffic led module.
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2020, VrobotX. Use is subject to license \n
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
 * This file is a drive for Traffic led  device, The Traffic led  inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. void VnLedTraffic::setpin(int pin);
 *	  2. void VnLedTraffic::ctrLed(boolean state)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2022/11/07      1.0.0            Build the first library.
 * </pre>
 */
#include "VnLedTraffic.h"

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the TrafficLed to arduino port,
 * TrafficLed pins are used and initialized here.
 * @Param : None
 */
VnLedTraffic::VnLedTraffic(void)
{
	red_led_pin = 13;
	yellow_led_pin = 33; 
	green_led_pin = 4;
}

/**
 * Alternate Constructor which can call your own function to map the TrafficLed to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnLedTraffic::VnLedTraffic(uint8_t port) : VnPort(port)
{
	red_led_pin = s1;
	yellow_led_pin = s2; 
	green_led_pin = 4;
	Serial.print("pin: ");
	Serial.println(red_led_pin);
	Serial.println(yellow_led_pin);
	Serial.println(green_led_pin);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Traffic Led to arduino port,
 * @Param :  switchPin - arduino port for TrafficLed detect pin.
 */
VnLedTraffic::VnLedTraffic(int redPin, int yellowPin, int greenPin)
{
	red_led_pin = redPin;
	yellow_led_pin = yellowPin; 
	green_led_pin = greenPin;
}
#endif // VN_PORT_DEFINED
/**
 * @Brief :  Control state of module Led
 * @Param :  State - State control led 
 * 			 State = ON: Turn on Led 
 * 			 State = OFF: Turn off Led
 * @Retval : None
 * @Others : None
 */
void VnLedTraffic::ctrLed(int typeLed, int state)
{
	switch (typeLed) {
		case RED:	
			Serial.print("RED");
			pinMode(red_led_pin, OUTPUT);
			digitalWrite(red_led_pin, state);
		break;
		case YELLOW:
			Serial.print("YELLOW");
			pinMode(yellow_led_pin, OUTPUT);
			digitalWrite(yellow_led_pin, state);
		break;
		case GREEN:
			Serial.print("GREEN");
			pinMode(green_led_pin, OUTPUT);
			digitalWrite(green_led_pin, state);
		break;
		default:
		break;		
	}

}