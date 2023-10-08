#include <MPU6050_tockn.h>  //scl =A5 / sda =A4 /vcc =5v /gnd=gnd
#include <Servo.h>
// #include <Wire.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
// Purple orange Arduino
// Blue red 5V
// Green brown Ground

int servopin1 = 9;  // Servo pin
int servopin2 = 10;
int servopin3 = 11;
int servopin4 = 12;

Servo servo1;  // Servo object
Servo servo2;
Servo servo3;
Servo servo4;

int RXPin = 6;
int TXPin = 7;

int GPSBaud = 9600;

int pos = 0;  //position


TinyGPSPlus gps;
MPU6050 mpu6050(Wire);

long timer = 0;
SoftwareSerial gpsSerial(RXPin, TXPin);


void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  servo1.attach(servopin1);  //attach object to pin
  servo2.attach(servopin2);
  servo3.attach(servopin3);
  servo4.attach(servopin4);
  Serial.println("Setup");
  Serial.println("init run");
  gpsSerial.begin(GPSBaud);
}

void loop() {
  if (millis() - timer > 1000) {
    Serial.print("angleX : ");  // print
    Serial.print(mpu6050.getAngleX());
    mpu6050.update();
    Serial.print("  angleY : ");
    Serial.print(mpu6050.getAngleY());
    Serial.print("  angleZ : ");
    Serial.println(mpu6050.getAngleZ());
    timer = millis();
  }
  //x-axis / roll
  if (abs(mpu6050.getAngleX()) < 1 && mpu6050.getAngleX() != 0) {
    servo2.write(90);
  }
  servo2.write(90 - mpu6050.getAngleY());  //unstable angle

  if (mpu6050.getAngleX() == 0) {
    servo1.write(90);  //set to 90 degrees
  }
  servo1.write(90 + mpu6050.getAngleY());  //unstable angle

  //y-axis / pitch

  if (mpu6050.getAngleY() == 0) {
    servo3.write(90);  //set to 90 degrees
  }

  if (mpu6050.getAngleZ() == 0) {
    servo4.write(90);  //set to 90 degrees
  }
  // Serial.print("90 - mpu6050.getAngleZ(): ");
  // Serial.println(90 - mpu6050.getAngleZ());
  // servo4.write(90 - mpu6050.getAngleZ());  //unstable angle

  while (gpsSerial.available() > 0)

    if (gps.encode(gpsSerial.read()))
      // displayInfo();

  if (millis() > 8000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}

