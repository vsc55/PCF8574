//  Copyright (C) 2017 Javier Pastor
//  http://www.cerebelum.net
//
// Este archivo forma parte de PCF8574.
//
// PCF8574 es software libre: se puede redistribuir y / o modificar
// bajo los t�rminos de la GNU Lesser General Public License como
// publicado por la Free Software Foundation, ya sea la versi�n 3 de
// la Licencia, o (a su elecci�n) cualquier versi�n posterior.
//
// PCF8574 se distribuye con la esperanza de que sea �til,
// pero SIN NINGUNA GARANT�A; Sin la garant�a impl�cita de
// MERCANTIBILIDAD o ADECUACI�N PARA UN PROP�SITO PARTICULAR. Vea el
// GNU Lesser General Public License para m�s detalles.
//
// Deber�a haber recibido una copia del P�blico General Menor de GNU
// Licencia junto con PCF8574. Si no, vea
// <http://www.gnu.org/licenses/>.
//

#include "PCF8574.h"


PCF8574::PCF8574() {
  this->_PinMode = 0;
  
  this->AddressI2C(PCF8574_ADDRESS_I2C);
  this->AddressWire(PCF8574_ADDRESS_WIRE);
}
PCF8574::PCF8574(int Address_PCF8574) {
  this->_PinMode = 0;
  
  this->AddressI2C(Address_PCF8574);
  this->AddressWire(PCF8574_ADDRESS_WIRE);
}




void PCF8574::begin() {
	this->WireBegin();
}
void PCF8574::begin(int Address_PCF8574) {
	this->AddressI2C(Address_PCF8574);
	this->WireBegin();
}




int PCF8574::AddressWire() {
  return this->_ADDRESS_WIRE;
}
void PCF8574::AddressWire(int Address_Wire) {
  this->_ADDRESS_WIRE = Address_Wire;
}
int PCF8574::AddressI2C() {
  return this->_ADDRESS_I2C;
}
void PCF8574::AddressI2C(int Address_PCF8574) {
  this->_ADDRESS_I2C = Address_PCF8574;
}




uint8_t PCF8574::PotenciaDeDos(byte pin) {
  switch ( pin )
  {
    case 1:
      return 1;
    case 2:
      return 2;
	case 3:
	  return 4;
	case 4:
	  return 8;
	case 5:
	  return 16;
	case 6:
	  return 32;
	case 7:
	  return 64;
	case 8:
	  return 128;
	
    default:
      //le tenemos que sumar uno por que al pasar el float a int redondea a la baja.
      return 0; //byte (pow (2, pin - 1)) + 1 ;
  }
}




bool PCF8574::WireIsBegin() {
	if (TWCR == 0) { return false; }
	else { return true; }
}
void PCF8574::WireBegin() {
  if (this->_BEING_WIRE == false) {
    if (this->WireIsBegin() == false)
	{
	  if (this->AddressWire() < 0 ) {
	    Wire.begin();
	  }
	  else {
	    Wire.begin(this->AddressWire());
	  }
	  this->_BEING_WIRE = true;
	}
	else {
	  this->AddressWire(-2);
	}
  }
}
uint8_t PCF8574::WireReadValue() {
  byte value = 0;
  Wire.requestFrom(this->AddressI2C(), 1);
  if (Wire.available())
  {
    value = Wire.read();
  }
  return value;
}
void PCF8574::WireWriteValue(byte value) {
  Wire.beginTransmission(AddressI2C());
  Wire.write(value);
  Wire.endTransmission();
}




bool PCF8574::isPinValid(byte pin) {
  if ((pin > PCF8574_MAX_PIN) || (pin < 0)) {
    return false;
  }
  return true;
}
void PCF8574::pinMode(byte pin, byte mode) {
  if (this->isPinValid(pin) == true) {
    if (pin == 0) {
	  for (byte i = 1; i <= PCF8574_MAX_PIN; i++) {
        this->pinMode(i, mode);
	  }
    }
    else {
      switch (mode) {
        case INPUT:
          this->_PinMode &= ~(1 << (pin -1));
          break;
        case OUTPUT:
          this->_PinMode |= (1 << (pin-1));
          break;
        default:
          break;
      }
    }
  }
}
uint8_t PCF8574::pinMode(byte pin) {
	return (this->_PinMode >> (pin-1)) & 0x1;
}





void PCF8574::ResetPinStatus() {
  this->digitalWrite(0, false);
}

boolean PCF8574::digitalWrite(byte pin, byte newstatus) {
  if (this->isPinValid(pin) == false) {
    return false;
  }
  
  byte value = 0;
  if (pin == 0) {
	value = 0;        //TODO ENCENDIDO
	for (byte i = 1; i <= PCF8574_MAX_PIN; i++) {
	  this->digitalWrite(i,newstatus);
	}
	return true;
  }
  else {
	if (this->pinMode(pin) == INPUT) {
		return false;
	}  
    //COMPROBAMOS EL ESTADO DEL PIN
    byte StatusPinActual = this->digitalRead(pin);
    if (newstatus == PIN_STATUS_ON) {
      if (StatusPinActual == PIN_STATUS_ON) {
        //SI NUEVO STATUS ES TRUE Y YA ESTA COMO TRUE NO HACEMOS CAMBIO
        return true;
      }
    } else {
      if (StatusPinActual == PIN_STATUS_OFF) {
        //SI EL NUEVO STATUS ES FALSE Y YA ESTA COMO FALSE NO HACEMOS CAMBIO.
        return true;
      }
    }
	
    //value = 255;    //TODO APAGADO
    value = 0;        //TODO ENCENDIDO
    for (byte ipin = 1; ipin <= PCF8574_MAX_PIN; ipin++)
    {
      if (ipin == pin) {
        if (newstatus == PIN_STATUS_ON) {
          continue;
        }
      }
	  else {
        if (this->digitalRead(ipin) == PIN_STATUS_ON) {
          continue;
        }
	  }
      value += this->PotenciaDeDos(ipin);
    }
  }

  this->WireWriteValue(value);		//ENVIA EL NUEVO CODIGO
  return true;
}

uint8_t PCF8574::digitalRead(byte pin) {
  if (this->isPinValid(pin) == false) {
    return PIN_STATUS_ERR;
  }
  if (this->isStatusPin(pin, this->WireReadValue()) == 1) {
    return PIN_STATUS_ON;
  }
  else {
    return PIN_STATUS_OFF;
  }
}

uint8_t PCF8574::isStatusPin(byte pin, byte value) {
  if (this->isPinValid(pin) == false) {
    return -1;
  }
  //value = 255;    //TODO APAGADO
  //value = 0;      //TODO ENCENDIDO
  value = 255 - value;
  return (value >> (pin -1)) & 0x1;
}





//TODO: PENDIENTE DEPURAR.
void PCF8574::DebugStatusPin(String &sreturn) {
  for (byte pin = 1; pin <= PCF8574_MAX_PIN; pin++)
  {
    sreturn = sreturn + this->digitalRead(pin);
  }
}

char* PCF8574::DebugStatusPin(){
    char* str;
	for (byte i = 0; i < PCF8574_MAX_PIN; i++)
	{
		str[i] = this->digitalRead(i + 1);
	}
    return str;
}