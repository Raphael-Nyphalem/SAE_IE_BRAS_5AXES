#include <Arduino.h>
#include "PCA9685.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(UINT16_MAX);

  initialisation();
}

void loop()
{
  bool test;
  static bool saisi_test = false;
  static uint8_t vecteur_test[2] ;

  test = saisie_commande_utilisateur(vecteur_test,saisi_test);
  if (saisi_test == true)
  {
    envoyer_les_donnees(vecteur_test);
    saisi_test = false;
  }
  /*
  static int8_t mode =-1;
  selection_de_mode(mode);

  if (mode == 1)
  {
    bool quitte_mode_1;
    bool saisie_finit = false;
    static uint8_t vecteur_1[TAILLE_VECTEUR];

    quitte_mode_1 = saisie_commande_utilisateur(vecteur_1,saisie_finit);
    if (quitte_mode_1)
    {
      mode = -1;
    }
    else
    {
      if (saisie_finit)
      {
        envoyer_les_donnees(vecteur_1);
        saisie_finit = false;
      }
    }
  }
  
  if(mode ==2)
  {
    bool quitte_mode_2;
    static uint8_t vecteur_2[TAILLE_VECTEUR];

    if (quitte_mode_2)
    {
      mode =-1;
    }
    else
    {
      envoyer_les_donnees(vecteur_2);
    }
 
  }
  */
}
