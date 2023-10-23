#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PCA = 0x7F;

const uint8_t R_MODE_1 = 0x00;
const uint8_t R_PRE_SCALE = 0xFE;

const uint8_t DEFAULT_MODE1 = 0x21;
const uint8_t PRESCALER = 25000000 / 4096 / 50 - 1;
const uint8_t SLEEP = 0x10;
const uint8_t EXT_CLK = 1<<6;


const uint8_t LED0_OFF_L = 0x08;
const uint8_t LED1_OFF_L = 0x0C;
const uint8_t LED2_OFF_L = 0x10;
const uint8_t LED3_OFF_L = 0x14;
const uint8_t LED4_OFF_L = 0x18;
const uint8_t LED5_OFF_L = 0x1C;
const uint8_t LED6_OFF_L = 0x20;
const uint8_t LED7_OFF_L = 0x24;

const uint8_t LED8_OFF_L = 0x28;
const uint8_t LED9_OFF_L = 0x2C;
const uint8_t LED10_OFF_L = 0x30;
const uint8_t LED11_OFF_L = 0x34;
const uint8_t LED12_OFF_L = 0x38;
const uint8_t LED13_OFF_L = 0x3C;
const uint8_t LED14_OFF_L = 0x40;
const uint8_t LED15_OFF_L = 0x44;

const uint8_t MOTEUR_A = LED0_OFF_L;
const uint8_t MOTEUR_B = LED1_OFF_L;
const uint8_t MOTEUR_C = LED2_OFF_L;
const uint8_t MOTEUR_D = LED3_OFF_L;
const uint8_t MOTEUR_E = LED4_OFF_L;



struct pca9685
{
  uint8_t adresse;
  int8_t angle;
};

/**
 * @brief permet l'initialisation du prescalere pour update rate a 50 hz
 *  qui est notre de fréquance de fonctionnement des moteurs
 *
 */
void initialisation();

/** 
* @brief fonction qui permet d'envoyer une donner à un registre  
* 
* @param registre [E] registre que l'on souhaite axée pour écrire une donnée 
* @param data [E] donnée que l'on souhaite écrire  
*/ 
void init_executeur(uint8_t registre, uint8_t data);


/**
 * @brief 
 * 
 * @param vecteur 
 */
void mode1_envoie_de_donnees(pca9685 moteur);


