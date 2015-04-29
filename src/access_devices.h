/*
 * access_devices.h
 *
 *  Created on: Mar 18, 2015
 *      Author: Rostislav Varzar
 */

#ifndef ACCESS_DEVICES_H_
#define ACCESS_DEVICES_H_

/// Set motor PWM frequency (Hz)
uint8_t set_motor_pwm_freq(uint8_t motor, uint16_t freq);

/// Set motor power (0...100%)
uint8_t set_motor_power(uint8_t motor, uint8_t power);

/// Start motor (with direction)
uint8_t start_motor(uint8_t motor, uint8_t direction);

/// Stop motor (with brake function)
uint8_t stop_motor(uint8_t motor, uint8_t brake);

#endif /* ACCESS_DEVICES_H_ */
