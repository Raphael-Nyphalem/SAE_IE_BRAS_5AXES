#include "PCA9685.h"


void initialisation()
{
  init_executeur(R_MODE_1, DEFAULT_MODE1 | SLEEP);
  init_executeur(R_MODE_1, DEFAULT_MODE1 | SLEEP | EXT_CLK);
  init_executeur(R_PRE_SCALE, PRESCALER);
  init_executeur(R_MODE_1, DEFAULT_MODE1 | EXT_CLK);
  delayMicroseconds(500);
}

void init_executeur(uint8_t registre, uint8_t data)   
{
  Wire.beginTransmission(ADDRESS_PCA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error = Wire.endTransmission();

  if (error >=1 )
  {
    Serial.print("erreur d'envoie de donnée dans le fonction 'init_executeur' \nErreur : ");
    Serial.println(error);
  }
  
}


void mode1_envoie_de_donnees(pca9685 moteur)
{
  uint16_t dataFull;
  uint8_t error;

  uint8_t data_L;
  uint8_t data_H;

  uint16_t process_data;

  dataFull = uint16_t(( 1.5+ (moteur.angle / 180.0) ) / 20 * 4096);

  process_data = dataFull >> 8 & 0x000F; // bit de poid fort
  data_H = uint8_t(process_data);
  process_data = dataFull & 0x00FF; // bit de poid faible
  data_L = uint8_t(process_data);

  Wire.beginTransmission(ADDRESS_PCA);
  Wire.write(moteur.adresse);
  Wire.write(data_L);
  Wire.write(data_H);
  error = Wire.endTransmission();

    if (error >=1 )
  {
    Serial.print("erreur d'envoie de donnée dans le fonction 'envoyer_les_donnees' \nErreur : ");
    Serial.println(error);
  }
}

void envoyer_N_donnee(pca9685 tableau[])
{

}