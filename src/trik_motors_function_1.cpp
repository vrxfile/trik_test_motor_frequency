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
#include <math.h>

#include "usbMSP430Defines.h"
#include "usbMSP430Interface.h"
#include "access_devices.h"

using namespace std;

#define MIN_TRESHOLD	128 	// Minimum treshold for encoder value
#define MAX_TRESHOLD	10000 	// Maximum treshold for encoder value

double rot0[128];		// Array of numrot elements
double der1[128];		// First derivative of set of rotnumbers
double der2[128];		// Second derivative of set of rotnumbers
uint8_t num0 = 0;		// Number of elements in rot1
uint8_t num1 = 0;		// Number of elements in der1
uint8_t num2 = 0;		// Number of elements in der2
uint16_t startpwr0 = 0;		// Minimum power value that starts motor

// Statistical data
double mat0 = 0;
double mat1 = 0;
double mat2 = 0;
double xmin0 = 0;
double xmin1 = 0;
double xmin2 = 0;
double xmax0 = 0;
double xmax1 = 0;
double xmax2 = 0;
double mid0 = 0;
double mid1 = 0;
double mid2 = 0;
double ran0 = 0;
double ran1 = 0;
double ran2 = 0;
double dis0 = 0;
double dis1 = 0;
double dis2 = 0;
double sqo0 = 0;
double sqo1 = 0;
double sqo2 = 0;

FILE* repdescr;			// Report file descriptor
#define REPFILENAME		"motor_report.txt"

