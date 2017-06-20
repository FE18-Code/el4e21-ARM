#ifndef I2C_H
#define I2C_H

#include "includes.h"
#include "bmp085.h"

/** Status Code (I2CSTAT) in Master Transmitter mode */
#define I2C_SMT__START 0x08 /**< A START condition has been transmitted */
#define I2C_SMT__REPSTART 0x10 /**< A repeated START condition has been transmitted */
#define I2C_SMT__SLA_W_ACK 0x18 /**< SLA+W has been transmitted; ACK has been received */
#define I2C_SMT__SLA_W_NACK 0x20 /**< SLA+W has been transmitted; NOT ACK has been received */
#define I2C_SMT__TXDAT_ACK 0x28 /**< Data byte in I2DAT has been transmitted; ACK has been received */
#define I2C_SMT__TXDAT_NACK 0x30 /**< Data byte in I2DAT has been transmitted; NOT ACK has been received */
#define I2C_SMT__ARBLOST 0x38 /**< Arbitration lost in SLA+R/W or Data bytes */

/** Status Code (I2CSTAT) in Master Receiver mode */
#define I2C_SMR__START 0x08 /**< A START condition has been transmitted */
#define I2C_SMR__REPSTART 0x10 /**< A repeated START condition has been transmitted */
#define I2C_SMR__NACK_ARBLOST 0x38 /**< Arbitration lost in NOT ACK bit */
#define I2C_SMR__SLA_R_ACK 0x40 /**< SLA+R has been transmitted; ACK has been received */
#define I2C_SMR__SLA_R_NACK 0x48 /**< SLA+R has been transmitted; NOT ACK has been received */
#define I2C_SMR__RXDAT_ACK 0x50 /**< Data byte has been received; ACK has been returned */
#define I2C_SMR__RXDAT_NACK 0x58 /**< Data byte has been received; NOT ACK has been returned */

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

/*************************************************************************
 * Function Name: i2c_wait_SI
 * Parameters: void
 * Return: void
 *
 * Description: blocking function waiting for SI flag to raise
 *		
 *************************************************************************/
void i2c_wait_SI(void);

/*************************************************************************
 * Function Name: i2c_repStart
 * Parameters: void
 * Return: void
 *
 * Description: blocking function doing a repeated start and waiting for status
 *		
 *************************************************************************/
void i2c_repStart();

#endif
