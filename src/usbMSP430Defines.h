/*
 * usbMSP430Interface.h
 *
 *  Created on: March 17, 2015
 *	Author: Rostislav Varzar
 */

#ifndef USBMSP430DEFINES_H
#define USBMSP430DEFINES_H

/// USB devices addresses
#define MOTOR1			0x00
#define MOTOR2			0x01
#define MOTOR3			0x03
#define MOTOR4			0x02
#define SENSOR1			0x04
#define SENSOR2			0x05
#define SENSOR3			0x06
#define SENSOR4			0x07
#define SENSOR5			0x08
#define SENSOR6			0x09
#define SENSOR7			0x0A
#define SENSOR8			0x0B
#define SENSOR9			0x0C
#define SENSOR10		0x0D
#define SENSOR11		0x0E
#define SENSOR12		0x0F
#define SENSOR13		0x10
#define SENSOR14		0x11
#define SENSOR15		0x12
#define SENSOR16		0x13
#define SENSOR17		0x14
#define SENSOR18		0x15
#define ENCODER1		0x16
#define ENCODER2		0x17
#define ENCODER3		0x19
#define ENCODER4		0x18
#define PORT1			0x1A
#define PORT2			0x1B
#define PORT3			0x1C
#define PORT4			0x1D
#define PORT5			0x1E
#define PORT6			0x1F
#define PORTJ			0x20
#define PWM1			0x21
#define PWM2			0x22
#define PWM3			0x23
#define PWM4			0x24
#define SENSCTRL		0x25
#define ASYNCTIMER		0x26
#define TOUCHDEVICE		0x27
#define I2C1			0x28
#define I2C2			0x29
#define I2C3			0x2A
#define I2C4			0x2B
#define I2C5			0x2C
#define I2C6			0x2D
#define I2C7			0x2E
#define BSL			0xEE
#define NNONE			0xFF

/// Motor registers
#define MMCTL			0x00
#define MMDUT			0x01
#define MMPER			0x02
#define MMANG			0x03
#define MMTMR			0x04
#define MMVAL			0x05
#define MMERR			0x06

/// Masks for bits of control register
#define MOT_ENABLE		0x8000	// Motor enable
#define MOT_AUTO		0x4000	// Autostop mode
#define MOT_ANGLE		0x2000	// Angle autostop mode
#define MOT_BACK		0x0010	// Backward direction
#define MOT_BRAKE		0x0008	// Brake enable
#define MOT_POWER		0x0003	// Motor power

/// Default motor period
#define DEF_MOT_PER		0x3000	// Default motor period in uS

/// Encoder registers
#define EECTL			0x00
#define EEVAL			0x01
#define EESTA			0x02

/// Masks for bits of control register
#define ENC_ENABLE		0x8000	// Enable bit
#define ENC_ASYNC		0x4000	// Async mode
#define ENC_2WIRES		0x2000	// 2-wires mode
#define ENC_PUPEN		0x1000	// Pull up resistors
#define ENC_FALL		0x0800	// Falling edge select

/// Sensor registers
#define SSCTL			0x00
#define SSIDX			0x01
#define SSVAL			0x02
#define SSSTA			0x03

/// Sensor types
#define DIGITAL_INP		0x0000
#define ANALOG_INP		0x0001

/// Masks for bits of control register
#define SENS_ENABLE		0x8000	// Enable bit
#define SENS_ASYNC		0x4000	// Async mode
#define SENS_PULL		0x2000	// Pull up resistors
#define SENS_READ		0x0001	// Sensor read

/// Software I2C registers
#define IICTL			0x00
#define IIDEV			0x01
#define IIREG			0x02
#define IIDAT			0x03
#define IIERR			0x04
#define IIIDX			0x05
#define IIVAL			0x06
#define IIDEL			0x07
#define IIVER			0x08

/// Masks for bits of control register
#define I2C_ENABLE		0x80	// I2C enable
#define I2C_READ		0x20	// I2C read
#define I2C_WRITE		0x40	// I2C write
#define I2C_SENS		0x10	// I2C read sensor

/// Software I2C sensors addresses
#define NXTTEMP			0x0000
#define HMC5883L_X		0x0001
#define HMC5883L_Y		0x0002
#define HMC5883L_Z		0x0003

/// Timer registers defines
#define AATCTL			0x00
#define AATPER			0x01
#define AATVAL			0x02
#define AATVER			0x03

/// Timer enable mask bit
#define AT_EN			0x0003

#define MAX_STRING_LENGTH	0x20

#define WRITE_FUNC		0x03
#define READ_FUNC		0x05

/// Error defines
#define NO_ERROR		0x00
#define FUNC_CODE_ERROR		0x01
#define REG_ADDR_ERROR		0x02
#define REG_VAL_ERROR		0x03
#define SLAVE_ERROR		0x04
#define SLAVE_BUSY		0x06
#define DEV_ADDR_ERROR		0x11
#define CRC_ERROR		0x12
#define START_ERROR		0x13
#define LENGTH_ERROR		0x14
#define REG_INC_ERROR		0x15
#define UNDEF_ERROR		0xFF

/// HEX number sizes
#define NUM_BYTE		0x02
#define NUM_WORD		0x04
#define NUM_DWORD		0x08

#define RECV_PACK_LEN		0x12

/// Errors for response
#define NO_ERROR		0x00
#define DEVICE_ERROR		0x01
#define PACKET_ERROR		0x02

#define TIME_OUT		0xFFFF

#define USB_DEV_NAME		"/dev/ttyACM0"

#endif // USBMSP430DEFINES_H

