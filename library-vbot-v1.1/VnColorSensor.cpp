/**
 * @ Copyright (C), 2018-2020, Vrobotx
 * \class   VnColorSensor
 * \brief   Driver for Vn Buzzer module.
 * @file    VnColorSensor.cpp
 * @author  Vrobotx
 * @version V1.0.0
 * @date    2019/12/30
 * @brief   Driver for Vn Buzzer module.
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
 * MeSerial class from SoftwareSerial.
 *
 * @ Method List:
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
 * <Author>`         `<Time>`        `<Version>`        `<Descr>`
 * Phan Dinh Bac       2019/04/11      1.0.0             Library for color sensor module
 * </pre>
 */
#include "VnColorSensor.h"


#ifdef VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * Buzzer pins are used and initialized here.
 * @Param : None
 */
VnColorSensor::VnColorSensor(void)
{
	_s2Pin		=	5;
	_s3Pin 		=	33;
	_outPin		=	4;
	_ctrPin 	= 	13;
   
   	pinMode(_s2Pin, OUTPUT);
	pinMode(_s3Pin, OUTPUT);
	pinMode(_outPin, INPUT);
	pinMode(_ctrPin, OUTPUT);

}

/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * If the hardware serial was selected, we will used the hardware serial.
 * @Param :  port - RJ25 port from PORT_1 to MATRIX
 */
VnColorSensor::VnColorSensor(uint8_t port):VnPort(port)
{
	_s2Pin		=	5;
	_s3Pin 		=	33;
	_outPin		=	s1;
	_ctrPin 	= 	s2;
   
   	pinMode(_s2Pin, OUTPUT);
	pinMode(_s3Pin, OUTPUT);
	pinMode(_outPin, INPUT);
	pinMode(_ctrPin, OUTPUT);
}

#else // VN_PORT_DEFINED
/**
 * Alternate Constructor which can call your own function to map the 74hc595 to arduino port,
 * @Param :  ser_pin 	- Pin correspond to the serial input data
 *			 clk_pin 	- Shift register clock
 *			 latch_pin 	- Pin emit signal load data from the shift to the storage register
 */
VnColorSensor::VnColorSensor(uint8_t s2Pin, uint8_t s3Pin, uint8_t outPin, uint8_t ctrPin)
{
	_s2Pin		=	s2Pin;	
	_s3Pin 		=	s3Pin;
	_outPin		=	outPin;
	_ctrPin 	= 	ctrPin;
   
   	pinMode(_s2Pin, OUTPUT);
	pinMode(_s3Pin, OUTPUT);
	pinMode(_outPin, INPUT);
	pinMode(_ctrPin, OUTPUT);
}
#endif // VN_PORT_DEFINED


/**
 * @Brief :  Enable color sensor
 * @Param :  None
 * @Retval : None.
 */
void VnColorSensor::enable_color_sensor(void)
{
	digitalWrite(_ctrPin, HIGH);
}
/**
 * @Brief :  Disable color sensor
 * @Param :  None
 * @Retval : None.
 */
void VnColorSensor::disable_color_sensor(void)
{
	digitalWrite(_ctrPin, LOW);
}

/**
 * @Brief :  Read function use to read color of object infont of color sensor
 * @Param :  *red - pointer point to memory cotain value of red part in object
 *			 *green - pointer point to memory cotain value of green part in object
 *			 *blue - pointer point to memory cotain value of blue part in object
 * @Retval : None.
 */
