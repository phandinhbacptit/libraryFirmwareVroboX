/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnKeyBoard
 * \brief   Driver for Keyboard module.
 * @file    VnKeyBoard.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Driver for Keyboard module.
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
 * This file is a drive for Keyboard device, The Keyboard inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. void VnKeyBoard::setpin(int pin);
 *	  2. void VnKeyBoard::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnKeyBoard::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnKeyBoard::noTone(int pin);
 *	  5. void VnKeyBoard::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2018/07/20      1.0.0            Build the first library.
 * </pre>
 */
#include "VnKeyBoard.h"

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnKeyBoard::VnKeyBoard(void) : VnPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2:  1 -io5, 2 - io33, 3 - io4, 4 -io13
 1 - SW3, 2 - SW4, 3 - SW1, 4 - SW2
 */
VnKeyBoard::VnKeyBoard(uint8_t port) : VnPort(port)
{
  sw1_pin = s1;//4;
  sw2_pin = s2;//13;
  sw3_pin = 5;
  sw4_pin = 33;
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Buzzer to arduino port,
 * @Param :  switchPin - arduino port for buzzer detect pin.
 */
VnKeyBoard::VnKeyBoard(int _sw1Pin, int _sw2Pin)
{
  sw1_pin = _sw1Pin;
  sw2_pin = _sw2Pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Reset the buzzer available pin by its arduino port.
 * @Param :  pin - arduino port for buzzer detect pin.
 * @Retval : None
 * @Others : None
 */
void VnKeyBoard::setpin(int _sw1_pin, int _sw2_pin)
{
	sw1_pin = _sw1_pin;
	sw2_pin = _sw2_pin;
#ifdef VN_PORT_DEFINED
	s1 = _sw1_pin;
	s2 = _sw2_pin;
#endif
}

/**
 * @Brief :  Playing the tones.
 * @Param :  pin - Which pin on board that buzzer is connecting to.
 *           frequency - The speed of buzzer's tone play.
 *           duration - Time of a tone play.
 * @Retval : None.
 * @Others : Frequency (in hertz) and duration (in milliseconds).
 */
int VnKeyBoard::read_button(void)
{
	uint8_t val1 = 0, val2 = 0, val3 = 0, val4 = 0;
	int ret = 1;
	
#ifdef 	VN_PORT_DEFINED
	val1 = VnPort::dRead1(INPUT_PULLUP);
	val2 = VnPort::dRead2(INPUT_PULLUP);
#else
	pinMode(sw1_pin, INPUT_PULLUP);
    val1 = digitalRead(sw1_pin);
	
	pinMode(sw2_pin, INPUT_PULLUP);
    val2 = digitalRead(sw2_pin);
#endif

	pinMode(sw3_pin, INPUT_PULLUP);
    val3 = digitalRead(sw3_pin);
	
	pinMode(sw4_pin, INPUT_PULLUP);
    val4 = digitalRead(sw4_pin);
	
	delay(150);
	
	if (val1 == 0)
		return 1;
	else if (val2 == 0)
		return 2;
	else if (val3 == 0)
		return 3;
	else if (val4 == 0)
		return 4;
	else return 0;
}
