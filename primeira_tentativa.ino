//Programa : Teste MPU6050 e LCD 20x4
//Alteracoes e adaptacoes : FILIPEFLOP
//
//Baseado no programa original de JohnChi
 
//Carrega a biblioteca Wire
#include<Wire.h>
//Carrega a biblioteca do LCD
#include <LiquidCrystal.h>
 
// Inicializa o LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
double GyX,GyY,GyZ;
void setup()
{
  Serial.begin(9600);
  //Inicializa o LCD
  lcd.begin(16, 2);
  lcd.clear();
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
     
  //Informacoes iniciais do display
  lcd.setCursor(0,0);
  lcd.print("cambagem");
  lcd.setCursor(0,2);
  lcd.print("convergência");
}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
   
  //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | GyX = "); Serial.print(GyX);
  lcd.setCursor(10,0);
  lcd.print("Camb=");
  lcd.print(GyX);
   
  //Envia valor Y do giroscopio para a serial e o LCD  
  Serial.print(" | GyY = "); Serial.print(GyY);
  lcd.setCursor(10,2);
  lcd.print("Y=");
  lcd.print(GyY);
   
  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  lcd.setCursor(13,3);
  lcd.print("Conv");
  lcd.print(GyZ);
   
  //Aguarda 300 ms e reinicia o processo
  delay(3000);
}
