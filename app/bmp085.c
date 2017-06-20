#include "bmp085.h"

/*************************************************************************
 * Function Name: bmp085_setup
 * Parameters: void
 * Return: void
 *
 * Description: setup bmp085_setup sensor
 *		
 *************************************************************************/
void bmp085_setup(void){
  FIO0DIR1_bit.P0_3=1; // sensor : reset as output (FIO0SET1_bit.P0_3)
  FIO0SET1_bit.P0_3=1; // sensor : released reset (set to 1)
  /* unused */ // sensor : eoc : FIO0SET1_bit.P0_2
}
