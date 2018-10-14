//Programa: Leitura e gravacao de cartoes RFID
//Autor: FILIPEFLOP

/*Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
//Pinos Reset e SS módulo MFRC522
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
//#define pino_botao_le A2
//#define pino_botao_gr A3
 
MFRC522::MIFARE_Key key;
 
void mensagem_inicial(){
  Serial.println("Aproxime o seu cartao do leitor...");
}
 
void modo_gravacao(){
  mensagem_inicial();
  //Aguarda cartao
  while ( ! mfrc522.PICC_IsNewCardPresent()){
    delay(100);
  }
  if ( ! mfrc522.PICC_ReadCardSerial())    return;
 
  //Mostra UID na serial
  Serial.print(F("UID do Cartao: "));    //Dump UID
  for (byte i = 0; i < mfrc522.uid.size; i++){
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  //Mostra o tipo do cartao
  Serial.println();
  Serial.print(F("Tipo do PICC: "));
  byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.println(mfrc522.PICC_GetTypeName((MFRC522::PICC_Type)piccType));
 
  byte buffer[16];
  byte block;
  byte status, len;
 
  Serial.setTimeout(20000L) ;
  Serial.println(F("Gravando ID Funcionário"));
//  String msg = "                                                   ";
  String msg = " 2803";
  msg.getBytes(buffer,6);
 
  block = 4;
  //Serial.println(F("Autenticacao usando chave A..."));
  status=mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK){
    Serial.print(F("PCD_Authenticate() failed3: "));
    Serial.println(mfrc522.GetStatusCodeName((MFRC522::StatusCode)status));
    return;
  }
 
  //Grava no bloco 4
  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK){
    Serial.print(F("MIFARE_Write() failed3: "));
    Serial.println(mfrc522.GetStatusCodeName((MFRC522::StatusCode)status));
    return;
  }
 
  block = 5;
  //Serial.println(F("Authenticating using key A..."));
  status=mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,
                                    block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK){
    Serial.print(F("PCD_Authenticate() failed4: "));
    Serial.println(mfrc522.GetStatusCodeName((MFRC522::StatusCode)status));
    return;
  }
 
  //Grava no bloco 5
  status = mfrc522.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK){
    Serial.print(F("MIFARE_Write() failed4: "));
    Serial.println(mfrc522.GetStatusCodeName((MFRC522::StatusCode)status));
    //return;
  }
  else{
    Serial.println(F("Dados gravados com sucesso!"));
    Serial.print("Gravacao OK!");
  }

  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
  delay(5000);
  Serial.println();
  Serial.println();
}

void setup(){
//  pinMode(pino_botao_le, INPUT);
//  pinMode(pino_botao_gr, INPUT);
  Serial.begin(9600);   //Inicia a serial
  SPI.begin();      //Inicia  SPI bus
  mfrc522.PCD_Init();   //Inicia MFRC522
 
  //Prepara chave - padrao de fabrica = FFFFFFFFFFFFh
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
}
 
void loop(){
  Serial.println("Gravação");
  modo_gravacao();
}
