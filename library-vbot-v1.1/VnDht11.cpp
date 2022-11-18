/**
 * @ Copyright (C), 2018-2020, VrobotX
 * \class   VnDht11
 * \brief   Driver for DHT11 sensor module.
 * @file    VnDht11.cpp
 * @author  VrobotX
 * @version V1.0.0
 * @date   2018/07/20
 * @brief   Driver for DHT11 sensor module.
 *
 * @ Copyright
 * This software is Copyright (C), 2018-2020, VrobotX. Use is subject to license \n
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
 * This file is a drive for DHT11 sensor device, The DHT11 sensor inherited the 
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
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
#include "VnDht11.h"

// DHT dht(dht_pin, DHT11);
  
#ifdef VN_PORT_DEFINED

/**
 * Alternate Constructor which can call your own function to map the DHT11 sensor to arduino port,
 * Single Led pins are used and initialized here.
 * @Param : None
 */
VnDht11::VnDht11(void) : VnPort()
{

}

/**
 * Alternate Constructor which can call your own function to map the Single Led to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to M2
 */
VnDht11::VnDht11(uint8_t port) : VnPort(port)
{
  dht_pin = s1;
  Serial.print("data: ");
  Serial.println(dht_pin);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the Single Led to arduino port,
 * @Param :  switchPin - arduino port for Single Led detect pin.
 */
VnDht11::VnDht11(int pin)
{
  dht_pin = pin;
}
#endif // VN_PORT_DEFINED

/**
 * @Brief :  Reset the Single Led available pin by its arduino port.
 * @Param :  pin - arduino port for Single Led detect pin.
 * @Retval : None
 * @Others : None
 */
void VnDht11::setpin(int pin)
{
	dht_pin = pin;
#ifdef VN_PORT_DEFINED
	s2 = pin;
#endif
}
/**
 * @Brief :  Read Humidity value from sensor
 * @Param :  None
 * @Retval : Humidity value
 * @Others : None
 */
float VnDht11::readHumidity()
{
    // dht.readHumidity();    //Đọc độ ẩm
}
/**
 * @Brief :  Read Temperature value from sensor
 * @Param :  None
 * @Retval : Temperature value
 * @Others : None
 */
float VnDht11::readTemp()
{
    // dht.readTemperature();    //Đọc độ ẩm
}