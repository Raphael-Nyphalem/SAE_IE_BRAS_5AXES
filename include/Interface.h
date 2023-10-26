#include "PCA9685.h"
#include "sequences.h"

/**
 * @brief 
 * 
 * @param moteur [E]
 * @param saisie_finis [E/S]
 * @return true [S] retourne VRAIS si on souhaite quitte le mode de fonctionnement
 * @return false [S] retourne FAUX si on souhaite reste dans le mode de fonctionnement actuelle
 */
bool saisie_commande_utilisateur(pca9685 &moteur, bool &saisie_finis);

/**
 * @brief Permet la selection du mode de fonctionnement voulue
 *
 * @param mode [E/S] paramètre du mode actuel de fonctionnement defaut -1 (pas de mode selectionner)
 * @return true [S] retourne Vrais si un mode est un mode pris en compte dans le programme
 * @return false [S] retourne FAUX si un mode est un mode qui n'est pas pris en compte dans le programme
 */
bool selection_de_mode(int8_t &mode);

/**
 * @brief Permet l'exécution d'une séquence écrite dans 'sequences.h' sur le bras 5 axe, 
 *  cette fonction utilise la fonction envoi_n_donnee() de PCA9685
 * 
 * @param sequence [E] séquence que l'on souhaite exécute, lorsque la séquence est à -1 c'est qu'aucune n'a été sélectionnée
 * @return true [S] retourne VRAIS si on souhaite quitte le mode de fonctionnement
 * @return false [S] retourne FAUX si on souhaite reste dans le mode de fonctionnement actuelle
 */
bool execution_sequence(int8_t sequence);

/**
 * @brief 
 * 
 * @param sequence [E/S]
 * @return true [S] retourne VRAIS si on souhaite quitte le mode de fonctionnement
 * @return false [S] retourne FAUX si on souhaite reste dans le mode de fonctionnement actuelle
 */
bool selection_de_sequence(int8_t &sequence);