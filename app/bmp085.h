#ifndef BMP085_H
#define BMP085_H

#include "includes.h"
#include "i2c.h"

/** main i2c @ BMP085 */
#define BMP085_I2C_ADDR_READ 0xEF
#define BMP085_I2C_ADDR_WRITE 0xEE

/** calibration coefficients @ and nb */
#define BMP085_I2C_ADDR_1STCOEFF 0xAA
#define BMP085_I2C_ADDR_NBYTECOEFF (unsigned char)22

/** temperature or pressure value UT/UP */
#define BMP085_I2C_UTUP_MSB 0xF6
#define BMP085_I2C_UTUP_LSB 0xF7
#define BMP085_I2C_UTUP_XLSB 0xF8

/** control register @ and values */
#define BMP085_I2C_ADDR_MEAS 0xF4
#define BMP085_I2C_MEAS_TEMP 0x2E
#define BMP085_I2C_MEAS_PRS0 0x34
#define BMP085_I2C_MEAS_PRS1 0x74
#define BMP085_I2C_MEAS_PRS2 0xB4
#define BMP085_I2C_MEAS_PRS3 0xF4

/*************************************************************************
 * Function Name: bmp085_setup
 * Parameters: void
 * Return: void
 *
 * Description: setup bmp085 sensor
 *		
 *************************************************************************/
void bmp085_setup(void);

/*************************************************************************
 * Function Name: temp_startconv
 * Parameters: void
 * Return: void
 *
 * Description: starts temperature conversion
 *		
 *************************************************************************/
void temp_startconv(void);

/*************************************************************************
 * Function Name: temp_read
 * Parameters: void
 * Return: int: raw temperature read from the sensor (16 bits format)
 *
 * Description: starts temperature conversion
 *		
 *************************************************************************/
int temp_read(void);

/*************************************************************************
 * Function Name: bmp085_opencom_w
 * Parameters: void
 * Return: void
 *
 * Description: opens i2c com with sensor (Write@)
 *		
 *************************************************************************/
void bmp085_opencom_w(void);

#endif
