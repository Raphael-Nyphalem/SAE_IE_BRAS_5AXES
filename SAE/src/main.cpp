#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PSA = 0x7F;


const uint8_t R_MODE_1= 0x00;
const uint8_t R_PRE_SCALE = 0xFE;


const uint8_t DEFAULT_MODE1 = 0x11;  
const uint8_t PRESCALER = 25000000/(4096*50);



void initialisation();
void ecrire_1_registre(uint8_t registre, uint8_t data);


void setup() {
  Wire.begin();
  initialisation();

  ecrire_1_registre(0x06,0x00);
  ecrire_1_registre(0x07,0x00);
  ecrire_1_registre(0x08,0x00);
  ecrire_1_registre(0x09,0x00);
}

void loop() {
  
}

void initialisation(){
  uint8_t sleep_a_1= 0x10;
  ecrire_1_registre(R_MODE_1,sleep_a_1);
  ecrire_1_registre(R_PRE_SCALE,PRESCALER);
  ecrire_1_registre(R_MODE_1,DEFAULT_MODE1);
}

void ecrire_1_registre(uint8_t registre, uint8_t data){
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error =  Wire.endTransmission();
}