/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnColorSensor
 * \brief   Driver for Vn Buzzer module.
 * @file    VnColorSensor.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Header for VnColorSensor.cpp module
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
 * This file is a drive for Vn Buzzer device, The Vn Buzzer inherited the 
 * VnSerial class from SoftwareSerial.
 *
 * @ Vnthod List:
 *
 *    1. VnColorSensor::VnColorSensor(void);
 *	  2. VnColorSensor::VnColorSensor(uint8_t port):VnPort(port);
 *	  3. VnColorSensor::VnColorSensor(uint8_t s2Pin, uint8_t s3kPin, uint8_t outPin, uint8_t ctrPin)
 *    4. void enable_color_sensor(void)
 *    5. void disable_color_sensor(void)
 *    6. void read_color(uint8_t *red, uint8_t *green, uint8_t *blue)
 *    7. void detect_color(void)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2019/04/11      1.0.0             Library for color sensor module
 * </pre>
 */
#ifndef _VnColorSensor_H_
#define _VnColorSensor_H_

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include <VnConfig.h>

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED
/**
 * Class: VnColorSensor
 * @Brief : Declaration of Class VnColorSensor.
 */
#define RIGHT_SIDE 		0
#define LEFT_SIDE 		1

#define RED_COLOR			1
#define GREEN_COLOR			2
#define BLUE_COLOR			3
#define YELLOW_COLOR		4
#define WHITE_COLOR			7
#define BLACK_COLOR			8

 
#ifdef VN_PORT_DEFINED
class VnColorSensor : public VnPort
#else
class VnColorSensor
#endif
{
public:
#ifdef VN_PORT_DEFINED

	VnColorSensor(void);
	VnColorSensor(uint8_t port);
  
#else //VN_PORT_DEFINED

	VnColorSensor(uint8_t s2Pin, uint8_t s3Pin, uint8_t outPin, uint8_t ctrPin);

#endif //VN_PORT_DEFINED

	void enable_color_sensor(void);
	void disable_color_sensor(void);
	void read_color(int *red, int *green, int *blue);
	uint8_t detect_color(void);
	
private:
	volatile uint8_t  _s2Pin;
	volatile uint8_t  _s3Pin;
	volatile uint8_t  _outPin;
	volatile uint8_t  _ctrPin;
};
#endif /* _VnColorSensor_H_ */