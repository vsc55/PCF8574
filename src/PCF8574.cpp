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
  this->Init(PCF8574_ADDRESS_I2C);
}
PCF8574::PCF8574(int Address_PCF8574) {
  this->Init(Address_PCF8574);
}




void 	PCF8574::Init(int Address_PCF8574) {
  this->_PinMode = 0;
  this->AddressI2C(Address_PCF8574);
  this->AddressWire(PCF8574_ADDRESS_WIRE);
}
void 	PCF8574::begin() {
	this->WireBegin();
}
void 	PCF8574::begin(int Address_PCF8574) {
	this->AddressI2C(Address_PCF8574);
	this->WireBegin();
}
bool 	PCF8574::isBegin() {
	return this->_BEING_WIRE;
}



int  	PCF8574::AddressWire() {
  return this->_ADDRESS_WIRE;
}
void 	PCF8574::AddressWire(int Address_Wire) {
  this->_ADDRESS_WIRE = Address_Wire;
}
int  	PCF8574::AddressI2C() {
  return this->_ADDRESS_I2C;
}
void 	PCF8574::AddressI2C(int Address_PCF8574) {
  this->_ADDRESS_I2C = Address_PCF8574;
}




uint8_t PCF8574::PotenciaDeDos(byte pin) {
  if (pin < 0) { return 0; }
  return (1 << (pin - 1));
}




bool 	PCF8574::WireIsBegin() {
	if (TWCR == 0) { return false; }
	else { return true; }
}
void 	PCF8574::WireBegin() {
  if (this->_BEING_WIRE == false) {
	if (this->_PIN_INT >= 0) {
	  //pinMode(this->_PIN_INT, INPUT_PULLUP);
	  //attachInterrupt(this->_PIN_INT, pin_ISR, CHANGE);
	  //https://www.arduino.cc/en/Reference/AttachInterrupt
	  //https://www.allaboutcircuits.com/technical-articles/using-interrupts-on-arduino/
	}
	  
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
void 	PCF8574::WireWriteValue(byte value) {
  Wire.beginTransmission(AddressI2C());
  Wire.write(value);
  Wire.endTransmission();
}




bool 	PCF8574::isPinValid(byte pin) {
  if ((pin > PCF8574_MAX_PIN) || (pin < 0)) {
    return false;
  }
  return true;
}
void 	PCF8574::pinMode(byte pin, byte mode) {
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





void 	PCF8574::ResetPinStatus() {
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