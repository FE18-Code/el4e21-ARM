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

#endif
