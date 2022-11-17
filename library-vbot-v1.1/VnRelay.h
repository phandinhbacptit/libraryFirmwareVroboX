/**
 * @ Copyright (C), 2018-2022, VrobotX
 * \class   VnRelay
 * \brief   Driver for Vn Single Led module.
 * @file    VnRelay.h
 * @author  VrobotX
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnRelay.cpp module
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2022, VrobotX. Use is subject to license \n
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
 * This file is a drive for Vn Buzzer device, The Vn Buzzer inherited the 
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. void VnRelay::setpin(int pin);
 *	  2. void VnRelay::ctrLed(boolean state)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2022/11/07      1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VnRelay_H_
#define _VnRelay_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: VnRelay
 * @Brief : Declaration of Class VnRelay.
 */
#ifdef VN_PORT_DEFINED
class VnRelay : public VnPort
#else
class VnRelay
#endif
{
public:
#ifdef VN_PORT_DEFINED

  VnRelay(void);
  VnRelay(uint8_t port);
#else // VN_PORT_DEFINED
  VnRelay(int pin);
#endif // VN_PORT_DEFINED
	void setpin(int pin);
	void ctrRelay(int state);
	
	volatile uint8_t relay_pin;
};
#endif
