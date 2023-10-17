#include "PCA9685.h"


void initialisation()
{
  init_executeur(R_MODE_1, DEFAULT_MODE1 | SLEEP);
  init_executeur(R_PRE_SCALE, PRESCALER);
  init_executeur(R_MODE_1, DEFAULT_MODE1);
  delayMicroseconds(500);
}

void init_executeur(uint8_t registre, uint8_t data)   
{
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error = Wire.endTransmission();
}


void saisie_commande_utilisateur(uint8_t vecteur[TAILLE])
{
  uint8_t angle_choisi;
  char moteur_choisi;
  bool stupid_proof_flag = true;

  Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
  Serial.println(' ');
  while (stupid_proof_flag == true)
  {
    
    if (Serial.available())
    {
      moteur_choisi = Serial.read();
      //Serial.println(moteur_choisi);
      switch (moteur_choisi)
      {
      case 'A':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_A;
        stupid_proof_flag = false;
        break;
      case 'B':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_B;
        stupid_proof_flag = false;
        break;
      case 'C':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_C;
        stupid_proof_flag = false;
        break;
      case 'D':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_D;
        stupid_proof_flag = false;
        break;
      case 'E':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_E;
        stupid_proof_flag = false;
        break;
      case ('h','H'):
        Serial.println("motor A -> rotation of the base of the arm on the z axis");
        Serial.println("motor B -> rotation of the arm attach to the base on the x axis");
        Serial.println("motor C -> rotation of the middle arm on the x axis");
        Serial.println("motor A -> rotation of the part of the arm attach to the clamp the x axis");
        Serial.println("motor A -> opens and closes the clamp");
        Serial.println(' ');
        Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
        Serial.println(' ');
        break;
      default:
        Serial.println("well,... if you can not read I can't do much for you ಠ_ಠ");
        Serial.println(' ');
        Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
        Serial.println(' ');
        break;
      }
    }
  }
    stupid_proof_flag = true;
  
  while (stupid_proof_flag == true)
  {
    if (Serial.available())
    {
      Serial.println("choose an angle between 0 and 180");
      angle_choisi = Serial.readStringUntil('\n').toInt();
      if (angle_choisi<=180)
      {
        vecteur[VECTEUR_ANGLE]=angle_choisi;
        Serial.println("choice saved");

        stupid_proof_flag = false;
      }
      else
      {
        Serial.println("[ERROR] - out of bounds");
      }
    }
  }
}

uint16_t angle_to_duty_cycle_convert(uint8_t angle)
{
  uint16_t data_angle;

  data_angle = uint16_t((1+ (angle / 180.0) ) / 20 * 4096);

  return data_angle;
}


void envoyer_les_donnees(uint8_t vecteur[TAILLE])
{
  uint16_t dataFull;
  uint8_t error;

  uint8_t data_L;
  uint8_t data_H;

  dataFull = angle_to_duty_cycle_convert(vecteur[VECTEUR_ANGLE]);

  uint16_t process_data;

  process_data = dataFull >> 8 & 0x000F; // bit de poid fort
  data_H = uint8_t(process_data);
  process_data = dataFull & 0x00FF; // bit de poid faible
  data_L = uint8_t(process_data);

  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(vecteur[VECTEUR_MOTEUR]);
  Wire.write(data_L);
  Wire.write(data_H);
  error = Wire.endTransmission();
}