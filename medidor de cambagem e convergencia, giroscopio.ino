 //Carrega a biblioteca Wire
#include<Wire.h>
//Carrega a biblioteca do LCD
#include <LiquidCrystal.h>

// Inicializa o LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
 
int minVal=265;
int maxVal=402;
 
double x;
double y;
double z;
double valorz;
 
void setup(){
Wire.begin();
Wire.beginTransmission(MPU_addr);
Wire.write(0x6B);
Wire.write(0);
Wire.endTransmission(true);
Serial.begin(9600);
lcd.begin(16, 2);
lcd.clear();
}
void loop(){
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true);
AcX=Wire.read()<<8|Wire.read();
AcY=Wire.read()<<8|Wire.read();
AcZ=Wire.read()<<8|Wire.read();
int xAng = map(AcX,minVal,maxVal,-90,90);
int yAng = map(AcY,minVal,maxVal,-90,90);
int zAng = map(AcZ,minVal,maxVal,-90,90);
 
x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
valorz = ((PI * 270,51 * z)/180);

lcd.setCursor(0,0);
  lcd.print("cambagem");
  lcd.setCursor(0,2);
  lcd.print("convergência");
 
Serial.print("AngleX= ");
Serial.println(x);
 
Serial.print("AngleY= ");
Serial.println(y);
lcd.setCursor(10,0);
lcd.print("Camb=");
lcd.print(y);

Serial.print("AngleZ= ");
Serial.println(valorz);
Serial.println("-----------------------------------------");
lcd.setCursor(13,2);
lcd.print("conv=");
lcd.print(valorz);
delay(4000);
}
