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

volatile uint16_t mper = 0xFFFF; // Period for motor PWM
//cout << "mdut = " << mdut << endl;

/// Set motor PWM frequency (Hz)
uint8_t set_motor_pwm_freq(uint8_t motor, uint16_t freq)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		if (freq > 45)
		{
			mper = (uint16_t) (3000000 / freq);
			if (mper < 1)
				mper = 1;
		}
		else
		{
			mper = 0xFFFF;
		}
		cout << "mper = " << mper << endl;
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
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t mdut = 0; // Motor PWM duty
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		if (power > 100)
			power = 100;
		mdut = uint16_t(
				(uint32_t) (power) * (uint32_t) (mper - 1)
						/ 100);
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
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t mctl = 0; // Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
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
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t mctl = 0; // Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
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

/// Set motor rotation time
uint8_t set_motor_time(uint8_t motor, uint32_t mtime)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		makeWriteRegPacket(s1, motor, MMTMR, mtime);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Set motor rotation angle
uint8_t set_motor_angle(uint8_t motor, uint32_t mangle)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		makeWriteRegPacket(s1, motor, MMANG, mangle);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Rotate motor by time (with direction and brake)
uint8_t rotate_motor_by_time(uint8_t motor, uint8_t direction, uint8_t brake)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t mctl = 0; // Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		if (direction)
			mctl = MOT_BACK;
		if (brake)
			mctl = mctl + MOT_BRAKE;
		mctl = mctl + MOT_ENABLE + MOT_POWER + MOT_AUTO;
		makeWriteRegPacket(s1, motor, MMCTL, mctl);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Rotate motor by angle (with direction and brake)
uint8_t rotate_motor_by_angle(uint8_t motor, uint8_t direction, uint8_t brake)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t mctl = 0; // Motor control register
	if ((motor == MOTOR1) || (motor == MOTOR2) || (motor == MOTOR3)
			|| (motor == MOTOR4))
	{
		if (direction)
			mctl = MOT_BACK;
		if (brake)
			mctl = mctl + MOT_BRAKE;
		mctl = mctl + MOT_ENABLE + MOT_POWER + MOT_AUTO + MOT_ANGLE;
		makeWriteRegPacket(s1, motor, MMCTL, mctl);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Enable async timer
uint8_t enable_async_timer(uint8_t tm_en)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t tctl = 0; // Timer control register
	if (tm_en)
		tctl = AT_EN;
	makeWriteRegPacket(s1, ASYNCTIMER, AATCTL, tctl);
	sendUSBPacket(s1, s1);
	return NO_ERROR;
}

/// Enable encoder
uint8_t enable_encoder(uint8_t encoder, uint8_t nwires, uint8_t pullup,
		uint8_t edge)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	uint16_t ectl = 0; // Encoder control register
	if ((encoder == ENCODER1) || (encoder == ENCODER2) || (encoder
			== ENCODER3) || (encoder == ENCODER4))
	{
		if (nwires)
			ectl = ENC_2WIRES;
		if (pullup)
			ectl = ectl + ENC_PUPEN;
		if (edge)
			ectl = ectl + ENC_FALL;
		ectl = ectl + ENC_ENABLE;
		makeWriteRegPacket(s1, encoder, EECTL, ectl);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Set/reset encoder value
uint8_t set_encoder_value(uint8_t encoder, uint32_t eval)
{
	char s1[MAX_STRING_LENGTH]; // Temp string
	if ((encoder == ENCODER1) || (encoder == ENCODER2) || (encoder
			== ENCODER3) || (encoder == ENCODER4))
	{
		makeWriteRegPacket(s1, encoder, EEVAL, eval);
		sendUSBPacket(s1, s1);
	}
	else
		return DEV_ADDR_ERROR;
	return NO_ERROR;
}

/// Read encoder value
uint32_t read_encoder_value(uint8_t encoder)
{
	char s1[MAX_STRING_LENGTH]; // Temp string variable
	char s2[MAX_STRING_LENGTH]; // Temp string variable
	uint8_t devaddr; // Returned device address
	uint8_t funccode; // Returned function code
	uint8_t regaddr; // Returned register address
	uint32_t regval = UINT32_MAX; // Returned register value
	uint16_t tmout = 0; // Reading timeout
	if ((encoder == ENCODER1) || (encoder == ENCODER2) || (encoder
			== ENCODER3) || (encoder == ENCODER4))
	{
		do
		{
			makeReadRegPacket(s1, encoder, EEVAL);
			sendUSBPacket(s1, s2);
			decodeReceivedPacket(s2, devaddr, funccode, regaddr,
					regval);
			tmout++;
		} while (((devaddr != encoder) || (regaddr != EEVAL)) && (tmout
				< TIME_OUT));
	}
	return regval;
}
