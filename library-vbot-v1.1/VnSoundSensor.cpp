/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnSoundSensor
 * \brief   Driver for Me line follwer device.
 * @file    VnSoundSensor.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2018/07/20
 * @brief   Driver for Me line follwer device.
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
 * 1. void VnSoundSensor::setpin(uint8_t out_pin)
 * 2. bool VnSoundSensor::readSoundSignal(void)
 * @ History:
 * <pre>
 * `<Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac         2020/02/08    1.0.1            Rebuild the old lib.
 * </pre>
 *
 * @example LineFollowerTest.ino
 */

#include "VnSoundSensor.h"                                    

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the sound sensor device to arduino port
 * no pins are used or initialized here.
 * @Param :  None
 */
VnSoundSensor::VnSoundSensor(void) : VnPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the sound sensor device to arduino port
 * @Param :  port - RJ25 port from PORT_4
 */
VnSoundSensor::VnSoundSensor(uint8_t port) : VnPort(port)
{

}
#else // VN_PORT_DEFINED 
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * incase we not using VN_PORT_DEFINED define it will assigned the out pin.
 * @Param :  out_pin - Output pin of sound sensor
 */
VnSoundSensor::VnSoundSensor(uint8_t out_pin)
{
  _soundOut = out_pin;
  pinMode(_soundOut, INPUT);
}
#endif // VN_PORT_DEFINED

/** 
 * @Brief :  Set pin using for out sound sensor signal
 * @Param :  out_pin - Output pin of sound sensor
 * @Retval : None
 */
void VnSoundSensor::setpin(uint8_t out_pin)
{
  _soundOut = out_pin;
  pinMode(_soundOut, INPUT);
#ifdef VN_PORT_DEFINED
  _soundOut = s1;
#endif // VN_PORT_DEFINED
}

/**
 * @Brief :  Get the sound sensor state.
 * @Retval :
 *   0: No sound is detected
 *   1: Sound detected
 */
bool VnSoundSensor::readSoundSignal(void)
{
#ifdef VN_PORT_DEFINED
	return(VnPort::dRead1(INPUT) );
#else // VN_PORT_DEFINED
  return digitalRead(_soundOut);
#endif // VN_PORT_DEFINED
}

// Test merge library

