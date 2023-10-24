#include "Interface.h"

bool saisie_commande_utilisateur(pca9685 &moteur, bool &saisie_finis)
{
  int8_t angle_choisi;
  char moteur_choisi;
  static bool flag_moteur = true;
  static bool flag_moteur_print = true;
  static bool flag_angle = false;
  static bool flag_angle_print = false;

  bool quitterMode1 = false;

  if (flag_moteur_print == true)
  {
    Serial.println("\nchoose a motor | A | B | C | D | E |, tap h for help");
    Serial.println("press Q for return to mode selection");

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
        moteur.adresse = MOTEUR_A;
        
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'b':
      case 'B':
        moteur.adresse = MOTEUR_B;
        
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'c':
      case 'C':
        moteur.adresse = MOTEUR_C;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'd':
      case 'D':
        moteur.adresse = MOTEUR_D;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'e':
      case 'E':
        moteur.adresse = MOTEUR_E;
        
        flag_moteur = false;
        flag_angle = true;
        flag_angle_print = true;
        break;
      case 'h':
      case 'H':
        Serial.println("\nmotor A -> rotation of the base of the arm on the z axis");
        Serial.println("motor B -> rotation of the arm attach to the base on the x axis");
        Serial.println("motor C -> rotation of the middle arm on the x axis");
        Serial.println("motor D -> rotation of the part of the arm attach to the clamp the x axis");
        Serial.println("motor E -> opens and closes the clamp");
        Serial.println("\npress Q for return to mode selection");
 
        flag_moteur_print = true;
        break;
      case 'q':
      case 'Q':
        Serial.println("\nreturning to mode selection . . .\n");

        quitterMode1 = true;
        flag_moteur = false;
        break;
      default:
        Serial.println("\nwell,... if you can not read I can't do much for you ಠ_ಠ\n");

        flag_moteur_print = true;
        break;
      }
    }
  }
    if (flag_angle_print == true)
  {
  Serial.println("\nchoose an angle between -90 and 90\n");


  flag_angle_print = false;
  }
  if ((flag_angle == true) && (quitterMode1 == false))
  {
    if (Serial.available())
    {
      angle_choisi = Serial.readStringUntil('\n').toInt();
      if ((angle_choisi >= -90) && (angle_choisi<=90))
      {
        moteur.angle=angle_choisi;
        Serial.println("\nchoice saved\n");


        flag_angle = false;
        saisie_finis = true;
      }
      else
      {
        Serial.println("\n[ERROR] - out of bounds\n");

        flag_angle_print = true;
      }
    }
    if (saisie_finis == true)
    {
      flag_moteur = true;
      flag_moteur_print = true;
      flag_angle = false;
      flag_angle_print = false;
    }
    
  }
  return quitterMode1;
}

bool selection_de_mode(int8_t &mode)
{
  static bool flag_choix_print = true;
  static bool flag_choix_read = false;
  bool retourne = false;

  if ((mode == 1) || (mode == 2))
  {

  }
  else
  {
    if (flag_choix_read == false)
    {
      mode = -1;
      flag_choix_print=true;
    }
  }

  if (flag_choix_print)
  {
    Serial.println("\nVeuiller effectuer un choix de mode de fonctionnment ");
    Serial.println("tapée 1 pour Mode 1: ");
    Serial.println("Tapée 2 pour Mode 2: \n");
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

void mode2_hardcoded_sequence()
{
  pca9685 moteurA;
  pca9685 moteurB;
  pca9685 moteurC;
  pca9685 moteurD;
  pca9685 moteurE;

  moteurA.adresse = MOTEUR_A;
  moteurB.adresse = MOTEUR_B;
  moteurC.adresse = MOTEUR_C;
  moteurD.adresse = MOTEUR_D;
  moteurE.adresse = MOTEUR_E;

}