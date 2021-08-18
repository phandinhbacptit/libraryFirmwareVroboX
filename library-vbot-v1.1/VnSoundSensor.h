/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnSoundSensor
 * \brief   Driver for Me line follwer device.
 * @file    VnSoundSensor.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Header for for VnSoundSensor.cpp module
 *
 * @ Copyright
 * This software is Copyright (C), 2012-2016, Vrobotx. Use is subject to license \n
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
 * This file is a drive for Me line follwer device, It supports line follwer device
 * V2.2 provided by the Vrobotx. The line follwer used Infrared Tube to Use infrared
 * receiver and transmitter to detect the black line.
 *
 * @ Method List:
 *
 *    1. void VnSoundSensor::setpin(uint8_t Sensor1,uint8_t Sensor2)
 *    2. uint8_t VnSoundSensor::readSensors(void)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac         2018/07/20     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#ifndef VnSoundSensor_H
#define VnSoundSensor_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED


/**
 * Class: VnSoundSensor
 * @Brief :
 * Declaration of Class VnSoundSensor.
 */
#ifndef VN_PORT_DEFINED
class VnSoundSensor
#else // !VN_PORT_DEFINED
class VnSoundSensor : public VnPort
#endif  // VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED

  VnSoundSensor(void);
  VnSoundSensor(uint8_t port);
  
#else // VN_PORT_DEFINED 

  VnSoundSensor(uint8_t out_pin);
  
#endif  // VN_PORT_DEFINED

  void setpin(uint8_t out_pin);
  bool readSoundSignal(void);
private:
  volatile uint8_t  _soundOut;
};
#endif
