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

void temp_read(t_bmp085_coeffs *vals){
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
  temp_lsb=I2C0DAT; // get temp lsb - read last byte
  
  i2c_stop();
  i2c_clearStatus();
  
  vals->UT=MSBLSB(temp_msb, temp_lsb);
}

void param_read(t_bmp085_coeffs *coeffs){
  unsigned char i;
  unsigned char tabcoeffs[BMP085_I2C_ADDR_NBYTECOEFF];
  
  bmp085_opencom_w();
  
  I2C0DAT=BMP085_I2C_ADDR_1STCOEFF; // data to send: coeffs reg @
  i2c_clearStatus();
  i2c_wait_status(I2C_SMT__TXDAT_ACK);
  
  i2c_repStart(); // changes mode : now master receiver
  
  I2C0DAT=BMP085_I2C_ADDR_READ; // data to send: sensor addr (now reads)
  i2c_clearStatus();
  i2c_clearStart();
  i2c_wait_status(I2C_SMR__SLA_R_ACK);
  
  for(i=0;i<BMP085_I2C_ADDR_NBYTECOEFF-1;i++){
    i2c_clearStatus();
    i2c_wait_status(I2C_SMR__RXDAT_ACK);
    tabcoeffs[i]=I2C0DAT; // get values
  }
  i2c_ack_disable();
  i2c_clearStatus();
  i2c_wait_status(I2C_SMR__RXDAT_NACK);
  tabcoeffs[BMP085_I2C_ADDR_NBYTECOEFF-1]=I2C0DAT; //read last byte
  
  i2c_stop();
  i2c_clearStatus();
  
  coeffs->AC1=MSBLSB(tabcoeffs[0], tabcoeffs[1]);
  coeffs->AC2=MSBLSB(tabcoeffs[2], tabcoeffs[3]);
  coeffs->AC3=MSBLSB(tabcoeffs[4], tabcoeffs[5]);
  coeffs->AC4=MSBLSB(tabcoeffs[6], tabcoeffs[7]);
  coeffs->AC5=MSBLSB(tabcoeffs[8], tabcoeffs[9]);
  coeffs->AC6=MSBLSB(tabcoeffs[10], tabcoeffs[11]);
  coeffs->B1=MSBLSB(tabcoeffs[12], tabcoeffs[13]);
  coeffs->B2=MSBLSB(tabcoeffs[14], tabcoeffs[15]);
  coeffs->MB=MSBLSB(tabcoeffs[16], tabcoeffs[17]);
  coeffs->MC=MSBLSB(tabcoeffs[18], tabcoeffs[19]);
  coeffs->MD=MSBLSB(tabcoeffs[20], tabcoeffs[21]);
}

long temp_compute(t_bmp085_coeffs *v){
  v->X1=(((v->UT)-(v->AC6))*v->AC5/32768);
  v->X2=(v->MC*2048/((v->X1)+(v->MD)));
  v->B5=((v->X1)+(v->X2));
  v->T=((v->B5+8)*16);
  
  return v->T;
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