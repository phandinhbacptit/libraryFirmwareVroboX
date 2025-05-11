/**
 * @ Copyright (C), 2012-2016, Vrobotx
 * \class VnEncoder
 * \brief   Driver for Me line follwer device.
 * @file    VnEncoder.cpp
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
 * @example LineFollowerTest.ino
 */

#include "VnEncoder.h"                                    

#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * no pins are used or initialized here.
 * @Param :  None
 */
VnEncoder::VnEncoder(void) : VnPort(0)
{

}

/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnEncoder::VnEncoder(uint8_t port) : VnPort(port)
{
	_inA_M1		=	33;
	_inB_M1 	=	5;
	_inA_M2		=	s1;
	_inB_M2		= 	s2;
	pinMode(_inA_M1,INPUT);
	pinMode(_inB_M1,INPUT);
	pinMode(_inA_M2,INPUT);
	pinMode(_inB_M2,INPUT);
	lastState_M1 = digitalRead(_inA_M1);
	lastState_M2 = digitalRead(_inA_M2);
}
#else // VN_PORT_DEFINED 
/**
 * Alternate Constructor which can call your own function to map the line follwer device to arduino port,
 * it will assigned the input pin.
 * @Param :  Sensor1 - arduino port(should digital pin)
 *           Sensor2 - arduino port(should digital pin)
 */
VnEncoder::VnEncoder(uint8_t InA_M1, uint8_t InB_M1, uint8_t InA_M2,uint8_t InB_M2)
{
	_inA_M1 = InA_M1;
	_inB_M1 = InB_M1;
	_inA_M2 = InA_M2;
	_inB_M2 = InB_M2;
	pinMode(_inA_M1, INPUT);
	pinMode(_inB_M1, INPUT);
	pinMode(_inA_M2, INPUT);
	pinMode(_inB_M2, INPUT);
	lastState_M1 = digitalRead(_inA_M1);
	lastState_M2 = digitalRead(_inA_M2);
}
#endif // VN_PORT_DEFINED

/** 
 * @Brief :  Reset the line follwer device available PIN by its arduino port.
 * @Param :  Sensor1 - arduino port(should digital pin)
 *           Sensor2 - arduino port(should digital pin)
 * @Retval : None
 */
void VnEncoder::setpin(uint8_t InA_M1, uint8_t InB_M1, uint8_t InA_M2,uint8_t InB_M2)
{
  _inA_M1 = InA_M1;
  _inB_M1 = InB_M1;
  _inA_M2 = InA_M2;
  _inB_M2 = InB_M2;
  pinMode(_inA_M1, INPUT);
  pinMode(_inB_M1, INPUT);
  pinMode(_inA_M2, INPUT);
  pinMode(_inB_M2, INPUT);
#ifdef VN_PORT_DEFINED
  s1 = _inA_M2;
  s2 = _inB_M2;
#endif // VN_PORT_DEFINED
}

/**
 * @Brief :  Get the sensors state.
 * @Retval :
 *   (0x00)-S1_IN_S2_IN:   sensor1 and sensor2 are both inside of black line \n
 *   (0x01)-S1_IN_S2_OUT:  sensor1 is inside of black line and sensor2 is outside of black line \n
 *   (0x02)-S1_OUT_S2_IN:  sensor1 is outside of black line and sensor2 is inside of black line \n
 *   (0x03)-S1_OUT_S2_OUT: sensor1 and sensor2 are both outside of black line
 */
uint8_t VnEncoder::readPulse(int32_t *PulseM1, int32_t *PulseM2)
{
	curState_M1 = digitalRead(_inA_M1);
	curState_M2 = digitalRead(_inA_M2);
		
	if (curState_M1 != lastState_M1  && curState_M1 == 1){
		if (digitalRead(_inB_M1) != curState_M1) {
			*PulseM1 -= 1;
		} else {
			*PulseM1 += 1;
		}
	}
	
	if (curState_M2 != lastState_M2  && curState_M2 == 1){
		if (digitalRead(_inB_M2) != curState_M2) {
			*PulseM2 -= 1;
		} else {
			*PulseM2 += 1;
		}
	}
	lastState_M1 = curState_M1;
	lastState_M2 = curState_M2;
	
	return 0;
}

// /**
 // * @Brief :  Get the sensors1(left sensors) state.
 // * @Retval :
 // *   0: sensor1 is inside of black line \n
 // *   1: sensor1 is outside of black line
 // */
// bool VnEncoder::readSensor1(void)
// {
// #ifdef VN_PORT_DEFINED
  // return(VnPort::dRead1(INPUT) );
// #else // VN_PORT_DEFINED
  // return digitalRead(_inA);
// #endif // VN_PORT_DEFINED
// }

// /**
 // * @Brief :  Get the sensors2(right sensors) state.
 // * @Retval :
 // *   0: sensor1 is inside of black line \n
 // *   1: sensor1 is outside of black line
 // */
// bool VnEncoder::readSensor2(void)
// {
// #ifdef VN_PORT_DEFINED
	// return(VnPort::dRead2(INPUT) );
// #else // VN_PORT_DEFINED
  // return digitalRead(_inB);
// #endif // VN_PORT_DEFINED
// }

