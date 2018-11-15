#include "led.h"
#include "Arduino.h"

Led::Led(short ledp,short stat): pin_led(ledp), status(stat){pinMode(ledp, OUTPUT);}
short Led::lightup(){digitalWrite(this->pin_led, HIGH); short aux = this->status; this->status = ON; return aux;}
short Led::turnoff(){digitalWrite(this->pin_led, LOW); short aux = this->status; this->status = OFF; return aux;}
short Led::check_status(){return this->status;}