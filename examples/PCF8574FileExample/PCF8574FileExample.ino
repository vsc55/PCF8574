#include <PCF8574.h>

#define I2C_DIRECCION_PCF8574_1 0x38
#define I2C_DIRECCION_PCF8574_2 0x38


/*
   Crear objeto, por defecto se configurar el bus I2C en modo master.
   Si le pasamos la dirección se usará esa en el bus I2C.

   I2C_PCF8574(I2C_DIRECCION_PCF8574_1, Optional I2C_ADDRES_DEVICE);
   
   Ejemplo:
      PCF8574 I2C_PCF8574(I2C_DIRECCION_PCF8574_1);
      PCF8574 I2C_PCF8574(I2C_DIRECCION_PCF8574_1, 0x11);
*/
PCF8574 I2C_PCF8574(I2C_DIRECCION_PCF8574_1);           //MASTER


void setup() {
  Serial.begin(9600);


  /*
     Reseteamos todos los canales y se ponen en modo False.
  */
  I2C_PCF8574.ResetPinStatus();


  /*
     Ponemos todos los canales en modo True.
     Nota: El canal numero 0 está reservado y se usa para referirse a todos los canales.
  */
  I2C_PCF8574.SetPinStatus(0, CANAL_STATUS_ON);


  /*
     Ponemos los canales 1 y 6 en modo False.
  */
  I2C_PCF8574.SetPinStatus(1, CANAL_STATUS_OFF);
  I2C_PCF8574.SetPinStatus(6, CANAL_STATUS_OFF);


  /*
     Leemos el estado de los canales 5 y 7 que ahora tiene un valor de true y false respetivamente.
  */
  int pin5 = I2C_PCF8574.ReadPinStatus(5);
  int pin6 = I2C_PCF8574.ReadPinStatus(6);


  /*
     Cambiamos la dirección I2C para poder controlar otro PCF8574.
  */
  I2C_PCF8574.SetAddress(I2C_DIRECCION_PCF8574_2);


  /*
     Reseteamos todos los canales del PCF8574 que tenemos configurado ahora mismo.
  */
  I2C_PCF8574.ResetPinStatus();


  /*
     Obtenemos la dirección I2C que está configurada actualmente.
  */
  byte I2C_ADDRESS = I2C_PCF8574.GetAddress();

}

void loop() {


}
