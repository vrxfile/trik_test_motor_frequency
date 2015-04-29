//============================================================================
// Name        : trik_motors_function_1.cpp
// Author      : Rostislav Varzar
// Version     :
// Copyright   : Free license
// Description : C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

#include "usbMSP430Defines.h"
#include "usbMSP430Interface.h"
#include "access_devices.h"

using namespace std;

// Delay approx 1 second
void myDelay()
{
	for (uint32_t d = 0; d < 5000000; d++)
		uint32_t a = d - d + d;
}

int main()
{
	// Open MSP430 USB device
	connect_USBMSP();

	// Init async timer
	enable_async_timer(1);

	// Init motor1
	set_motor_pwm_freq(MOTOR1, 100);
	set_motor_power(MOTOR1, 50);
	set_motor_time(MOTOR1, 4000);

	// Init encoder 1
	enable_encoder(ENCODER1, 1, 1, 1);

	uint32_t enc = 0;	// Encoder value
	uint32_t oldenc = 0;	// Old encoder value
	uint8_t timeout = 0;	// Timeout counter
	float numrot = 0;	// Number of rotations per 1% power
	for (uint16_t frq = 50; frq < 1000; frq += 10)
	{
		set_motor_pwm_freq(MOTOR1, frq);
		set_motor_pwm_freq(MOTOR1, frq);
		for (uint8_t pwr = 2; pwr <= 100; pwr += 2)
		{
			encoder_fail:
			timeout ++;
			set_motor_power(MOTOR1, pwr);
			set_motor_power(MOTOR1, pwr);
			set_encoder_value(ENCODER1, 0);
			set_encoder_value(ENCODER1, 0);
			rotate_motor_by_time(MOTOR1, 0, 1);
			rotate_motor_by_time(MOTOR1, 0, 1);
			usleep(1000000);
			enc = read_encoder_value(ENCODER1);
			// May be some situations when encoder read fail or motor doesn't start
			if (timeout > 1)
				cout << "ERROR! TIMEOUT = " << (uint16_t)timeout << endl;
			// Very big value
			if ((enc > 10000) && (timeout < 16))
				goto encoder_fail;
			// Motor didn't start
			if ((enc == 0) && (pwr > 10) && (timeout < 16))
				goto encoder_fail;
			// New value less than old value
//			if ((enc < oldenc) && (timeout < 16))
//				goto encoder_fail;
			if (pwr != 0)
				numrot = (float)enc / (float)pwr;
			else
				numrot = 0;
			cout << "FRQ=" << (uint16_t)frq << " PWR=" << (uint16_t)pwr << " ENC=" << (uint32_t)enc << " ROT=" << numrot << endl;
			oldenc = enc;
			timeout = 0;
		}
	}



	// Close MSP430 USB device
	disconnect_USBMSP();

	return 0;
}
