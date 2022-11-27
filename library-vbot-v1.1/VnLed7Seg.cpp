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
void VnLed7Seg::setLed(int pos, int number)
{
     digitalWrite(_latchPin, LOW);
      switch (pos) {
        case 1:
          shiftOut(_serPin, _clkPin, LSBFIRST, 0x80);
          break;
        case 2:
          shiftOut(_serPin, _clkPin, LSBFIRST, 0x40);
          break;
        case 3:
          shiftOut(_serPin, _clkPin, LSBFIRST, 0x20);
          break;
        case 4:
          shiftOut(_serPin, _clkPin, LSBFIRST, 0x10);
          break;
      }
	  switch (number) {
		  case 'a':
		  case 'A':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[10]);
		   break;
		  case 'b':
		  case 'B':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[11]);
		   break;
		  case 'c':
		  case 'C':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[12]);
		   break;
		  case 'd':
		  case 'D':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[13]);
		   break;
		  case 'e':
		  case 'E':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[14]);
		   break;
		  case 'f':
		  case 'F':
		   shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[15]);
		   break;
		  default:
			shiftOut(_serPin, _clkPin, LSBFIRST,  LED_BCD[number]);
			break;
	  }
      delay(1);
      digitalWrite(_latchPin, HIGH);
}