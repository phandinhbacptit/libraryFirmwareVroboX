/**
 * @ Copyright (C), 2018-2022, VrobotX
 * \class   VnDht11
 * \brief   Driver for DHT11 sensor module.
 * @file    VnDht11.h
 * @author  VrobotX
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VDHT11 sensor module
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
 *    1. void VnDht11::setpin(int pin);
 *	  2. void VnDht11::ctrLed(boolean state)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2022/11/07      1.0.0            Build the first library.
 * </pre>
 */
#ifndef _VnDht11_H_
#define _VnDht11_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>
#include "DHT.h"

#define DHT11 	11
#define DHT22 	22
#define DHT21 	21
#define AM2301 	21

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: VnDht11
 * @Brief : Declaration of Class VnDht11.
 */
#ifdef VN_PORT_DEFINED
class VnDht11 : public VnPort
#else
class VnDht11
#endif
{
public:
#ifdef VN_PORT_DEFINED

  VnDht11(void);
  VnDht11(uint8_t port);
#else // VN_PORT_DEFINED
  VnDht11(int pin);
#endif // VN_PORT_DEFINED
	void setpin(int pin);
	float readHumidity();
	float readTemp();
	
	volatile uint8_t dht_pin, dht_type;
};
#endif
