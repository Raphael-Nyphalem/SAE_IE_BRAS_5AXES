#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PSA = 0x7F;


const uint8_t R_MODE_1= 0x00;
const uint8_t R_PRE_SCALE = 0xFE;


const uint8_t DEFAULT_MODE1 = 0x31;  
const uint8_t PRESCALER = 25000000/4096/50;


/**
 * @brief 
 * 
 */
void initialisation();

/**
 * @brief 
 * 
 * @param registre 
 * @param data 
 */
void ecrire_sur_un_registre(uint8_t registre, uint8_t data);

/***/
void ecrire_sur_4_registre(uint8_t registre_n, uint8_t data[4]);

void setup() {
  Wire.begin();
  initialisation();

  uint8_t data[4];
  data[0] =0X00;
  data[1] =0X00;
  data[2] =0XFF;
  data[3] =0X07;
  ecrire_sur_4_registre(0x06,data);
}

void loop() {
  
}

void initialisation(){
  ecrire_sur_un_registre(R_MODE_1,DEFAULT_MODE1 | 0x10);
  ecrire_sur_un_registre(R_PRE_SCALE,PRESCALER);
  ecrire_sur_un_registre(R_MODE_1,DEFAULT_MODE1);
}

void ecrire_sur_un_registre(uint8_t registre, uint8_t data){
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error =  Wire.endTransmission();
}

void ecrire_sur_4_registre(uint8_t registre_n,uint8_t data[4])
{
  uint8_t data_ON_L = data[0];
  uint8_t data_ON_H = data[1] & 0x1F;
  uint8_t data_OFF_L= data[2];
  uint8_t data_OFF_H= data[3]& 0x1F;

  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre_n);
  Wire.write(data_ON_L);
  Wire.write(data_ON_H);
  Wire.write(data_OFF_L);
  Wire.write(data_OFF_H);
  uint8_t error =  Wire.endTransmission();

}