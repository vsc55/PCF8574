#include <PCF8574.h>

#define I2C_DIRECCION_PCF8574_1 0x38
#define I2C_DIRECCION_PCF8574_2 0x38

//definimos el objeto
PCF8574 I2C_PCF8574(I2C_DIRECCION_PCF8574);

void setup() {
  Serial.begin(9600);

  //PONE TODOS LOS PINES EN FALSE
  IC_PCF8574.ResetPinStatus();

  //PONE TODOS LOS PINES A TURE
  IC_PCF8574.SetPinStatus(0, true);

  //PONE EL PIN 1 Y 6 EN FALSE
  I2C_PCF8574.SetPinStatus(1, false);
  I2C_PCF8574.SetPinStatus(6, false);

  //leemos el estado del pin 5 y 6 que tiene un valor de true y false respectivamente.
  int pin5 = I2C_PCF8574.ReadPinStatus(5);
  int pin6 = I2C_PCF8574.ReadPinStatus(6);

  //cambiamos del la direccion I2C del PCF8574 para poder ablar con otro PCF8574.
  I2C_PCF8574.SetAddress(I2C_DIRECCION_PCF8574_2)

  //ahora reseteamos todos los pines del PCF8574 del segundo canal I2C.
  IC_PCF8574.ResetPinStatus();

  //obtenemos la direccion I2C que estamos usando ahora.
  byte I2C_ADDRESS = I2C_PCF8574.SetAddress();

}

void loop() {


}
