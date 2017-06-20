#ifndef I2C_H
#define I2C_H

#include "includes.h"
#include "bmp085.h"

/*************************************************************************
 * Function Name: i2cSetup
 * Parameters: void
 * Return: void
 *
 * Description: setup i2c
 *		
 *************************************************************************/
void i2cSetup(void);

/*************************************************************************
 * Function Name: i2cTest
 * Parameters: void
 * Return: void
 *
 * Description: setup i2c
 *		
 *************************************************************************/
void i2cTest(void);

/*************************************************************************
 * Function Name: i2c_clearStatus
 * Parameters: void
 * Return: void
 *
 * Description: clears SI bit
 *		
 *************************************************************************/
void i2c_clearStatus(void);

/*************************************************************************
 * Function Name: i2c_start
 * Parameters: void
 * Return: void
 *
 * Description: sets STA bit
 *		
 *************************************************************************/
void i2c_start(void);

/*************************************************************************
 * Function Name: i2c_clearStart
 * Parameters: void
 * Return: void
 *
 * Description: clears STA bit
 *		
 *************************************************************************/
void i2c_clearStart(void);

/*************************************************************************
 * Function Name: i2c_stop
 * Parameters: void
 * Return: void
 *
 * Description: sets STO bit
 *		
 *************************************************************************/
void i2c_stop(void);

/*************************************************************************
 * Function Name: i2c_ack_enable
 * Parameters: void
 * Return: void
 *
 * Description: sets AA bit
 *		
 *************************************************************************/
void i2c_ack_enable(void);

/*************************************************************************
 * Function Name: i2c_ack_disable
 * Parameters: void
 * Return: void
 *
 * Description: clears AA bit
 *		
 *************************************************************************/
void i2c_ack_disable(void);

/*************************************************************************
 * Function Name: i2c_wait_status
 * Parameters: status_code: the value of I2C0STAT reg to wait for
 * Return: void
 *
 * Description: blocking function waiting for I2C0STAT to be equal to param1
 *		
 *************************************************************************/
void i2c_wait_status(unsigned char status_code);

#endif
