/********************************************************
 *
*    Used with ICCARM and AARM.
 *
 *    (c) Copyright IAR Systems 2006
 *
 *    File name   : main.c
 *    Description : Main module
 *
 *    History :
 *    1. Date        : 2, December 2006
 *       Author      : Stanimir Bonev
 *       Description : Create
 *
 *  This example project shows how to use the IAR Embedded Workbench for ARM
 * to develop code for the IAR LPC-2378-SK board. It shows basic use of the I/O,
 * the timer, the interrupt controllers and the LDC module for graphic and text
 * drawing.
 *  It starts by show the IAR logo on the LCD and after 5 second draw a test screen.
 *
 * Jumpers:
 *  PWR_SEL - depending of power source
 *  RST_E   - unfilled
 *  ISP_E   - unfilled
 *
 *  AN_TRIM - contrast / backlight
 *  BUT1    - adjust backlight
 *  BUT2    - adjust LCD contrast
 *
 * Note:
 *  After power-up the controller get clock from internal RC oscillator that
 * is unstable and may fail with J-Link auto detect, therefore adaptive clocking
 * should always be used. The adaptive clock can be select from menu:
 *  Project->Options..., section Debugger->J-Link/J-Trace  JTAG Speed - Adaptive.
 *  If Port 2 bits 0 - 9 are used by application PINSEL10 must be cleared and
 * this will disable trace port too.
 *
 *    $Revision: 38756 $
 **************************************************************************/
#include "includes.h"
#include "i2c.h"
#include "bmp085.h"

#define TIMER0_TICK_PER_SEC   20
#define DLY_100US             500

extern FontType_t Terminal_6_8_6;
extern FontType_t Terminal_9_12_6;
extern FontType_t Terminal_18_24_12;

volatile Boolean CntrSel = FALSE;
bool i = true;

/*************************************************************************
 * Function Name: Timer0IntrHandler
 * Parameters: none
 *
 * Return: none
 *
 * Description: Timer 0 interrupt handler
 *
 *************************************************************************/
void Timer0IntrHandler (void)
{
  static unsigned char state=0;
  
  if(state==0){
    FIO0SET1=0x20; // LED Off
    state=1;
  }else{
    FIO0CLR1=0x20; // LED On
    state=0;
  }
  
  // clear interrupt
  T0IR_bit.MR0INT = 1;
  VICADDRESS = 0;
}

/*************************************************************************
 * Function Name: ClearFlag
 * Parameters: void
 * Return: void
 *
 * Description: clear arg
 *		
 *************************************************************************/
void ClearFlag (void* arg)
{
int* pFlag = arg;
  *pFlag = 0;
}

/*************************************************************************
 * Function Name: DelayResolution100us
 * Parameters: Int32U Dly
 *
 * Return: none
 *
 * Description: Delay ~ (arg * 100us)
 *
 *************************************************************************/
void DelayResolution100us(Int32U Dly)
{
  for(; Dly; Dly--)
  {
    for(volatile Int32U j = DLY_100US; j; j--)
    {
    }
  }
}

/*************************************************************************
 * Function Name: DrawTable
 * Parameters: none
 *
 * Return: none
 *
 * Description: misc
 *
 *************************************************************************/
void DrawTable (void)
{
Int32U x,y,j,k;

// xxxxRRRRGGGGBBBB
const Int32U TableColor [] =
{
  0xFFF, 0xAAA, 0x888, 0x666, 0x444, 0x000,   // Grey
  0x00F, 0x00A, 0x008, 0x006, 0x004, 0x001,   // Red
  0x0F0, 0x0A0, 0x080, 0x060, 0x040, 0x010,   // Green
  0xF00, 0xA00, 0x800, 0x600, 0x400, 0x100,   // Blue
};

  for(y = 0; y < 4; ++y)
  {
    for(x = 0; x < 6; ++x)
    {
      // set rectangle
      k = (x*22) | ((((x+1)*22)-1)<<8);
      GLCD_SendCmd(CASET,(pInt8U)&k,0);
      k = (y*29) | ((((y+1)*29)-1)<<8);
      GLCD_SendCmd(RASET,(pInt8U)&k,0);
      // fill rectangle
      for(j = 0; j < (22*29); ++j)
      {
        GLCD_SendCmd(RAMWR,(pInt8U)&TableColor[x+(y*6)],2);
      }
    }
  }
}



/*************************************************************************
 * Function Name: main
 * Parameters: none
 *
 * Return: none
 *
 * Description: main
 *
 *************************************************************************/
int main(void){
  // MAM init
  MAMCR_bit.MODECTRL = 0;
  MAMTIM_bit.CYCLES = 3;    // FCLK > 40 MHz
  MAMCR_bit.MODECTRL = 2;   // MAM functions fully enabled
  
  // Init clock
  InitClock();
  
  // Init GPIO
  GpioInit();
  
  // Init LED
  FIO0DIR1=0x20; // pin as output for LED
  FIO0CLR1=0x20; // LED On Init
  
  // Init VIC
  VIC_Init();

  // Init Time0
  PCONP_bit.PCTIM0 = 1; // Enable TMR0 clk
  T0TCR_bit.CE = 0;     // counting  disable
  T0TCR_bit.CR = 1;     // set reset
  T0TCR_bit.CR = 0;     // release reset
  T0CTCR_bit.CTM = 0;   // Timer Mode: every rising PCLK edge
  T0MCR_bit.MR0I = 1;   // Enable Interrupt on MR0
  T0MCR_bit.MR0R = 1;   // Enable reset on MR0
  T0MCR_bit.MR0S = 0;   // Disable stop on MR0
  // set timer 0 period
  T0PR = 0;
  T0MR0 = SYS_GetFpclk(TIMER0_PCLK_OFFSET)/(TIMER0_TICK_PER_SEC);
  // init timer 0 interrupt
  T0IR_bit.MR0INT = 1;  // clear pending interrupt
  VIC_SetVectoredIRQ(Timer0IntrHandler,0,VIC_TIMER0);
  VICINTENABLE |= 1UL << VIC_TIMER0;
  T0TCR_bit.CE = 1;     // counting Enable

  __enable_interrupt();

  // GLCD_init
  GLCD_PowerUpInit(NULL);

  GLCD_Backlight(BACKLIGHT_ON);
  DelayResolution100us(30000);
  //DrawTable();

  GLCD_SetFont(&Terminal_9_12_6,0x000F00,0x00FF0);
  GLCD_SetWindow(0,116,131,131);
  GLCD_TextSetPos(0,0);

  // Init i2c
  i2cSetup();
  
  // Init bmp085 sensor
  bmp085_setup();
  
  // Votre programme commence ici

  //i2cTest();
  GLCD_print("Hello World.\n");
  
  while(1){
   
  }
}