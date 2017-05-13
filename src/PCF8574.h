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

#ifndef PCF8574_H
#define PCF8574_H

#include <Arduino.h>
#include <Wire.h>


#define PCF8574_DIRECCION_I2C 	0x38
#define PCF8574_MAX_CANALES 	8

#define CANAL_STATUS_OFF		0
#define CANAL_STATUS_ON			1




class PCF8574
{
  private:
    int _DIRECCION_I2C = PCF8574_DIRECCION_I2C;

    byte PCF8574::PotenciaDeDos(byte channel);
    byte PCF8574::WireReadValue();
    void PCF8574::WireWriteValue(byte value);

  public:
    PCF8574();
    PCF8574(int Address_PCF8574);

    void PCF8574::ResetPinStatus();
    bool PCF8574::SetPinStatus(byte pin, bool newstatus);
    bool PCF8574::ReadPinStatus(byte pin);
    int  PCF8574::isStatusPin(byte pin, byte value);
    int  PCF8574::GetAddress();
    void PCF8574::SetAddress(int Address_PCF8574);
    void PCF8574::DebugStatusPin(String &sreturn);
};

#endif
