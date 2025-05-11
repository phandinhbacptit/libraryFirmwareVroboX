/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnEncoder
 * \brief   Driver for Me line follwer device.
 * @file    VnEncoder.h
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Header for for VnEncoder.cpp module
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
 *    1. void VnEncoder::setpin(uint8_t Sensor1,uint8_t Sensor2)
 *    2. uint8_t VnEncoder::readSensors(void)
 *    3. bool VnEncoder::readSensor1(void)
 *    4. bool VnEncoder::readSensor1(void)
 *
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac         2018/07/20     1.0.0            Rebuild the old lib.
 * </pre>
 *
 */
#ifndef VnEncoder_H
#define VnEncoder_H

#include <stdint.h>
#include <stdbool.h>
#include <Arduino.h>
#include "VnConfig.h"
//#include "VbotBoard.h"

#ifdef VN_PORT_DEFINED
#include "VnPort.h"
#endif // VN_PORT_DEFINED

#define S1_IN_S2_IN   (0x00)    // sensor1 and sensor2 are both inside of black line
#define S1_IN_S2_OUT  (0x01)    // sensor1 is inside of black line and sensor2 is outside of black line
#define S1_OUT_S2_IN  (0x02)    // sensor1 is outside of black line and sensor2 is inside of black line
#define S1_OUT_S2_OUT (0x03)    // sensor1 and sensor2 are both outside of black line

/**
 * Class: VnEncoder
 * @Brief :
 * Declaration of Class VnEncoder.
 */
#ifndef VN_PORT_DEFINED
class VnEncoder
#else // !VN_PORT_DEFINED
class VnEncoder : public VnPort
#endif  // VN_PORT_DEFINED
{
public:
#ifdef VN_PORT_DEFINED

  VnEncoder(void);
  VnEncoder(uint8_t port);
  
#else // VN_PORT_DEFINED 

  VnEncoder(uint8_t InA_M1, uint8_t InB_M1, uint8_t InA_M2,uint8_t InB_M2);
  
#endif  // VN_PORT_DEFINED

  void setpin(uint8_t InA_M1, uint8_t InB_M1, uint8_t InA_M2,uint8_t InB_M2);
  uint8_t readPulse(int32_t *PulseM1, int32_t *PulseM2);
  // bool readSensor1(void);
  // bool readSensor2(void);
private:
  volatile uint8_t  _inA_M1;
  volatile uint8_t  _inB_M1;
  volatile uint8_t  _inA_M2;
  volatile uint8_t  _inB_M2;
  volatile int32_t curState_M1;
  volatile int32_t lastState_M1;
  
  volatile int32_t curState_M2;
  volatile int32_t lastState_M2;
};
#endif
