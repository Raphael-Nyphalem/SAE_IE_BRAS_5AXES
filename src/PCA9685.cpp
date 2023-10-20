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

  if (error >=1 )
  {
    Serial.print("erreur d'envoie de donnée dans le fonction 'init_executeur' \nErreur : ");
    Serial.println(error);
  }
  
}


bool saisie_commande_utilisateur(uint8_t vecteur[TAILLE], bool &saisie_finis)
{
  uint8_t angle_choisi;
  char moteur_choisi;
  static bool flag_moteur = true;
  static bool flag_moteur_print = true;
  static bool flag_angle = false;
  static bool flag_angle_print = false;

  bool quitterMode1 = false;

  if (flag_moteur_print == true)
  {
    Serial.println(' ');
    Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
    Serial.println(' ');

    flag_moteur_print = false;
  }
  if (flag_moteur == true)
  { 
    if (Serial.available())
    {
      moteur_choisi = Serial.read();
      //Serial.println(moteur_choisi);
      switch (moteur_choisi)
      {
      case 'a':
      case 'A':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_A;
        
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'b':
      case 'B':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_B;
        
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        flag_angle_print = true;
        break;
      case 'c':
      case 'C':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_C;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'd':
      case 'D':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_D;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'e':
      case 'E':
        vecteur[VECTEUR_MOTEUR] = MOTEUR_E;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'h':
      case 'H':
        Serial.println(' ');
        Serial.println("motor A -> rotation of the base of the arm on the z axis");
        Serial.println("motor B -> rotation of the arm attach to the base on the x axis");
        Serial.println("motor C -> rotation of the middle arm on the x axis");
        Serial.println("motor A -> rotation of the part of the arm attach to the clamp the x axis");
        Serial.println("motor A -> opens and closes the clamp");
        Serial.println(' ');
        Serial.println("press Q for return to mode selection");
        
        flag_moteur_print = true;
        break;
      case 'q':
      case 'Q':
        Serial.println(' ');
        Serial.println("returning to mode selection . . .");
        Serial.println(' ');
        quitterMode1 = true;
        flag_moteur = false;
        break;
      default:
        Serial.println(' ');
        Serial.println("well,... if you can not read I can't do much for you ಠ_ಠ");
        Serial.println(' ');

        flag_moteur_print = true;
        break;
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

    if (error >=1 )
  {
    Serial.print("erreur d'envoie de donnée dans le fonction 'envoyer_les_donnees' \nErreur : ");
    Serial.println(error);
  }
}

bool selection_de_mode(int8_t &mode)
{
  static bool flag_choix_print = true;
  static bool flag_choix_read = false;
  bool retourne = false;

  if (mode !=1 or mode !=2)
  {
    mode = -1;
    flag_choix_print=true;
  }
  

  if (flag_choix_print)
  {
    Serial.println("\nVeuiller effectuer un choix de mode de fonctionnment ");
    Serial.println("tapée 1 pour Mode 1: ");
    Serial.println("Tapée 2 pour Mode 2: ");
    flag_choix_print = false;
    flag_choix_read = true;
  }

  if (Serial.available() and flag_choix_read)
  {
    char lue = Serial.read();
    switch (lue)
    {
    case '1':
      mode = 1;
      flag_choix_read = false;
      break;
    
    case '2':
      mode = 2;
      flag_choix_read = false;
      break;

    default:
      flag_choix_print = true;
      break;
    }
  }

  if (mode >=1)
  {
    retourne =true;
  }

  return retourne;
}