#include "Wire.h"  // Arduino Wire library
#include "I2Cdev.h"  //Installer ces 2 librairies
#include "MPU6050.h"
#include "math.h"
 
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
 
int16_t ax, ay, az;  //mesures brutes
int16_t gx, gy, gz;
float angle=0;

// motor initialization
int In1 = 6;
int In2 = 7;
int In3 = 9;
int In4 = 8;
int ENA = 10;
int ENB = 5;
 
void setup() {
  Wire.begin();  //I2C bus
  //Serial.begin(9600); 
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB (LEONARDO)
  }
 
  // initialize device
  accelgyro.initialize();

  // motor 
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  digitalWrite(In1,HIGH);
  digitalWrite(In2, LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4, LOW);
}

void negativeState() 
{ 
digitalWrite(In1 , HIGH);
digitalWrite(In2, LOW);
digitalWrite(In3, HIGH);
digitalWrite(In4,LOW);
analogWrite( ENA, 100);
analogWrite( ENB, 100);
}

void positiveState()
{
digitalWrite(In1 , LOW);
digitalWrite(In2, HIGH);
digitalWrite(In3, LOW);
digitalWrite(In4,HIGH);
analogWrite( ENA, 100);
analogWrite( ENB, 100);
}

void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  angle= atan2((double)ax,(double)az )*180/PI; // 180/PI permet d'avoir la valeur en °
  Serial.println(angle);
  delay(10);

  // equilibrage 
  if ( angle <= -5 )
  {
  negativeState();
  }
  else if ( angle >= 5 )
  {
  positiveState();
  }
  
}
