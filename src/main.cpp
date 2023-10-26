#include <Arduino.h>
#include "Interface.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(UINT16_MAX);

  initialisation();

  //TEST N canaux
  uint8_t nb_canaux = 2;
  int8_t tab[nb_canaux] = {-90,90};
  envoi_n_donnee(tab, nb_canaux);
  
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
    mode1_envoie_de_donnees(moteur);
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
        mode1_envoie_de_donnees(moteur_1);
        saisie_finit = false;
      }
    }
  }
  
  if(mode ==2)
  {
    bool quitte_mode_2;
    static int8_t sequance = -1;
    quitte_mode_2 = selection_de_sequence(sequance);

    if (sequance > 0)
    {
      quitte_mode_2 = execution_sequence( sequance );
    }

    if (quitte_mode_2)
    {
      sequance = -1;
      mode =-1;
    }
    
  }
}
