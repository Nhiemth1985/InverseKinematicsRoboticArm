#include <ldr.h>
#include <Arduino.h>

LDR::LDR(short ldrp,short stat): pin_ldr(ldrp), status(stat){pinMode(ldrp, INPUT);}

LDR::LDR(const LDR& ldr) : pin_ldr(ldr.pin_ldr),status(ldr.status){}

int LDR::read_status(){
    int lect = analogRead(pin_ldr); 

    if(lect >=450) this->status = 1;
    else this->status = 0;
      
    delay(100);

    return this->status;
}