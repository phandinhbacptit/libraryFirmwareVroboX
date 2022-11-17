/**
 * @ Copyright (C), 2018-2020, VrobotX
 * \class   VnRelay
 * \brief   Driver for Relay module.
 * @file    VnRelay.cpp
 * @author  VrobotX
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Driver for Vn Single Led module.
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
 * This file is a drive for Vn Single Led device, The Vn Single Led inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. void VnRelay::setpin(int pin);
 *	  2. void VnRelay::ctrRelay(boolean state)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2022/11/07      1.0.0            Build the first library.
 * </pre>
 */
#include "VnRelay.h"

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Single Led to arduino port,
 * Single Led pins are used and initialized here.
 * @Param : None
 */
VnRelay::VnRelay(void) : VnPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the Single Led to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnRelay::VnRelay(uint8_t port) : VnPort(port)
{
  relay_pin = s1;
  Serial.print("data: ");
  Serial.println(relay_pin);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Single Led to arduino port,
 * @Param :  switchPin - arduino port for Single Led detect pin.
 */
VnRelay::VnRelay(int pin)
{
  relay_pin = pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Reset the Single Led available pin by its arduino port.
 * @Param :  pin - arduino port for Single Led detect pin.
 * @Retval : None
 * @Others : None
 */
void VnRelay::setpin(int pin)
{
	relay_pin = pin;
#ifdef VN_PORT_DEFINED
	s1 = pin;
#endif
}
/**
 * @Brief :  Control state of module Led
 * @Param :  State - State control led 
 * 			 State = ON: Turn on Led 
 * 			 State = OFF: Turn off Led
 * @Retval : None
 * @Others : None
 */
void VnRelay::ctrRelay(int state)
{
	Serial.print("aa");
	pinMode(relay_pin, OUTPUT);
    digitalWrite(relay_pin, state);
}