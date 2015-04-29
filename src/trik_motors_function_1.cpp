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

	enable_async_timer(1);
	enable_encoder(ENCODER1, 1, 1, 1);
	set_encoder_value(ENCODER1, 0);
	cout << "encoder1 = " << read_encoder_value(ENCODER1) << endl;
	set_motor_pwm_freq(MOTOR1, 1000);
	set_motor_power(MOTOR1, 50);
	start_motor(MOTOR1, 0);
	myDelay();
	myDelay();
	myDelay();
	cout << "encoder1 = " << read_encoder_value(ENCODER1) << endl;
	start_motor(MOTOR1, 1);
	myDelay();
	myDelay();
	myDelay();
	cout << "encoder1 = " << read_encoder_value(ENCODER1) << endl;
	stop_motor(MOTOR1, 1);
	cout << "encoder1 = " << read_encoder_value(ENCODER1) << endl;
	set_encoder_value(ENCODER1, 0);
	cout << "encoder1 = " << read_encoder_value(ENCODER1) << endl;

	// Close MSP430 USB device
	disconnect_USBMSP();

	return 0;
}
