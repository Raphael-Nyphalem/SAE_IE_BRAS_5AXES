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
  static int8_t mode =-1;
  selection_de_mode(mode);

  if (mode == 1)
  {
    bool quitte_mode_1;
    uint8_t vecteur[TAILLE];

    quitte_mode_1 = saisie_commande_utilisateur(vecteur);
    if (quitte_mode_1)
    {
      mode = -1;
    }
    else
    {
      envoyer_les_donnees(vecteur);
    }
  }
  
  if(mode ==2)
  {
    bool quitte_mode_2;
    uint8_t vecteur[TAILLE];

    if (quitte_mode_2)
    {
      mode =-1;
    }
    else
    {
      envoyer_les_donnees(vecteur);
    }
 
  }
}
