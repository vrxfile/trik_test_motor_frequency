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
	set_motor_power(MOTOR1, 0);
	set_motor_time(MOTOR1, 5000);

	// Init encoder 1
	enable_encoder(ENCODER1, 1, 1, 1);

	for (uint16_t frq = 10; frq < 1000; frq += 10)
	{
		set_motor_pwm_freq(MOTOR1, frq);
		set_motor_pwm_freq(MOTOR1, frq);
		for (uint8_t pwr = 5; pwr <= 100; pwr += 5)
		{
			encoder_fail:
			set_motor_power(MOTOR1, pwr);
			set_motor_power(MOTOR1, pwr);
			set_encoder_value(ENCODER1, 0);
			set_encoder_value(ENCODER1, 0);
			rotate_motor_by_time(MOTOR1, 0, 1);
			rotate_motor_by_time(MOTOR1, 0, 1);
			myDelay();
			myDelay();
			myDelay();
			myDelay();
			uint32_t enc = read_encoder_value(ENCODER1);
			if (enc > 16383)
				goto encoder_fail;
			cout << "FRQ=" << (uint16_t)frq << " PWR=" << (uint16_t)pwr << " ENC=" << (uint32_t)enc << endl;
		}
	}


	// Close MSP430 USB device
	disconnect_USBMSP();

	return 0;
}