char stmp1[128];		// Temp string

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

	// Make report file
	repdescr = fopen(REPFILENAME, "w");
	fprintf(repdescr, "Motor report file\n");
	fprintf(repdescr, "FRQ\t\tSTDDEV0\t\tSTDDEV1\t\tSTDDEV2\t\tMINSTART\n");
	fclose(repdescr);

	uint32_t enc = 0;	// Encoder value
	uint32_t oldenc = 0;	// Old encoder value
	uint8_t timeout = 0;	// Timeout counter
	double numrot = 0;	// Number of rotations per 1% power
	for (uint16_t frq = 50; frq < 5000; frq += 50)
	{
		num0 = 0;
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
			cout << "FRQ=" << (uint16_t)frq << " PWR=" << (uint16_t)pwr << " ENC=" << (uint32_t)enc;
			if (enc < MIN_TRESHOLD)
				enc = 0;
			if (enc > MAX_TRESHOLD)
				enc = 0;
			if (pwr != 0)
				numrot = (double)enc / (double)pwr;
			else
				numrot = 0;
			cout << " ROT=" << numrot << endl;
			// Numrotations array
			if (numrot != 0)
			{
				rot0[num0] = numrot;
				num0++;
			}
			oldenc = enc;
			timeout = 0;
		}
		// Derivative 1 array
		for (uint8_t i = 0; i < (num0 - 1); i++)
		{
			der1[i] = rot0[i] - rot0[i+1];
		}
		num1 = num0 - 1;
		// Derivative 2 array
		for (uint8_t i = 0; i < (num1 - 1); i++)
		{
			der2[i] = der1[i] - der1[i+1];
		}
		num2 = num1 - 1;
		// Math expectation
		mat0 = 0;
		for (uint8_t i = 0; i < num0; i++)
		{
			mat0 = mat0 + rot0[i];
		}
		mat0 = mat0 / num0;
		mat1 = 0;
		for (uint8_t i = 0; i < num1; i++)
		{
			mat1 = mat1 + der1[i];
		}
		mat1 = mat1 / num1;
		mat2 = 0;
		for (uint8_t i = 0; i < num2; i++)
		{
			mat2 = mat2 + der2[i];
		}
		mat2 = mat2 / num2;
		// Min and max
		xmin0 = rot0[0];
		xmax0 = rot0[0];
		xmin1 = der1[0];
		xmax1 = der1[0];
		xmin2 = der2[0];
		xmax2 = der2[0];
		for (uint8_t i = 0; i < num0; i++)
		{
			if (rot0[i] < xmin0) xmin0 = rot0[i];
			if (rot0[i] > xmax0) xmax0 = rot0[i];
		}
		for (uint8_t i = 0; i < num1; i++)
		{
			if (der1[i] < xmin1) xmin1 = der1[i];
			if (der1[i] > xmax1) xmax1 = der1[i];
		}
		for (uint8_t i = 0; i < num2; i++)
		{
			if (der2[i] < xmin2) xmin2 = der2[i];
			if (der2[i] > xmax2) xmax2 = der2[i];
		}
		// Ranges
		ran0 = xmax0 - xmin0;
		ran1 = xmax1 - xmin1;
		ran2 = xmax2 - xmin2;
		// Midranges
		mid0 = xmin0 + (ran0 / 2);
		mid1 = xmin1 + (ran1 / 2);
		mid2 = xmin2 + (ran2 / 2);
		// Dispersion (variance)
		dis0 = 0;
		for (uint8_t i = 0; i < num0; i++)
		{
			dis0 = dis0 + ((mat0 - rot0[i])*(mat0 - rot0[i]));
		}
		dis0 = dis0 / num0;
		dis1 = 0;
		for (uint8_t i = 0; i < num1; i++)
		{
			dis1 = dis1 + ((mat1 - der1[i])*(mat1 - der1[i]));
		}
		dis1 = dis1 / num1;
		dis2 = 0;
		for (uint8_t i = 0; i < num2; i++)
		{
			dis2 = dis2 + ((mat2 - der2[i])*(mat2 - der2[i]));
		}
		dis2 = dis2 / num2;
		// Standard deviation
		sqo0 = sqrt(dis0);
		sqo1 = sqrt(dis1);
		sqo2 = sqrt(dis2);
		// Minimum power value
		startpwr0 = 100 - (2 * num0) + 2;

		cout << "Numrotations array:" << endl;
		for (uint8_t i = 0; i < num0; i++)
			cout << rot0[i] << " ";
		cout << endl;
		cout << "Number of measures = " << (uint16_t)num0 << endl;
		cout << "Min. start power (%) = " << startpwr0 << endl;
		cout << "Xmin = " << xmin0 << endl;
		cout << "Xmax = " << xmax0 << endl;
		cout << "Math. exp. (avg) = " << mat0 << endl;
		cout << "Range = " << ran0 << endl;
		cout << "Middle range = " << mid0 << endl;
		cout << "Variance = " << dis0 << endl;
		cout << "Std. deviation = " << sqo0 << endl;

		cout << "Derivative 1 array:" << endl;
		for (uint8_t i = 0; i < num1; i++)
			cout << der1[i] << " ";
		cout << endl;
		cout << "Xmin = " << xmin1 << endl;
		cout << "Xmax = " << xmax1 << endl;
		cout << "Math. exp. (avg) = " << mat1 << endl;
		cout << "Range = " << ran1 << endl;
		cout << "Middle range = " << mid1 << endl;
		cout << "Variance = " << dis1 << endl;
		cout << "Std. deviation = " << sqo1 << endl;

		cout << "Derivative 2 array:" << endl;
		for (uint8_t i = 0; i < num2; i++)
			cout << der2[i] << " ";
		cout << endl;
		cout << "Xmin = " << xmin2 << endl;
		cout << "Xmax = " << xmax2 << endl;
		cout << "Math. exp. (avg) = " << mat2 << endl;
		cout << "Range = " << ran2 << endl;
		cout << "Middle range = " << mid2 << endl;
		cout << "Variance = " << dis2 << endl;
		cout << "Std. deviation = " << sqo2 << endl;

		repdescr = fopen(REPFILENAME, "a");
		fprintf(repdescr, "%05d\t\t%5.3f\t\t%5.3f\t\t%5.3f\t\t%05d\n", frq, sqo0, sqo1, sqo2, startpwr0);
		fclose(repdescr);
	}

	// Close MSP430 USB device
	disconnect_USBMSP();

	return 0;
}
