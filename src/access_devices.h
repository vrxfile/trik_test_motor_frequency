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

/// Set motor rotation time
uint8_t set_motor_time(uint8_t motor, uint32_t mtime);

/// Set motor rotation angle
uint8_t set_motor_angle(uint8_t motor, uint32_t mangle);

/// Rotate motor by time (with direction and brake)
uint8_t rotate_motor_by_time(uint8_t motor, uint8_t direction, uint8_t brake);

/// Rotate motor by angle (with direction and brake)
uint8_t rotate_motor_by_angle(uint8_t motor, uint8_t direction, uint8_t brake);

/// Enable async timer
uint8_t enable_async_timer(uint8_t tm_en);

/// Enable encoder
uint8_t enable_encoder(uint8_t encoder, uint8_t nwires, uint8_t pullup,
		uint8_t edge);

/// Set/reset encoder value
uint8_t set_encoder_value(uint8_t encoder, uint32_t eval);

/// Read encoder value
uint32_t read_encoder_value(uint8_t encoder);

#endif /* ACCESS_DEVICES_H_ */
