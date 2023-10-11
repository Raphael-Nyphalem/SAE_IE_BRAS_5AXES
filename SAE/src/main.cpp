#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PSA = 0x7F;


const uint8_t R_MODE_1= 0x00;
const uint8_t R_PRE_SCALE = 0xFE;


const uint8_t DEFAULT_MODE1 = 0x11;  
const uint8_t PRESCALER = 25000000/(4096*50);



void initialisation();
void ecrire_sur_un_registre(uint8_t registre, uint8_t data);
void ecrire_sur_4_registre(uint8_t registre_n, 
                        uint8_t data_ON_L,
                        uint8_t data_ON_H,
                        uint8_t data_OFF_L,
                        uint8_t data_OFF_H
                        );

void setup() {
  Wire.begin();
  initialisation();
}

void loop() {
  
}

void initialisation(){
  uint8_t sleep_a_1= 0x10;
  ecrire_sur_un_registre(R_MODE_1,sleep_a_1);
  ecrire_sur_un_registre(R_PRE_SCALE,PRESCALER);
  ecrire_sur_un_registre(R_MODE_1,DEFAULT_MODE1);
}

void ecrire_sur_un_registre(uint8_t registre, uint8_t data){
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error =  Wire.endTransmission();
}

void ecrire_sur_4_registre(uint8_t registre_n,uint8_t data_ON_L,uint8_t data_ON_H,uint8_t data_OFF_L,uint8_t data_OFF_H)
{
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(R_MODE_1);
  Wire.write(DEFAULT_MODE1 | 0x20);
  uint8_t error =  Wire.endTransmission();

  if (error == 0)
  {
    Wire.beginTransmission(ADDRESS_PSA);
    Wire.write(registre_n);
    Wire.write(data_ON_L);
    Wire.write(data_ON_H);
    Wire.write(data_OFF_L);
    Wire.write(data_OFF_H);
    error =  Wire.endTransmission();
    if (error == 0)
    {
      Wire.beginTransmission(ADDRESS_PSA);
      Wire.write(R_MODE_1);
      Wire.write(DEFAULT_MODE1 | 0x20);
      error =  Wire.endTransmission();

    }
  }
}