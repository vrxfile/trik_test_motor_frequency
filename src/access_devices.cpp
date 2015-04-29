/*
 * access_devices.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: Rostislav Varzar
 */

#include <iostream>
#include <stdint.h>
#include "usbMSP430Defines.h"
#include "usbMSP430Interface.h"
#include "access_devices.h"

using namespace std;

volatile uint16_t mper = 1; // Period for motor PWM
//cout << "mdut = " << mdut << endl;

/// Set motor PWM frequency (Hz)
uint8_t set_motor_pwm_freq(uint8_t motor, uint16_t freq)
{
	char s1[MAX_STRING_LENGTH];	// Temp string
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3) || (motor == MOTOR4))
	{
		if (freq > 0)
		{
			mper = (uint16_t)(3000000 / freq);
			if (mper < 1)
				mper = 1;
		}
		else
		{
			mper = 1;
		}
		makeWriteRegPacket(s1, motor, MMPER, mper);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Set motor power (0...100%)
uint8_t set_motor_power(uint8_t motor, uint8_t power)
{
	char s1[MAX_STRING_LENGTH];	// Temp string
	uint16_t mdut = 0;		// Motor PWM duty
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3) || (motor == MOTOR4))
	{
		if (power > 100)
			power = 100;
		mdut = uint16_t((uint32_t)(power) * (uint32_t)(mper - 1) / 100);
		makeWriteRegPacket(s1, motor, MMDUT, mdut);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Start motor (with direction)
uint8_t start_motor(uint8_t motor, uint8_t direction)
{
	char s1[MAX_STRING_LENGTH];	// Temp string
	uint16_t mctl = 0;		// Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3) || (motor == MOTOR4))
	{
		if (direction)
			mctl = MOT_BACK;
		mctl = mctl + MOT_ENABLE + MOT_POWER;
		makeWriteRegPacket(s1, motor, MMCTL, mctl);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Stop motor (with brake function)
uint8_t stop_motor(uint8_t motor, uint8_t brake)
{
	char s1[MAX_STRING_LENGTH];	// Temp string
	uint16_t mctl = 0;		// Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3) || (motor == MOTOR4))
	{
		if (brake)
			mctl = MOT_BRAKE;
		mctl = mctl + MOT_ENABLE;
		makeWriteRegPacket(s1, motor, MMCTL, mctl);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}



/// Init motors 1 and 2
void init_motors_12()
{
	char s1[MAX_STRING_LENGTH];	// Temp string

	makeWriteRegPacket(s1, MOTOR1, MMPER, 0x5000);
	sendUSBPacket(s1, s1);
	makeWriteRegPacket(s1, MOTOR1, MMDUT, 0x4000);
	sendUSBPacket(s1, s1);

	makeWriteRegPacket(s1, MOTOR2, MMPER, 0x5000);
	sendUSBPacket(s1, s1);
	makeWriteRegPacket(s1, MOTOR2, MMDUT, 0x4000);
	sendUSBPacket(s1, s1);
}

/// Start 1 and 2 motors
void start_motors_12()
{
	char s1[MAX_STRING_LENGTH];	// Temp string

	makeWriteRegPacket(s1, MOTOR1, MMCTL, MOT_ENABLE + MOT_POWER);
	sendUSBPacket(s1, s1);

	makeWriteRegPacket(s1, MOTOR2, MMCTL, MOT_ENABLE + MOT_POWER);
	sendUSBPacket(s1, s1);
}

/// Stop 1 and 2 motors
void stop_motors_12()
{
	char s1[MAX_STRING_LENGTH];	// Temp string

	makeWriteRegPacket(s1, MOTOR1, MMCTL, MOT_ENABLE + MOT_BRAKE);
	sendUSBPacket(s1, s1);

	makeWriteRegPacket(s1, MOTOR2, MMCTL, MOT_ENABLE + MOT_BRAKE);
	sendUSBPacket(s1, s1);
}

/// Init analog sensors 1, 2 and 3
void init_sensors_123()
{
	char s1[MAX_STRING_LENGTH];	// Temp string

	makeWriteRegPacket(s1, SENSOR1, SSCTL, SENS_ENABLE + SENS_READ);
	sendUSBPacket(s1, s1);
	makeWriteRegPacket(s1, SENSOR1, SSIDX, ANALOG_INP);
	sendUSBPacket(s1, s1);

	makeWriteRegPacket(s1, SENSOR2, SSCTL, SENS_ENABLE + SENS_READ);
	sendUSBPacket(s1, s1);
	makeWriteRegPacket(s1, SENSOR2, SSIDX, ANALOG_INP);
	sendUSBPacket(s1, s1);

	makeWriteRegPacket(s1, SENSOR3, SSCTL, SENS_ENABLE + SENS_READ);
	sendUSBPacket(s1, s1);
	makeWriteRegPacket(s1, SENSOR3, SSIDX, ANALOG_INP);
	sendUSBPacket(s1, s1);
}

/// Read data of first sensor
uint32_t read_sensor_1()
{
	char s1[MAX_STRING_LENGTH];		    // Temp string variable
	char s2[MAX_STRING_LENGTH];		    // Temp string variable
	uint32_t errcode;			    // Returned error code
	uint8_t devaddr;			    // Returned device address
	uint8_t funccode;			    // Returned function code
	uint8_t regaddr;			    // Returned register address
	uint32_t regval=UINT32_MAX;		    // Returned register value
	uint16_t tmout = 0;			    // Reading timeout

	do
	{
		makeReadRegPacket(s1, SENSOR1, SSVAL);
		errcode = sendUSBPacket(s1, s2);
		errcode = decodeReceivedPacket(s2, devaddr, funccode, regaddr, regval);
		tmout ++;
	} while (((devaddr != SENSOR1) || (regaddr != SSVAL)) && (tmout < TIME_OUT));
	return regval;
}

/// Read data of second sensor
uint32_t read_sensor_2()
{
	char s1[MAX_STRING_LENGTH];		    // Temp string variable
	char s2[MAX_STRING_LENGTH];		    // Temp string variable
	uint32_t errcode;			    // Returned error code
	uint8_t devaddr;			    // Returned device address
	uint8_t funccode;			    // Returned function code
	uint8_t regaddr;			    // Returned register address
	uint32_t regval=UINT32_MAX;		    // Returned register value
	uint16_t tmout = 0;			    // Reading timeout

	do
	{
		makeReadRegPacket(s1, SENSOR2, SSVAL);
		errcode = sendUSBPacket(s1, s2);
		errcode = decodeReceivedPacket(s2, devaddr, funccode, regaddr, regval);
		tmout ++;
	} while (((devaddr != SENSOR2) || (regaddr != SSVAL)) && (tmout < TIME_OUT));
	return regval;
}

/// Read data of third sensor
uint32_t read_sensor_3()
{
	char s1[MAX_STRING_LENGTH];		    // Temp string variable
	char s2[MAX_STRING_LENGTH];		    // Temp string variable
	uint32_t errcode;			    // Returned error code
	uint8_t devaddr;			    // Returned device address
	uint8_t funccode;			    // Returned function code
	uint8_t regaddr;			    // Returned register address
	uint32_t regval=UINT32_MAX;		    // Returned register value
	uint16_t tmout = 0;			    // Reading timeout

	do
	{
		makeReadRegPacket(s1, SENSOR3, SSVAL);
		errcode = sendUSBPacket(s1, s2);
		errcode = decodeReceivedPacket(s2, devaddr, funccode, regaddr, regval);
		tmout ++;
	} while (((devaddr != SENSOR3) || (regaddr != SSVAL)) && (tmout < TIME_OUT));
	return regval;
}
