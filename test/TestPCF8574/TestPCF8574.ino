#include <PCF8574.h>

#define I2C_DIRECCION_PCF8574_1 0x38
#define I2C_DIRECCION_PCF8574_2 0x38


PCF8574 I2C_PCF8574;           //MASTER


void setup() {
  Serial.begin(9600);

  I2C_PCF8574.begin(I2C_DIRECCION_PCF8574_1);
  I2C_PCF8574.ResetPinStatus();
}

void loop() {

  Serial.println("");
  I2C_PCF8574.ResetPinStatus();
  I2C_PCF8574.SetPins(1, 8);

  Serial.print("TODO >> ON >> ");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
  delay(5000);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
  delay(5000);


  I2C_PCF8574.pinMode(2, OUTPUT);
  I2C_PCF8574.pinMode(3, OUTPUT);
  I2C_PCF8574.pinMode(4, OUTPUT);



  Serial.print("TODO >> ON >> ");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
  //I2C_PCF8574.SetIniPin(2);
  I2C_PCF8574.SetEndPin(5);
  delay(5000);
  Serial.println("OFF DEL 2 AL 5");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
  delay(10000);









  Serial.print("PIN 1 > ON >");
  I2C_PCF8574.SetPinStatus(1, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(1, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 2 > ON >");
  I2C_PCF8574.SetPinStatus(2, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(2, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 3 > ON >");
  I2C_PCF8574.SetPinStatus(3, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(3, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 4 > ON >");
  I2C_PCF8574.SetPinStatus(4, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(4, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 5 > ON >");
  I2C_PCF8574.SetPinStatus(5, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(5, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 6 > ON >");
  I2C_PCF8574.SetPinStatus(6, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(6, PIN_STATUS_OFF);
  delay(1000);


  Serial.print("PIN 7 > ON >");
  I2C_PCF8574.SetPinStatus(7, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(7, PIN_STATUS_OFF);
  delay(1000);



  Serial.print("PIN 8 > ON >");
  I2C_PCF8574.SetPinStatus(8, PIN_STATUS_ON);
  delay(500);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(8, PIN_STATUS_OFF);
  delay(1000);



  /*
    Serial.println("TODO ON");
    I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
    Serial.println("APAGAR DEL 2 AL 6");
    I2C_PCF8574.GetIniPin(2);
    I2C_PCF8574.GetEndPin(6);
    I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
    delay(10000);

    Serial.println("OFF DEL 1 AL 7");
    I2C_PCF8574.SetPinStatus(1, PIN_STATUS_OFF);
    I2C_PCF8574.SetPinStatus(7, PIN_STATUS_OFF);
    delay(10000);
  */
}
