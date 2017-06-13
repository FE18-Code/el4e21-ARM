/*************************************************************************
 *
 *    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2009
 *
 *
 *    File name   : sys.h
 *    Description : System driver include file
 *
 *    History :
 *    1. Date        : March 23, 2009
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *    $Revision: 30870 $
 **************************************************************************/

#include "board.h"

#ifndef __SYS_H
#define __SYS_H

#ifdef SYS_GLOBAL
#define SYS_EXTERN
#else
#define SYS_EXTERN  extern
#endif

/*************************************************************************
 * Function Name: irq_handler
 * Parameters: none
 *
 * Return: none
 *
 * Description: IRQ handler
 *
 *************************************************************************/
__irq __arm void IRQ_Handler (void);

/*************************************************************************
 * Function Name: VIC_Init
 * Parameters: void
 * Return: void
 *
 * Description: Initialize VIC
 *
 *************************************************************************/
void VIC_Init(void);

/*************************************************************************
 * Function Name: VIC_SetVectoredIRQ
 * Parameters:  void(*pIRQSub)()
 *              unsigned int VicIrqSlot
 *              unsigned int VicIntSouce
 *
 * Return: void
 *
 * Description:  Init vectored interrupts
 *
 *************************************************************************/
void VIC_SetVectoredIRQ(void(*pIRQSub)(), unsigned int Priority,
                        unsigned int VicIntSource);

/*************************************************************************
 * Function Name: InitClock
 * Parameters: void
 * Return: void
 *
 * Description: Initialize PLL and clocks' dividers. Hclk - 288MHz,
 * Usbclk - 48MHz
 *
 *************************************************************************/
void InitClock(void);

/*************************************************************************
 * Function Name: GpioInit
 * Parameters: void
 * Return: void
 *
 * Description: Reset all GPIO pins to default: primary function
 *
 *************************************************************************/
void GpioInit(void);

/*************************************************************************
 * Function Name: SYS_GetFsclk
 * Parameters: none
 * Return: Int32U
 *
 * Description: return Sclk [Hz]
 *
 *************************************************************************/
Int32U SYS_GetFsclk(void);

/*************************************************************************
 * Function Name: SYS_GetFpclk
 * Parameters: Int32U Periphery
 * Return: Int32U
 *
 * Description: return Pclk [Hz]
 *
 *************************************************************************/
Int32U SYS_GetFpclk(Int32U Periphery);

#endif //__SYS_H
