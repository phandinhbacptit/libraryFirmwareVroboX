/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnLed7Seg
 * \brief   Driver for led 7 segment module.
 * @file    VnLed7Seg.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for led 7 segment module
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
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. void VnLed7Seg::setpin(int pin);
 *	  2. void VnLed7Seg::tone(int pin, uint16_t frequency, uint32_t duration);
 *	  3. void VnLed7Seg::tone(uint16_t frequency, uint32_t duration)
 *	  4. void VnLed7Seg::noTone(int pin);
 *	  5. void VnLed7Seg::noTone();
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2019/12/30      1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VnLed7Seg_H_
#define _VnLed7Seg_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: VnLed7Seg
 * @Brief : Declaration of Class VnLed7Seg.
 */
 
#ifdef VN_PORT_DEFINED
class VnLed7Seg : public VnPort
#else
class VnLed7Seg
#endif
{
public:
#ifdef VN_PORT_DEFINED

	VnLed7Seg(void);
	VnLed7Seg(uint8_t port);
	VnLed7Seg(uint8_t port, uint8_t slot);
  
#else //VN_PORT_DEFINED

	VnLed7Seg(uint8_t ser_pin, uint8_t clk_pin, uint8_t latch_pin, uint8_t clr_pin);

#endif //VN_PORT_DEFINED
	void shiftOutData(uint8_t dataOut);
	void screenClear(void);
	void setLed(int pos, int number);
private:
	volatile uint8_t  _latchPin;
	volatile uint8_t  _clkPin;
	volatile uint8_t  _serPin;
	volatile uint8_t  _clrPin;
	unsigned char LED_BCD[16] ={0xeb,0x88,0xe5,0xad,0x8e,0x2f,0x6f,0x89,0xef,0xaf,0xcf,0x6e,0x63,0xec,0x67,0x47};

};
#endif /* _VnLed7Seg_H_ */