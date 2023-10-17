#include <Arduino.h>
#include "PCA9685.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  initialisation();
}

void loop()
{
  uint8_t vecteur[TAILLE];
  saisie_commande_utilisateur(vecteur);
  envoyer_les_donnees(vecteur);
}
