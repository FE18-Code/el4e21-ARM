#include "i2c.h"

void i2cSetup(void){
  // Clear previous config (if any)
  I2C0CONCLR=0x6C;
  
  //1. Power: In the PCONP register (Table 4�46), set bit PCI2C0/1/2.
  PCONP_bit.PCI2C0=1; // set to 1 at reset
  
  //2. Clock: In PCLK_SEL0 select PCLK_I2C0; in PCLK_SEL1 select PCLK_I2C1/2
  PCLKSEL0_bit.PCLK_I2C0=1;
  
  //3. Pins: Select I2C pins and their modes in PINSEL0 to PINSEL4 and PINMODE0 to PINMODE4
  PINSEL1_bit.P0_27=0x01;
  PINSEL1_bit.P0_28=0x01;

  //4. Interrupts are enabled in the VIC using the VICIntEnable register (Table 7�71).
  
  //5. Initialization: see Section 21�9.12.1 and Section 21�10.1.
  // Duty Cycle Registers (Half Word)
  I20SCLH=200;
  I20SCLL=240;
  // I2EN = 1
  I2C0CONSET=0x40;
}

void i2cTest(void){
  unsigned char i=0;
  
  i2c_clearStatus();
  i2c_start();
  i2c_wait_status(I2C_SMT__START);
  
  I2C0DAT=BMP085_I2C_ADDR_WRITE; // data to send: sensor addr
  i2c_clearStatus();
  i2c_clearStart();
  i2c_wait_status(I2C_SMT__SLA_W_ACK);
  
  I2C0DAT=BMP085_I2C_ADDR_1STCOEFF; // data to send: 1st reg addr to read
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__TXDAT_ACK);
  
  i2c_ack_enable();
  i2c_start();
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__REPSTART); // changes mode : now master receiver
  
  I2C0DAT=BMP085_I2C_ADDR_READ; // data to send: sensor addr (now reads)
  i2c_clearStatus();
  i2c_clearStart();
  i2c_wait_status(I2C_SMR__SLA_R_ACK);
  
  i2c_clearStatus();  
  for(i=0;i<22;i++){
    i2c_wait_status(I2C_SMR__RXDAT_ACK);
    i2c_clearStatus();
    /* cp values to table */
  }
}

/* i2c utils fcts */
void i2c_clearStatus(void){
  I2C0CONCLR=0x08; // clear status (SIC)
}

void i2c_start(void){
  I2C0CONSET=0x20; // set start (STA)
}

void i2c_clearStart(void){
  I2C0CONCLR=0x20; // clr start (CSTA)
}

void i2c_stop(void){
  I2C0CONSET=0x10; // set stop (STO)
}

void i2c_ack_enable(void){
  I2C0CONSET=0x04; // set ack (AA)
}

void i2c_ack_disable(void){
  I2C0CONCLR=0x04; // clr ack (AAC)
}

void i2c_wait_status(unsigned char status_code){
  while((I2C0STAT)!=status_code); // waits...
}

void i2c_wait_SI(void){
  while((I2C0CONSET&0x08)!=0x08); // waits ...
}

void i2c_repStart(){
  i2c_ack_enable();
  i2c_start();
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__REPSTART); // changes mode : now master receiver
}
