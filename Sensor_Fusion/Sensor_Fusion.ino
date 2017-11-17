#include <Wire.h>
#include <sensor_fusion.h>
#include <printf.h>

#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define CONFIG 0x1A
#define INT_STATUS 0x3A
#define ACCEL_XOUT_H 0x3B
//#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
//#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
//#define ACCEL_ZOUT_L 0x40
#define GYRO_XOUT_H 0x43
//#define GYRO_XOUT_L 0x44
#define GYRO_YOUT_H 0x45
//#define GYRO_YOUT_L 0x46
#define GYRO_ZOUT_H 0x47
//#define GYRO_ZOUT_L 0x48

uint8_t buf;
uint16_t a_x, a_y, a_z;
uint16_t g_x, g_y, g_z;
void setup() {
  Serial.begin(9600);
  //while (!Serial);
  //printf_begin();
  
  //Part B. Set up PWR, GYRO, CONFIG
  Serial.println("PWR");
  readReg(PWR_MGMT_1,&buf,1);
  buf = buf&B11011111;
  writeReg(PWR_MGMT_1,&buf, 1);
  Serial.println(buf);

  Serial.println("GYRO");
  readReg(GYRO_CONFIG,&buf,1);
  buf = buf|B00011000;
  writeReg(GYRO_CONFIG,&buf, 1);
  Serial.println(buf);

  Serial.println("CONFIG");
  readReg(CONFIG,&buf,1);
  buf = buf&B11111000;
  writeReg(CONFIG,&buf, 1);
  Serial.println(buf);
}

void loop() {
  readReg(INT_STATUS,&buf,1);
  if ((buf&B00000001) == 1)
  {
    Serial.println("Data Ready");
    readReg16(ACCEL_XOUT_H, &a_x, 2);
    readReg16(ACCEL_YOUT_H, &a_y, 2);
    readReg16(ACCEL_ZOUT_H, &a_z, 2);
    Serial.println(a_x);
    Serial.println(a_y);
    Serial.println(a_z);
    readReg16(GYRO_XOUT_H, &g_x, 2);
    readReg16(GYRO_YOUT_H, &g_y, 2);
    readReg16(GYRO_ZOUT_H, &g_z, 2);
    Serial.println(g_x);
    Serial.println(g_y);
    Serial.println(g_z);
  }
}
