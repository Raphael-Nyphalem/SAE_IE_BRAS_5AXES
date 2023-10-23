#include <Arduino.h>
#include "Interface.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(UINT16_MAX);

  initialisation();
}

void loop()
{
  /*
  bool test;
  static bool saisi_test = false;
  static pca9685 moteur;

  test = saisie_commande_utilisateur(moteur,saisi_test);
  if (saisi_test == true)
  {
    envoyer_les_donnees(moteur);
    saisi_test = false;
  }*/
  static int8_t mode =-1;
  selection_de_mode(mode);

  if (mode == 1)
  {
    bool quitte_mode_1;
    static bool saisie_finit = false;
    static pca9685 moteur_1;

    quitte_mode_1 = saisie_commande_utilisateur(moteur_1,saisie_finit);
    if (quitte_mode_1)
    {
      mode = -1;
    }
    else
    {
      if (saisie_finit)
      {
        envoyer_les_donnees(moteur_1);
        saisie_finit = false;
      }
    }
  }
  
  if(mode ==2)
  {
    bool quitte_mode_2;
    static pca9685 moteur_2;

    if (quitte_mode_2)
    {
      mode =-1;
    }
    else
    {
      envoyer_les_donnees(moteur_2);
    }
 
  }
}
