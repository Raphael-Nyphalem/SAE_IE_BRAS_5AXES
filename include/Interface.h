#include "PCA9685.h"

/**
 * @brief 
 * 
 * @param vecteur 
 * @param saisie_finis 
 * @return true 
 * @return false 
 */
bool saisie_commande_utilisateur(uint8_t vecteur[TAILLE_VECTEUR],bool &saisie_finis);

/**
 * @brief Permet la selection du mode de fonctionnement voulue
 * 
 * @param mode [E/S] paramètre du mode actuel de fonctionnement defaut -1 (pas de mode selectionner)
 * @return true [S] retourne Vrais si un mode est un mode pris en compte dans le programme
 * @return false [S] retourne Vrais si un mode est un mode  qui n'est pas pris en compte dans le programme
 */
bool selection_de_mode(int8_t &mode);