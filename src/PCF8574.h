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


#define PCF8574_DIRECCION_I2C 	0x38
#define PCF8574_DIRECCION_WIRE	-1
#define PCF8574_MAX_PIN 		8
#define PCF8574_INI_PIN			1

#define PIN_STATUS_OFF			0
#define PIN_STATUS_ON			1


class PCF8574
{
  private:
    int _DIRECCION_I2C = PCF8574_DIRECCION_I2C;
	int _DIRECCION_WIRE = PCF8574_DIRECCION_WIRE;
	int _PIN_INI = PCF8574_INI_PIN;
	int _PIN_END = PCF8574_MAX_PIN;

    byte PCF8574::PotenciaDeDos(byte pin);
	
	void PCF8574::WireBegin();
	int  PCF8574::GetAddressWire();
	void PCF8574::SetAddressWire(int Address_Wire);	
    byte PCF8574::WireReadValue();
    void PCF8574::WireWriteValue(byte value);
	

  public:
    PCF8574();
    PCF8574(int Address_PCF8574);
	PCF8574(int Address_PCF8574, int Address_Wire);
	PCF8574(int Address_PCF8574, int Address_Wire, int PinIni, int PinEnd);

    void PCF8574::ResetPinStatus();
    bool PCF8574::SetPinStatus(byte pin, byte newstatus);
    bool PCF8574::ReadPinStatus(byte pin);
    int  PCF8574::isStatusPin(byte pin, byte value);
    int  PCF8574::GetAddress();
    void PCF8574::SetAddress(int Address_PCF8574);
    void PCF8574::DebugStatusPin(String &sreturn);
	
	int  PCF8574::GetIniPin();
	bool PCF8574::SetIniPin(int pin);
	int  PCF8574::GetEndPin();
	bool PCF8574::SetEndPin(int pin);
};

#endif
