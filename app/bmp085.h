#ifndef BMP085_H
#define BMP085_H

#include "includes.h"
#include "i2c.h"

/** quick macro for 16 bits merge */
#define MSBLSB(MSB, LSB)  ((MSB)*256+(LSB))

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

/** typedef for coefficients */
typedef struct{
  unsigned short AC4;
  unsigned short AC5;
  unsigned short AC6;
  short AC1;
  short AC2;
  short AC3;
  short B1;
  short B2;
  short MB;
  short MC;
  short MD;
  unsigned long B4;
  unsigned long B7;
  long X1;
  long X2;
  long X3;
  long B3;
  long B5;
  long B6;
  long T;
  long UT;
  long UP;
  long P;
}t_bmp085_coeffs;

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
 * Parameters: t_bmp085_coeffs*: output struct to store temp value
 * Return: void
 *
 * Description: starts temperature conversion
 *		
 *************************************************************************/
void temp_read(t_bmp085_coeffs *vals);

/*************************************************************************
 * Function Name: param_read
 * Parameters: t_bmp085_coeffs*: coeff structs to fill
 * Return: void
 *
 * Description: reads parameters from E2PROM
 *		
 *************************************************************************/
void param_read(t_bmp085_coeffs *coeffs);

/*************************************************************************
 * Function Name: temp_compute
 * Parameters: t_bmp085_coeffs*: input/output values struct
 * Return: long: temperature converted
 *
 * Description: converts raw temp read to some more real value
 *		
 *************************************************************************/
long temp_compute(t_bmp085_coeffs *v);

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
