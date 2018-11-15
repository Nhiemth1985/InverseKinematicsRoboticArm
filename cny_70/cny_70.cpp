#include <cny_70.h>
#include <Arduino.h>

CNY::CNY(short cnyp,short stat): pin_cny(cnyp), status(stat){pinMode(cnyp, INPUT);}

CNY::CNY(const CNY& cny) : pin_cny(cny.pin_cny),status(cny.status){}

int CNY::read_status(){
	this->status = analogRead(pin_cny); 
    delay(100);

    return this->status;
}