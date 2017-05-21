//  Copyright (C) 2017 Javier Pastor
//  http://www.cerebelum.net
//
// Este archivo forma parte de PCF8574.
//
// PCF8574 es software libre: se puede redistribuir y / o modificar
// bajo los términos de la GNU Lesser General Public License como
// publicado por la Free Software Foundation, ya sea la versión 3 de
// la Licencia, o (a su elección) cualquier versión posterior.
//
// PCF8574 se distribuye con la esperanza de que sea útil,
// pero SIN NINGUNA GARANTÍA; Sin la garantía implícita de
// MERCANTIBILIDAD o ADECUACIÓN PARA UN PROPÓSITO PARTICULAR. Vea el
// GNU Lesser General Public License para más detalles.
//
// Debería haber recibido una copia del Público General Menor de GNU
// Licencia junto con PCF8574. Si no, vea
// <http://www.gnu.org/licenses/>.
//

#include <PCF8574.h>

#define I2C_DIRECCION_PCF8574_1 0x21    //PCF8574
#define I2C_DIRECCION_PCF8574_2 0x38    //PFC8574A


/*
   Crear objeto, por defecto se configurar el bus I2C en modo master.
   Opcional: Podemos pasarle el intervalo de pines que vamos a usar.

   Ejemplo:
      PCF8574 I2C_PCF8574;
      PCF8574 I2C_PCF8574(1, 8);
*/
PCF8574 I2C_PCF8574;           //MASTER


void setup() {
  Serial.begin(9600);


  /*
     Iniciamos el objeto y configuramos la dirección I2C del PCF8574.
     NOTA: Si vamos a usar el bus I2C en modo esclavo tendremos que configura la dirección Wire antes de ejecutar Begin().
     NOTA: Si se ha ejecutado antes en algún sitio Wire.Begin(), se usarán los datos que se hayan ejecutando antes, y la dirección Wire que tengamos configurado en el objeto no tendrá efecto.
  */
  I2C_PCF8574.begin(I2C_DIRECCION_PCF8574_2);


  /*
     Configuramos que pines del PCF8574 vamos a usar. En este caso del pin 1 al 8.
  */
  I2C_PCF8574.SetPins(1, 8);


  /*
     Configuramos todos los pines en modo OUT excepto el 8 en modo IN.
     NOTE: Todos los pines por defecto están configurados en modo IN.
  */
  I2C_PCF8574.pinMode(1, OUTPUT);
  I2C_PCF8574.pinMode(2, OUTPUT);
  I2C_PCF8574.pinMode(3, OUTPUT);
  I2C_PCF8574.pinMode(4, OUTPUT);
  I2C_PCF8574.pinMode(5, OUTPUT);
  I2C_PCF8574.pinMode(6, OUTPUT);
  I2C_PCF8574.pinMode(7, OUTPUT);
  I2C_PCF8574.pinMode(8, INPUT);


  /*
     Reseteamos todos los pines (que están configurados en modo OUT) poniéndolos en modo False.
  */
  I2C_PCF8574.ResetPinStatus();


  /*
     Ponemos todos los pines (que están configurados en modo OUT) en modo True.
     Nota: El pin numero 0 está reservado y se usa para referirse a todos los pines (que están configurados en modo OUT).
  */
  I2C_PCF8574.SetPinStatus(0, PIN_STATUS_ON);


  /*
     Ponemos los pines 1 y 6 en modo False. Se intenta también con el 8 pero al estar en modo IN no pasa nada.
  */
  I2C_PCF8574.SetPinStatus(1, PIN_STATUS_OFF);
  I2C_PCF8574.SetPinStatus(6, PIN_STATUS_OFF);
  I2C_PCF8574.SetPinStatus(8, PIN_STATUS_OFF);


  /*
     Siempre se podrá leer el estado de un pin da igual si está configurado en modo IN o OUT.
     PIN_STATUS_OFF = 0, PIN_STATUS_ON = 1, PIN_STATUS_ERR = 2
  */
  int Status_Pin5 = I2C_PCF8574.ReadPinStatus(5);
  int Status_Pin6 = I2C_PCF8574.ReadPinStatus(6);
  int Status_Pin8 = I2C_PCF8574.ReadPinStatus(8);


  /*
     Cambiamos la dirección I2C para poder controlar otro PCF8574.
  */
  I2C_PCF8574.SetAddress(I2C_DIRECCION_PCF8574_2);


  /*
     Configuramos que pines del PCF8574 vamos a usar. En este caso del pin 1 al 8.
     Al principio del código configuramos los pines de entrada y salida en un solo comando, pero podemos modificar únicamente el pin inicial o final cuando lo queramos.
     Ahora configuramos el pin numero 2 como inicial y el 5 como el final, con lo que actuaremos solo en los pines 2,3,4,5.
     NOTA: Leer el estado de cualquier pin siempre es posible, da igual el intervalo de pines configurados. Pero solo podremos actuar en la franja de pines que tengamos configurados.
     NOTA: Tener en cuenta que si cambiamos el intervalo de pines la configuración de pinMode no se verá afectada, y seguirán configurados en el estado anterior.
  */
  I2C_PCF8574.SetIniPin(2);
  I2C_PCF8574.SetEndPin(5);


  /*
     Reseteamos todos los pines del PCF8574 que tenemos configurado ahora mismo.
     Solo afectara a la franja de pines que hemos configurado antes del 2 al 5.
  */
  I2C_PCF8574.ResetPinStatus();


  /*
     Obtenemos la dirección I2C que está configurada actualmente.
     También obtenemos el Pin inicial y final que están configurados.
  */
  byte I2C_ADDRESS = I2C_PCF8574.GetAddress();
  int  PIN_INI = I2C_PCF8574.GetIniPin();
  int  PIN_END = I2C_PCF8574.GetEndPin();
}

void loop() {


}
