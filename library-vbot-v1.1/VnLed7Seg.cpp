/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnLed7Seg
 * \brief   Driver for led 7 segment module.
 * @file    VnLed7Seg.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2019/12/30
 * @brief   Driver for led 7 segment  module.
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
 * This file is a drive for led 7 segment  device, The led 7 segment inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
 *
 *    1. VnLed7Seg::VnLed7Seg(void);
 *	  2. VnLed7Seg::VnLed7Seg(uint8_t port):VnPort(port);
 *	  3. VnLed7Seg::VnLed7Seg(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin);
 *	  4. void VnLed7Seg::screenClear(void);
 *	  5. void VnLed7Seg::displayImage(unsigned int image[], int duration);
 *	  6. void VnLed7Seg:: scrollImage(unsigned int image[], uint8_t duration, uint8_t dir_shift);
 *
 * @ History:
 * <pre>
 * <Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac     2019/12/30         1.0.0             Build the first library.
 * </pre>
 */
#include "VnLed7Seg.h"


#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnLed7Seg::VnLed7Seg(void)
{
	_serPin		=	4;
	_clkPin 	=	33;
	_latchPin	=	13;
	_clrPin 	= 	5;
   
   	pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_clrPin, OUTPUT);
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
}

/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to MATRIX
 */
VnLed7Seg::VnLed7Seg(uint8_t port):VnPort(port)
{
	_serPin		=	s1;
	_clkPin 	=	s2;
	_latchPin	=	13;
	_clrPin		= 	5;
   
    pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_clrPin, OUTPUT);
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
	digitalWrite(_clrPin, LOW);	
	delay(100);
	digitalWrite(_clrPin, HIGH);	
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * @Param :  ser_pin 	- Pin correspond to the serial input data
 *			 clk_pin 	- Shift register clock
 *			 latch_pin 	- Pin emit signal load data from the shift to the storage register
 */
VnLed7Seg::VnLed7Seg(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin, uint8_t clr_pin)
{
  	_serPin		=	ser_pin;
	_clkPin 	=	clk_pin;
	_latchPin	=	latch_pin;
	_clrPin 	= 	clr_pin;
   
    pinMode(_clkPin, OUTPUT);
	pinMode(_serPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_clrPin, OUTPUT);
	// Serial.print("ser: ");
	// Serial.print(_serPin);
	// Serial.print("clk: ");
	// Serial.print(_clkPin);
	// Serial.print("latch: ");
	// Serial.print(_latchPin);
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Clear display image in the screen
 * @Param :  None
 * @Retval : None.
 */
void VnLed7Seg::screenClear(void)
{  
	digitalWrite(_latchPin, LOW);
	shiftOut(_serPin, _clkPin, LSBFIRST, 0x00);	//column
	shiftOut(_serPin, _clkPin, LSBFIRST, 0x00);	//row
	digitalWrite(_latchPin, HIGH);
	delay(1);
}
void VnLed7Seg::setLed(uint8_t num1, uint8_t num2, uint8_t num3, uint8_t num4, int duration)
{
	int pos[4] = {0x80, 0x40, 0x20, 0x10};
	uint8_t tmpNum[] = {0, 0, 0, 0};
	tmpNum[0] = num1;
	tmpNum[1] = num2;
	tmpNum[2] = num3;
	tmpNum[3] = num4;
	uint32_t _tmpDur = duration * 200;
	
	for (int i = 0; i <=3; i++) {
		switch (tmpNum[i]) {
			case 0:
				tmpNum[i] = LED_BCD[0];
				break;
			case 1:
				tmpNum[i] = LED_BCD[1];
				break;
			case 2:
				tmpNum[i] = LED_BCD[2];
				break;
			case 3:
				tmpNum[i] = LED_BCD[3];
				break;
			case 4:
				tmpNum[i] = LED_BCD[4];
				break;
			case 5:
				tmpNum[i] = LED_BCD[5];
				break;
			case 6:
				tmpNum[i] = LED_BCD[6];
				break;
			case 7:
				tmpNum[i] = LED_BCD[7];
				break;
			case 8:
				tmpNum[i] = LED_BCD[8];
				break;
			case 9:
				tmpNum[i] = LED_BCD[9];
				break;
			case 'a':
			case 'A':
				tmpNum[i] = LED_BCD[10];
				break;
			case 'b':
			case 'B':
				tmpNum[i] = LED_BCD[11];
				break;
			case 'c':
			case 'C':
				tmpNum[i] = LED_BCD[12];
				break;
			case 'd':
			case 'D':
				tmpNum[i] = LED_BCD[13];
				break;
			case 'e':
			case 'E':
				tmpNum[i] = LED_BCD[14];
				break;
			case 'f':
			case 'F':
				tmpNum[i] = LED_BCD[15];
				break;
			default:
				tmpNum[0] = num1;
				tmpNum[1] = num2;
				tmpNum[2] = num3;
				tmpNum[3] = num4;
				break;
	  }
	}
	  
		for (uint32_t hold = 0; hold < _tmpDur; hold++) {
		for (int a = 0; a < 4; a++) {
			digitalWrite(_latchPin, LOW);
			//delay(1);
			shiftOut(_serPin, _clkPin, LSBFIRST, pos[a]);	//column
			shiftOut(_serPin, _clkPin, LSBFIRST, tmpNum[a]);//row[a]);		//row
			delay(1);
			digitalWrite(_latchPin, HIGH);
		}
	}
}
