#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PSA = 0x7F;

const uint8_t R_MODE_1 = 0x00;
const uint8_t R_PRE_SCALE = 0xFE;

const uint8_t DEFAULT_MODE1 = 0x21;
const uint8_t PRESCALER = 25000000 / 4096 / 50;


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


const uint8_t TAILLE =2;
const uint8_t VECTEUR_MOTEUR =0;
const uint8_t VECTEUR_ANGLE =1;


uint8_t vecteur_moteur_data[TAILLE];
uint8_t process_data_storage[TAILLE];

/**
 * @brief permet l'initialisation du précalère a 50 hz
 *  qui est l'autre de fréquance de fonctionnement des moteurs
 *
 */
void initialisation();

/**
 * @brief fonction qui permet d'envoyer une donner a un registre 
 *
 * @param registre [E] registre que l'on soueite axéder pour ecrire une donnée
 * @param data [E] donnée que l'on soueite écrire 
 */
void init_executeur(uint8_t registre, uint8_t data);

/**
 * @brief 
 * 
 * @param vecteur [E/S]
 */
void saisie_commande_utilisateur(uint8_t vecteur[TAILLE]);

/**
 * @brief 
 * 
 * @param angle [E]
 * @return uint16_t [S]
 */
uint16_t angle_to_duty_cycle_convert(uint8_t angle);

/**
 * @brief 
 * 
 * @param vecteur [E]
 */
void envoyer_les_donnees(uint8_t vecteur[TAILLE]);

void setup()
{
  Wire.begin();
  initialisation();
}

void loop()
{
  uint8_t vecteur[TAILLE];
  saisie_commande_utilisateur(vecteur);
  envoyer_les_donnees(vecteur);
}

void initialisation()
{
  init_executeur(R_MODE_1, DEFAULT_MODE1 | 0x10);
  init_executeur(R_PRE_SCALE, PRESCALER);
  init_executeur(R_MODE_1, DEFAULT_MODE1);  
}

void init_executeur(uint8_t registre, uint8_t data)   
{
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error = Wire.endTransmission();
}

void saisie_commande_utilisateur(uint8_t vecteur[TAILLE])
{
  int8_t angle_choisi;
  char choice;
  bool stupid_proof_flag = true;

  while (stupid_proof_flag == true)
  {
    Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
    choice = Serial.available();
    Serial.println(choice);
    switch (choice)
    {
    case 'A':
      vecteur[VECTEUR_MOTEUR] = MOTEUR_A;
      stupid_proof_flag = false;
      break;
    case 'B':
      vecteur[VECTEUR_MOTEUR] = MOTEUR_B;
      stupid_proof_flag = false;
      break;
    case 'C':
      vecteur[VECTEUR_MOTEUR] = MOTEUR_C;
      stupid_proof_flag = false;
      break;
    case 'D':
      vecteur[VECTEUR_MOTEUR] = MOTEUR_D;
      stupid_proof_flag = false;
      break;
    case 'E':
      vecteur[VECTEUR_MOTEUR] = MOTEUR_E;
      stupid_proof_flag = false;
      break;
    case ('h','H'):
      Serial.println("motor A -> rotation of the base of the arm on the z axis");
      Serial.println("motor B -> rotation of the arm attach to the base on the x axis");
      Serial.println("motor C -> rotation of the middle arm on the x axis");
      Serial.println("motor A -> rotation of the part of the arm attach to the clamp the x axis");
      Serial.println("motor A -> opens and closes the clamp");
      break;
    default:
      Serial.println("well,... if you can not read I can't do much for you ಠ_ಠ");
      break;
    }
  }
    stupid_proof_flag = true;

  while (stupid_proof_flag == true)
  {
    Serial.println("choose an angle between -90 and 90");
    angle_choisi = Serial.available();
    if ((angle_choisi >= -90) && (angle_choisi <= 90))
    {
      vecteur[VECTEUR_ANGLE]=angle_choisi;
      Serial.println("choice saved");

      stupid_proof_flag = false;
    }
    else
    {
      Serial.println("[ERROR] - out of bounds");
    }
  }
}

uint16_t angle_to_duty_cycle_convert(uint8_t angle)
{
  uint16_t data_angle;

  data_angle = uint16_t((1.5 + (angle / 180.0) ) / 20 * 4096);

  return data_angle;
}


void envoyer_les_donnees(uint8_t vecteur[TAILLE])
{
  uint16_t dataFull;
  uint8_t error;

  uint8_t data_L;
  uint8_t data_H;

  dataFull = angle_to_duty_cycle_convert(vecteur[VECTEUR_ANGLE]);

  uint16_t process_data;

  process_data = dataFull >> 12 & 0x000F; // bit de poid fort
  data_H = uint8_t(process_data);
  process_data = dataFull & 0x00FF; // bit de poid faible
  data_L = uint8_t(process_data);

  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(vecteur[VECTEUR_MOTEUR]);
  Wire.write(data_L);
  Wire.write(data_H);
  error = Wire.endTransmission();
}