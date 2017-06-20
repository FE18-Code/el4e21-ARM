#ifndef BMP085_H
#define BMP085_H

#include "includes.h"

#define BMP085_I2C_ADDR_READ 0xEF
#define BMP085_I2C_ADDR_WRITE 0xEE
#define BMP085_I2C_FIRST_REG 0xAA

/*************************************************************************
 * Function Name: bmp085_setup
 * Parameters: void
 * Return: void
 *
 * Description: setup bmp085 sensor
 *		
 *************************************************************************/
void bmp085_setup(void);

#endif
