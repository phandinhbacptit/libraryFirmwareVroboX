/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnKeyBoard
 * \brief   Driver for Keyboard module.
 * @file    VnKeyBoard.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnKeyBoard.cpp module
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
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
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
#ifndef VnKeyBoard_H
#define VnKeyBoard_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED


#define MODE1	1
#define MODE2	2
#define MODE3	3
#define MODE4	4

/**
 * Class: VnKeyBoard
 * @Brief : Declaration of Class VnKeyBoard.
 */
#ifdef VN_PORT_DEFINED
class VnKeyBoard : public VnPort
#else
class VnKeyBoard
#endif
{
public:
#ifdef VN_PORT_DEFINED

  VnKeyBoard(void);
  VnKeyBoard(uint8_t port);
#else // VN_PORT_DEFINED
  VnKeyBoard(int _sw1Pin, int _sw2Pin);
#endif // VN_PORT_DEFINED
	void setpin(int _sw1_pin, int _sw2_pin);
	int read_button(void);
	
	volatile uint8_t sw1_pin, sw2_pin, sw3_pin, sw4_pin;
};
#endif