void VnColorSensor::read_color(int *red, int *green, int *blue)
{
	int redFrequency = 0;
	int greenFrequency = 0;
	int blueFrequency = 0;
	
	enable_color_sensor();

	// //Setting RED (R) filtered photodiodes to be read
	digitalWrite(_s2Pin, LOW);
	digitalWrite(_s3Pin, LOW);

	redFrequency = pulseIn(_outPin, LOW);
	*red = map(redFrequency, 198, 615, 255,0);
	
	// Serial.println(" ");
	// Serial.print("R = ");
	// Serial.print(redFrequency);
	delay(10);
	
	//Setting GREEN (G) filtered photodiodes to be read
	digitalWrite(_s2Pin, HIGH);
	digitalWrite(_s3Pin, HIGH);
	greenFrequency = pulseIn(_outPin, LOW);
	*green = map(greenFrequency, 512, 1100, 255, 0);
	
	// Serial.print(" ");
	// Serial.print("G = ");
    // Serial.print(greenFrequency);
	delay(10);
	
	// Setting BLUE (B) filtered photodiodes to be read
	digitalWrite(_s2Pin, LOW);
	digitalWrite(_s3Pin, HIGH);
	blueFrequency = pulseIn(_outPin, LOW);
	*blue = map(blueFrequency, 376, 974, 255, 0);
	
	// Serial.print(" ");
	// Serial.print("B = ");
	// Serial.print(blueFrequency);
	delay(10);
}

/**
 * @Brief :  Read function use to detect color from object 
 * @Param :  None
 * @Retval : Color of object if successful detect	
			 None color if fail detect 
 */
uint8_t VnColorSensor::detect_color(void)
{
	int red_part = 0, green_part = 0, blue_part = 0;
	short tmp_red= 0, tmp_green= 0, tmp_blue= 0;
	float red= 0, green= 0, blue= 0;
	
	int color = 0;

	read_color(&red_part, &green_part, &blue_part);
	
	// Serial.println(" ");
	// Serial.print("R = ");
	// Serial.print(red_part);
	
	// Serial.print(" ");
	// Serial.print("G = ");
	// Serial.print(green_part);
	
	// Serial.print(" ");
	// Serial.print("B = ");
	// Serial.print(blue_part);
	
	// if (red_part >= 189  && red_part <= 326   &&  green_part >= 229  && green_part <= 436   &&  blue_part >= 165  && blue_part <= 370)  
		// color = WHITE_COLOR;
	// else if (red_part >= -453 && red_part <= -45  &&  green_part >= -180 && green_part <= -60  &&  blue_part >= -263 && blue_part <= -15) 
		// color = BLACK_COLOR;
	// else if (red_part >= 143 && red_part <= 279   &&  green_part >= 164 && green_part <= 273  &&  blue_part >= 90 && blue_part <= 231) 
		// color = RED_COLOR;
	// else if (red_part >= -4 && red_part <= 12  &&  green_part >= 170 && green_part <= 286  &&  blue_part >= 63 && blue_part <= 162) 
		// color = GREEN_COLOR;
	// else if (red_part >= 218   && red_part <= 318   &&  green_part >= 307  && green_part <= 416   &&  blue_part >= 195 && blue_part <= 317)  
		// color = YELLOW_COLOR;
	// else if (red_part >= -71 && red_part <= -50  &&  green_part >= 111 && green_part <= 253  &&  blue_part >= 95 && blue_part <= 269)   
		// color = BLUE_COLOR;
	// else if (red_part >= 124  && red_part <= 257   &&  green_part >= 246 && green_part <= 385    &&  blue_part >= 180  && blue_part <= 321)  
		// color = GRAY_COLOR;
	// else  
		// color = 0;
	if (red_part < -700 && green_part < -700  && blue_part < -700)
		return 0;
	else if (red_part > green_part && red_part > blue_part) 
		return RED_COLOR;
	else if (green_part > red_part && red_part > blue_part) 
		return YELLOW_COLOR;
	else if (red_part > 255 && green_part > 255 && blue_part > 255)
		return WHITE_COLOR;
	else if (green_part > red_part && green_part > blue_part && green_part> 200)
		return GREEN_COLOR;
	else if (blue_part > red_part && blue_part > green_part)
		return BLUE_COLOR;
	else if (green_part > red_part && green_part > blue_part && green_part < 200)
		return BLACK_COLOR;

	
	return color;
}