#include "Interface.h"

bool saisie_commande_utilisateur(uint8_t vecteur[TAILLE_VECTEUR], bool &saisie_finis)
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
    if (flag_angle_print == true)
  {
  Serial.println(' ');
  Serial.println("choose an angle between 0 and 180");
  Serial.println(' ');

  flag_angle_print = false;
  }
  if ((flag_angle == true) && (quitterMode1 == false))
  {
    if (Serial.available())
    {
      angle_choisi = Serial.readStringUntil('\n').toInt();
      if (angle_choisi<=180)
      {
        vecteur[VECTEUR_ANGLE]=angle_choisi;
        Serial.println(' ');
        Serial.println("choice saved");

        flag_angle = false;
        saisie_finis = true;
      }
      else
      {
        Serial.println(' ');
        Serial.println("[ERROR] - out of bounds");

        flag_angle_print = true;
      }
    }
    if (saisie_finis == true)
    {
      bool flag_moteur = true;
      bool flag_moteur_print = true;
      bool flag_angle = false;
      bool flag_angle_print = false;
    }
    
  }
  return quitterMode1;
}

bool selection_de_mode(int8_t &mode)
{
  static bool flag_choix_print = true;
  static bool flag_choix_read = false;
  bool retourne = false;

  if (mode == 1 or mode == 2)
  {}
  else
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