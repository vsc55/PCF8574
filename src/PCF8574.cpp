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
  this->_PinMode = 0;
  
  this->SetAddress(PCF8574_ADDRESS_I2C);
  this->SetAddressWire(PCF8574_ADDRESS_WIRE);
}
PCF8574::PCF8574(int Address_PCF8574) {
  this->_PinMode = 0;
  
  this->SetAddress(Address_PCF8574);
  this->SetAddressWire(PCF8574_ADDRESS_WIRE);
}




void PCF8574::begin() {
	this->WireBegin();
}
void PCF8574::begin(int Address_PCF8574) {
	this->SetAddress(Address_PCF8574);
	this->WireBegin();
}




int  PCF8574::GetAddressWire() {
  return this->_ADDRESS_WIRE;
}
void PCF8574::SetAddressWire(int Address_Wire) {
  this->_ADDRESS_WIRE = Address_Wire;
}
int  PCF8574::GetAddress() {
  return this->_ADDRESS_I2C;
}
void PCF8574::SetAddress(int Address_PCF8574) {
  this->_ADDRESS_I2C = Address_PCF8574;
}




bool PCF8574::IsPowerOfTwo (long x) {
  return (x > 0) && (x & (x-1) == 0);
}
byte PCF8574::PotenciaDeDos(byte pin) {
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
      return int (pow (2, pin - 1)) + 1 ;
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
	  if (this->GetAddressWire() < 0 ) {
	    Wire.begin();
	  }
	  else {
	    Wire.begin(this->GetAddressWire());
	  }
	  this->_BEING_WIRE = true;
	}
	else {
	  this->SetAddressWire(-2);
	}
  }
}
byte PCF8574::WireReadValue() {
  byte value = 0;
  Wire.requestFrom(this->GetAddress(), 1);
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




bool PCF8574::isPinValid(int pin) {
  if ((pin > PCF8574_MAX_PIN) || (pin < 0)) {
    return false;
  }
  return true;
}
void PCF8574::pinMode(int pin, int mode) {
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
int  PCF8574::pinMode(int pin) {
	return (this->_PinMode >> (pin-1)) & 0x1;
}





void PCF8574::ResetPinStatus() {
  this->SetPinStatus(0, false);
}

boolean PCF8574::SetPinStatus(byte pin, byte newstatus) {
  if (this->isPinValid(pin) == false) {
    return false;
  }
  
  byte value = 0;
  if (pin == 0) {
	value = 0;        //TODO ENCENDIDO
	for (byte i = 1; i <= PCF8574_MAX_PIN; i++) {
	  this->SetPinStatus(i,newstatus);
	}
	return true;
  }
  else {
	if (this->pinMode(pin) == INPUT) {
		return false;
	}  
    //COMPROBAMOS EL ESTADO DEL PIN
    int StatusPinActual = this->digitalRead(pin);
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

  WireWriteValue(value);		//ENVIA EL NUEVO CODIGO
  return true;
}

int PCF8574::digitalRead(byte pin) {
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

int PCF8574::isStatusPin(byte pin, byte value) {
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
  for (int pin = 1; pin <= PCF8574_MAX_PIN; pin++)
  {
    sreturn = sreturn + this->digitalRead(pin);
  }
}

char* PCF8574::DebugStatusPin(){
    char* str;
	for (int i = 0; i < PCF8574_MAX_PIN; i++)
	{
		str[i] = this->digitalRead(i + 1);
	}
    return str;
}