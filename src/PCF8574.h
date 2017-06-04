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

#ifndef PCF8574_H
#define PCF8574_H

#include <Arduino.h>
#include <Wire.h>


#define PCF8574_ADDRESS_I2C 	0x21		//PARA EL PCF8574A LA DIRECCION INICIAL ES 0x38

#define PCF8574_ADDRESS_WIRE	-1

#define PCF8574_MAX_PIN			8
#define PCF8574_INT_PIN			-1			//PIN DE ARDUINO QUE SE USARA PARA CONTROLAR EL ESTADO INT

#define PIN_STATUS_OFF			0
#define PIN_STATUS_ON			1
#define PIN_STATUS_ERR			2


class PCF8574
{
  private:
    bool 	_BEING_WIRE = false;
    int 	_ADDRESS_I2C;
	int 	_ADDRESS_WIRE;
	uint8_t _PIN_INT = PCF8574_INT_PIN;
	
	volatile uint8_t _PinMode;
	volatile byte 	 _IntState = LOW;
	
    uint8_t PCF8574::PotenciaDeDos(byte pin);
	
	bool 	PCF8574::WireIsBegin();
	void 	PCF8574::WireBegin();
    uint8_t PCF8574::WireReadValue();
    void 	PCF8574::WireWriteValue(byte value);
	
	void 	PCF8574::Init(int Address_PCF8574);

  public:
    PCF8574();
	PCF8574(int Address_PCF8574);

	void 	PCF8574::begin();
	void 	PCF8574::begin(int Address_PCF8574);
	bool 	PCF8574::isBegin();
	
	void 	PCF8574::pinMode(byte pin, byte mode);
	uint8_t PCF8574::pinMode(byte pin);
	bool 	PCF8574::digitalWrite(byte pin, byte newstatus);
    uint8_t PCF8574::digitalRead(byte pin);
	
	int 	PCF8574::AddressWire();
	void 	PCF8574::AddressWire(int Address_Wire);	
	int 	PCF8574::AddressI2C();
    void 	PCF8574::AddressI2C(int Address_PCF8574);
	
	bool 	PCF8574::isPinValid(byte pin);
    void 	PCF8574::ResetPinStatus();
    uint8_t PCF8574::isStatusPin(byte pin, byte value);
	
	void  	PCF8574::DebugStatusPin(String &sreturn);
	char* 	PCF8574::DebugStatusPin();
};

#endif