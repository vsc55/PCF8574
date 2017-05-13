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

#include "PCF8574.h"


PCF8574::PCF8574() {
  if (TWCR == 0)
  {
    Wire.begin();
  }
}


/****************************************************************
 *
 * @Address_PCF8574				Direccion i2C de nuestro PCF8574.
 *
 ****************************************************************/
PCF8574::PCF8574(int Address_PCF8574) {
  SetAddress(Address_PCF8574);
  if (TWCR == 0)
  {
    Wire.begin();
  }
}


int PCF8574::GetAddress() {
  return _DIRECCION_I2C;
}


void PCF8574::SetAddress(int Address_PCF8574) {
  _DIRECCION_I2C = Address_PCF8574;
}


byte PCF8574::PotenciaDeDos(byte channel) {
  switch ( channel )
  {
    case 1:
      return 1;
    case 2:
      return 2;
    default:
      //le tenemos que sumar uno por que al pasar el float a int redondea a la baja.
      return int (pow (2, channel - 1)) + 1 ;
  }
}


byte PCF8574::WireReadValue() {
  byte value = 0;
  Wire.requestFrom(GetAddress(), 1);
  if (Wire.available())
  {
    value = Wire.read();
  }
  return value;
}


void PCF8574::WireWriteValue(byte value) {
  Wire.beginTransmission(GetAddress());
  Wire.write(value);
  Wire.endTransmission();
}


void PCF8574::ResetPinStatus() {
  SetPinStatus(0, false);
}


boolean PCF8574::SetPinStatus(byte pin, byte newstatus) {
  if ((pin > PCF8574_MAX_CANALES) || (pin < 0)) {
    return false;
  }

  byte value = 0;
  if (pin == 0) {
    if (newstatus == CANAL_STATUS_ON) {
      value = 0;
    } else {
      value = 255;
    }
  }
  else {
    //COMPROBAMOS EL ESTADO DEL PIN
    bool StatusPinActual = ReadPinStatus(pin);
    if (newstatus == CANAL_STATUS_ON) {
      if (StatusPinActual == true) {
        //SI NUEVO STATUS ES TRUE Y YA ESTA COMO TRUE NO HACEMOS CAMBIO
        return true;
      }
    } else {
      if (StatusPinActual == false) {
        //SI EL NUEVO STATUS ES FALSE Y YA ESTA COMO FALSE NO HACEMOS CAMBIO.
        return true;
      }
    }
    //value = 255;    //TODO APAGADO
    value = 0;        //TODO ENCENDIDO

    for (byte channel = 1; channel < 9; channel++)
    {
      if (channel == pin) {
        if (newstatus == false) {
          value +=  PotenciaDeDos(channel);
        }
      }
      else {
        if (ReadPinStatus(channel) == false) {
          value +=  PotenciaDeDos(channel);
        }
      }
    }
  }
  WireWriteValue(value);		//ENVIA EL NUEVO CODIGO
  return true;
}


void PCF8574::DebugStatusPin(String &sreturn) {
  for (int channel = 1; channel < 9; channel++)
  {
    sreturn = sreturn + ReadPinStatus(channel);
  }
}


bool PCF8574::ReadPinStatus(byte pin) {

  if ((pin > PCF8574_MAX_CANALES) || (pin < 0)) {
    return false;
  }
  
  byte value = WireReadValue();
  if (isStatusPin(pin, value) == 1) {
    return true;
  }
  else {
    return false;
  }
}

int PCF8574::isStatusPin(byte pin, byte value) {
  int pin1 = 1;
  int pin2 = 1;
  int pin3 = 1;
  int pin4 = 1;
  int pin5 = 1;
  int pin6 = 1;
  int pin7 = 1;
  int pin8 = 1;

  if (value >= 128 ) {
    pin8 = 0;
    value -= 128;
  }
  if (value >= 64 ) {
    pin7 = 0;
    value -= 64;
  }
  if (value >= 32 ) {
    pin6 = 0;
    value -= 32;
  }
  if (value >= 16 ) {
    pin5 = 0;
    value -= 16;
  }
  if (value >= 8 ) {
    pin4 = 0;
    value -= 8;
  }
  if (value >= 4 ) {
    pin3 = 0;
    value -= 4;
  }
  if (value >= 2 ) {
    pin2 = 0;
    value -= 2;
  }
  if (value >= 1 ) {
    pin1 = 0;
    value -= 1;
  }

  switch ( pin )
  {
    case 1:
      return pin1;
    case 2:
      return pin2;
    case 3:
      return pin3;
    case 4:
      return pin4;
    case 5:
      return pin5;
    case 6:
      return pin6;
    case 7:
      return pin7;
    case 8:
      return pin8;

    default:
      return -1;
  }
}