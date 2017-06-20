#include "bmp085.h"

void bmp085_setup(void){
  FIO0DIR1_bit.P0_3=1; // sensor : reset as output (FIO0SET1_bit.P0_3)
  FIO0SET1_bit.P0_3=1; // sensor : released reset (set to 1)
  /* unused */ // sensor : eoc : FIO0SET1_bit.P0_2
}

void temp_startconv(void){
  bmp085_opencom_w();
  
  I2C0DAT=BMP085_I2C_ADDR_MEAS; // data to send: sensor ctrl reg @
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__TXDAT_ACK);
  
  I2C0DAT=BMP085_I2C_MEAS_TEMP; // data to send: sensor ctrl reg val : go temp conv
  i2c_clearStatus();
  i2c_wait_SI();
  i2c_stop();
  i2c_clearStatus();
}

int temp_read(void){
  unsigned char temp_msb;
  unsigned char temp_lsb;
  
  bmp085_opencom_w();
  
  I2C0DAT=BMP085_I2C_UTUP_MSB; // data to send: UT reg @
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__TXDAT_ACK);
  
  i2c_repStart(); // changes mode : now master receiver
  
  I2C0DAT=BMP085_I2C_ADDR_READ; // data to send: sensor addr (now reads)
  i2c_clearStatus();
  i2c_clearStart();
  i2c_wait_status(I2C_SMR__SLA_R_ACK);
  
  i2c_clearStatus();
  i2c_wait_status(I2C_SMR__RXDAT_ACK);
  temp_msb=I2C0DAT; // get temp msb
  i2c_ack_disable();
  i2c_clearStatus();
  i2c_wait_status(I2C_SMR__RXDAT_NACK);
  temp_lsb=I2C0DAT; // get temp lsb
  
  i2c_stop();
  i2c_clearStatus();
  
  return (temp_msb*256+temp_lsb);
}

void bmp085_opencom_w(void){
  i2c_clearStatus();
  i2c_start();
  i2c_wait_status(I2C_SMT__START);
  
  I2C0DAT=BMP085_I2C_ADDR_WRITE; // data to send: sensor addr
  i2c_clearStatus();
  i2c_clearStart();
  i2c_wait_status(I2C_SMT__SLA_W_ACK);
}