#include <Arduino.h>
#include <Wire.h>

const uint8_t ADDRESS_PSA = 0x7F;

const uint8_t R_MODE_1 = 0x00;
const uint8_t R_PRE_SCALE = 0xFE;
const uint8_t R_LED0_ON_L = 0x06;

const uint8_t DEFAULT_MODE1 = 0x21;
const uint8_t PRESCALER = 25000000 / 4096 / 50;

const uint8_t STORAGE_ON_OFF = 4;
const uint8_t ADRESS_MOTEUR = 5;

const uint8_t MOTEUR_A = 0;
const uint8_t MOTEUR_B = 1;
const uint8_t MOTEUR_C = 2;
const uint8_t MOTEUR_D = 3;
const uint8_t MOTEUR_E = 4;

const uint8_t MOTEUR_A_ADRESS_ON_L_0FF = 0x06;
const uint8_t MOTEUR_A_ADRESS_ON_L_F00 = 0x07;
const uint8_t MOTEUR_A_ADRESS_ON_H_0FF = 0x08;
const uint8_t MOTEUR_A_ADRESS_ON_H_F00 = 0x09;

const uint8_t MOTEUR_B_ADRESS_ON_L_0FF = 0x0A;
const uint8_t MOTEUR_B_ADRESS_ON_L_F00 = 0x0B;
const uint8_t MOTEUR_B_ADRESS_ON_H_0FF = 0x0C;
const uint8_t MOTEUR_B_ADRESS_ON_H_F00 = 0x0D;

const uint8_t MOTEUR_C_ADRESS_ON_L_0FF = 0x0E;
const uint8_t MOTEUR_C_ADRESS_ON_L_F00 = 0x0F;
const uint8_t MOTEUR_C_ADRESS_ON_H_0FF = 0x10;
const uint8_t MOTEUR_C_ADRESS_ON_H_F00 = 0x11;

const uint8_t MOTEUR_D_ADRESS_ON_L_0FF = 0x12;
const uint8_t MOTEUR_D_ADRESS_ON_L_F00 = 0x13;
const uint8_t MOTEUR_D_ADRESS_ON_H_0FF = 0x14;
const uint8_t MOTEUR_D_ADRESS_ON_H_F00 = 0x14;

const uint8_t MOTEUR_E_ADRESS_ON_L_0FF = 0x16;
const uint8_t MOTEUR_E_ADRESS_ON_L_F00 = 0x17;
const uint8_t MOTEUR_E_ADRESS_ON_H_0FF = 0x18;
const uint8_t MOTEUR_E_ADRESS_ON_H_F00 = 0x19;




/**
 * @brief 
 * 
 */
void initialisation();

/**
 * @brief 
 * 
 * @param registre 
 * @param data 
 */
void ecrire_sur_un_registre(uint8_t registre, uint8_t data);

/***/
void ecrire_sur_4_registre(uint8_t registre_ledn_ON_L, uint8_t data[4]);

void setup() {
  Wire.begin();
  initialisation();

  uint8_t data[4];
  data[0] =0X00;
  data[1] =0X00;
  data[2] =0XFF;
  data[3] =0X07;
  ecrire_sur_4_registre(R_LED0_ON_L,data);
}

void loop() {
  
}

void initialisation(){
  ecrire_sur_un_registre(R_MODE_1,DEFAULT_MODE1 | 0x10);
  ecrire_sur_un_registre(R_PRE_SCALE,PRESCALER);
  ecrire_sur_un_registre(R_MODE_1,DEFAULT_MODE1);
}

void ecrire_sur_un_registre(uint8_t registre, uint8_t data){
  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre);
  Wire.write(data);
  uint8_t error =  Wire.endTransmission();
}

void ecrire_sur_4_registre(uint8_t registre_ledn_ON_L,uint8_t data[4])
{
  uint8_t data_ON_L = data[0];
  uint8_t data_ON_H = data[1] & 0x0F;
  uint8_t data_OFF_L= data[2];
  uint8_t data_OFF_H= data[3]& 0x0F;

  Wire.beginTransmission(ADDRESS_PSA);
  Wire.write(registre_ledn_ON_L);
  Wire.write(data_ON_L);
  Wire.write(data_ON_H);
  Wire.write(data_OFF_L);
  Wire.write(data_OFF_H);
  uint8_t error =  Wire.endTransmission();

}

void ecrire_sur_2_registre(uint8_t registre_ledn_ON_L,);


bool preparation_des_donnees(uint8_t num_moteur, uint16_t data_ON, uint16_t data_OFF, uint8_t data_storage[STORAGE_ON_OFF][ADRESS_MOTEUR])
{
  uint8_t process_data;
  bool process_finis = false;

  process_data = uint8_t((data_OFF >> 12) & 0x000F); //bit de poid fort
  data_storage[1][num_moteur] = process_data;
  process_data = uint8_t(data_OFF & 0x00FF); //bit de poid faible
  data_storage[0][num_moteur] = process_data;

  process_data = uint8_t((data_OFF >> 12) & 0x000F);
  data_storage[3][num_moteur] = process_data;
  process_data = uint8_t(data_ON & 0x00FF);
  data_storage[2][num_moteur] = process_data;

  process_finis = true;

  return process_finis;
}

void utilisateur_commande_moteur(uint16_t &data_angle, uint8_t &moteur_X)
{
  char choice;
  int16_t angle_choisi;
  bool stupid_proof_flag = true;

  while (stupid_proof_flag == false)
  {
    Serial.println("choose a motor | A | B | C | D | E |, tap h for help ");
    choice = Serial.available();
    Serial.println(choice);
    switch (choice)
    {
    case 'A':
      moteur_X = MOTEUR_A;
      stupid_proof_flag = false;
      break;
    case 'B':
      moteur_X = MOTEUR_B;
      stupid_proof_flag = false;
      break;
    case 'C':
      moteur_X = MOTEUR_C;
      stupid_proof_flag = false;
      break;
    case 'D':
      moteur_X = MOTEUR_D;
      stupid_proof_flag = false;
      break;
    case 'E':
      moteur_X = MOTEUR_E;
      stupid_proof_flag = false;
      break;
    case 'h':
      Serial.println("motor A -> rotation of the base of the arm on the z axis");
      Serial.println("motor B -> rotation of the arm attach to the base on the x axis");
      Serial.println("motor C -> rotation of the middle arm on the x axis");
      Serial.println("motor A -> rotation of the part of the arm attach to the clamp the x axis");
      Serial.println("motor A -> opens and closes the clamp");
      break;
    default:
      Serial.println("well,... if you can not read I can't do much for you à² _à² ");
      break;
    }
  }

  stupid_proof_flag = true;

  while (stupid_proof_flag == false)
  {
    Serial.println("choose an between -90 and 90");
    angle_choisi = Serial.available();
    if ((angle_choisi >= -90) && (angle_choisi <= 90))
    {
      data_angle = uint16_t((1.5 + (angle_choisi / 180) * 4096) / 20);
      Serial.println("choice saved");
      stupid_proof_flag = false;
    }
    else
    {
      Serial.println("[ERROR] - out of bounds");
    }
  }
}

