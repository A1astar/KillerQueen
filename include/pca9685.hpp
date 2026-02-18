#ifndef PCA9685_HPP
#define PCA9685_HPP

// ===== Libs =====
#include <driver/i2c_master.h>

// ===== Hardware addr =====
#define PCA9685_ADDR 0x40

// ===== Registers =====
#define MODE1_REG 0x00
#define MODE2_REG 0x01
#define SUBADDR1_REG 0x02
#define SUBADDR2_REG 0x03
#define SUBADDR3_REG 0x04
#define ALLCALLADR_REG 0x05
#define LED0_ON_L_REG 0x06
#define LED0_ON_H_REG 0x07
#define LED0_OFF_L_REG 0x08
#define LED0_OFF_H_REG 0x09
#define LED1_ON_L_REG 0x0A
#define LED1_ON_H_REG 0x0B
#define LED1_OFF_L_REG 0x0C
#define LED1_OFF_H_REG 0x0D
#define LED2_ON_L_REG 0x0E
#define LED2_ON_H_REG 0x0F
#define LED2_OFF_L_REG 0x10
#define LED2_OFF_H_REG 0x11
#define LED3_ON_L_REG 0x12
#define LED3_ON_H_REG 0x13
#define LED3_OFF_L_REG 0x14
#define LED3_OFF_H_REG 0x15
#define LED4_ON_L_REG 0x16
#define LED4_ON_H_REG 0x17
#define LED4_OFF_L_REG 0x18
#define LED4_OFF_H_REG 0x19
#define LED5_ON_L_REG 0x1A
#define LED5_ON_H_REG 0x1B
#define LED5_OFF_L_REG 0x1C
#define LED5_OFF_H_REG 0x1D
#define LED6_ON_L_REG 0x1E
#define LED6_ON_H_REG 0x1F
#define LED6_OFF_L_REG 0x20
#define LED6_OFF_H_REG 0x21
#define LED7_ON_L_REG 0x22
#define LED7_ON_H_REG 0x23
#define LED7_OFF_L_REG 0x24
#define LED7_OFF_H_REG 0x25
#define LED8_ON_L_REG 0x26
#define LED8_ON_H_REG 0x27
#define LED8_OFF_L_REG 0x28
#define LED8_OFF_H_REG 0x29
#define LED9_ON_L_REG 0x2A
#define LED9_ON_H_REG 0x2B
#define LED9_OFF_L_REG 0x2C
#define LED9_OFF_H_REG 0x2D
#define LED10_ON_L_REG 0x2E
#define LED10_ON_H_REG 0x2F
#define LED10_OFF_L_REG 0x30
#define LED10_OFF_H_REG 0x31
#define LED11_ON_L_REG 0x32
#define LED11_ON_H_REG 0x33
#define LED11_OFF_L_REG 0x34
#define LED11_OFF_H_REG 0x35
#define LED12_ON_L_REG 0x36
#define LED12_ON_H_REG 0x37
#define LED12_OFF_L_REG 0x38
#define LED12_OFF_H_REG 0x39
#define LED13_ON_L_REG 0x3A
#define LED13_ON_H_REG 0x3B
#define LED13_OFF_L_REG 0x3C
#define LED13_OFF_H_REG 0x3D
#define LED14_ON_L_REG 0x3E
#define LED14_ON_H_REG 0x3F
#define LED14_OFF_L_REG 0x40
#define LED14_OFF_H_REG 0x41
#define LED15_ON_L_REG 0x42
#define LED15_ON_H_REG 0x43
#define LED15_OFF_L_REG 0x44
#define LED15_OFF_H_REG 0x45
#define ALL_LED_ON_L_REG 0xFA
#define ALL_LED_ON_H_REG 0xFB
#define ALL_LED_OFF_L_REG 0xFC
#define ALL_LED_OFF_H_REG 0xFD
#define PRESCALE_REG 0xFE
#define TESTMODE_REG 0xFF

// ===== MODE1 register bits =====
#define RESTART (1 << 7)
#define EXTCLK (1 << 6)
#define AI (1 << 5)
#define SLEEP (1 << 4)
#define SUB1 (1 << 3)
#define SUB2 (1 << 2)
#define SUB3 (1 << 1)
#define ALLCALL (1 << 0)

// ===== MODE2 register bits =====
#define INVRT (1 << 4)
#define OCH (1 << 3)
#define OUTDRV (1 << 2)
#define OUTNE1 (1 << 1)
#define OUTNE0 (1 << 0)

/**
 * @brief Initialize a new I2C connection for PCA9685.
 *
 * @param addr address of the device.
 * @param sda sda GPIO of the device.
 * @param scl scl GPIO of the device.
 * @return
 * - `0` on I2C setup successfully, `-1` on error.
 */
int pca9685_init(uint16_t addr, gpio_num_t sda, gpio_num_t scl);

/**
 * @brief Setup the frequency at which the outputs modulate
 * @param freq_hz the choosen frequence Hz (min: 24Hz, max: 1526Hz)
 * @return
 * `0` on I2C setup successfully, `-1` on error.
 */
int pca9685_pwm(uint16_t freq_hz);

#endif
