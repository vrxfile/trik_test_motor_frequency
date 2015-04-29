/*
 * usbMSP430Interface.h
 *
 *  Created on: March 17, 2015
 *	Author: Rostislav Varzar
 */

#ifndef USBMSP430INTERFACE_H
#define USBMSP430INTERFACE_H

#include <stdint.h>

/// Extract number from packet
uint32_t hex2num(char *string				// Input string
		, uint16_t pos				// Start position
		, uint16_t numsize);			// Number size

/// Make write register packet
void makeWriteRegPacket(char *msp_packet		// Created packet string
			, uint8_t dev_addr		// Device address
			, uint8_t reg_addr		// Registers address to write
			, uint32_t reg_val);		// Value to write

/// Make read register packet
void makeReadRegPacket(char *msp_packet			// Created packet string
			, uint8_t dev_addr		// Device address
			, uint8_t reg_addr);		// Register address to read

/// Function for decoding received packet
uint32_t decodeReceivedPacket(char *msp_packet		// Input MSP430 USB packet string
				, uint8_t &dev_addr	// Decoded response device address
				, uint8_t &func_code	// Decoded function number (read/write)
				, uint8_t &reg_addr	// Decoded register address
				, uint32_t &reg_val);	// Decoded register value

/// Init USB TTY device
uint32_t init_USBTTYDevice();

/// Send USB packet
uint32_t sendUSBPacket(char *in_msp_packet		// Packet to send
			, char *out_msp_packet);	// Received packet

/// Connect to USB MSP430 device
uint32_t connect_USBMSP();

/// Disconnect from USB MSP430 device
uint32_t disconnect_USBMSP();

#endif // USBMSP430INTERFACE_H

