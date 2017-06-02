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
  I2C_PCF8574.pinMode(0, OUTPUT);
  I2C_PCF8574.ResetPinStatus();



  Serial.print("TODO >> ON >> ");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
  delay(2000);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
  delay(2000);


  I2C_PCF8574.pinMode(2, INPUT);
  I2C_PCF8574.pinMode(3, INPUT);
  I2C_PCF8574.pinMode(4, INPUT);

  Serial.println("TODO EXCEPTO 2,3,4");
  Serial.print("TODO >> ON >> ");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
  delay(2000);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
  delay(2000);




  I2C_PCF8574.pinMode(2, OUTPUT);
  I2C_PCF8574.pinMode(3, OUTPUT);
  I2C_PCF8574.pinMode(4, OUTPUT);
  I2C_PCF8574.pinMode(5, INPUT);
  I2C_PCF8574.pinMode(6, INPUT);


  Serial.println("TODO EXCEPTO 5,6");
  Serial.print("TODO >> ON >> ");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);
  delay(2000);
  Serial.println("OFF");
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_OFF);
  delay(2000);



  String vreturn;
  for (int ii = 1; ii <= 8; ii++) {
    Serial.print("PIN "); Serial.println(ii); 
    Serial.println("   > ON");
    I2C_PCF8574.SetPinStatus(ii, PIN_STATUS_ON);

    I2C_PCF8574.DebugStatusPin(vreturn);
    Serial.print("    > ON DATOS: "); Serial.println(vreturn);
    vreturn = "";

    delay(500);
    Serial.println("    > OFF");
    I2C_PCF8574.SetPinStatus(ii, PIN_STATUS_OFF);


    I2C_PCF8574.DebugStatusPin(vreturn);
    Serial.print("    > OFF DATOS: "); Serial.println(vreturn);
    vreturn = "";

    Serial.println("-------------");
    delay(1000);
  }


  Serial.println("");
  Serial.println("");


  
    for (int ii = 1; ii <= 8; ii++) {
    Serial.print("PIN "); Serial.println(ii); 
    Serial.println("    > ON");
    I2C_PCF8574.SetPinStatus(ii, PIN_STATUS_ON);

    char* creturn = I2C_PCF8574.DebugStatusPin();
    Serial.print("    > ON DATOS: "); Serial.println(creturn[0], BIN);

    delay(500);
    Serial.println("    > OFF");
    I2C_PCF8574.SetPinStatus(ii, PIN_STATUS_OFF);

    creturn = I2C_PCF8574.DebugStatusPin();
    Serial.print("    > ON DATOS: "); Serial.println(creturn[0], BIN);

    Serial.println("-------------");
    delay(1000);
  }
  delay(1000);
}
