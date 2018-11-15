#include <Driving.h>
#include <Arduino.h>

Driver::Driver() : stepper(0), led(0), cnya(0), cnyb(0), ldra(0),ldrb(0),ldrc(0),ldrd(0), servoa(0),servob(0){}

void Driver::init_stepper(int stepsPerRevolution, int pina, int pinb, int pinc, int pind){stepper = new Stepper(stepsPerRevolution,pina,pinb,pinc,pind);}
void Driver::init_leds(short pinled){led = new Led(pinled);}
void Driver::init_cnys(short cnypd,short cnypt){cnya = new CNY(cnypd); cnyb = new CNY(cnypt);}
void Driver::init_servos(int sp, int sd){servoa = new Servo(); servoa->attach(sp); servob = new Servo(); servob->attach(sd);}
void Driver::init_ldrs(short ldr_tambor,short ldrza, short ldrzb, short ldrzc){ldra = new LDR(ldr_tambor); ldrb = new LDR(ldrza); ldrc = new LDR(ldrzb); ldrd = new LDR(ldrzc);}

void Driver::oneStepAtATime(){stepper->step(1); delay(200);}
void Driver::oneRevolution(){stepper->step(200); delay(200);}
void Driver::goneAndBack(){stepper->step(-80); delay(2000); stepper->step(80); delay(2000);}
void Driver::modulateSpeed(long whatSpeed){stepper->setSpeed(whatSpeed);}
void Driver::goOn(int steps){stepper->step(steps);}
void Driver::forceStop(){stepper->step(0); delay(100);}

void Driver::blink_leds(uint16_t index){
	for(short i=0; i<index; ++i){
		led->lightup();
		delay(500);
		led->turnoff();
		delay(500);
	}
}

void Driver::turnOff(){led->turnoff(); delay(5000);}
void Driver::turnOn(){led->lightup(); delay(5000);}

short Driver::check_dice(uint16_t index){

	short to_mean = 0;

	switch(index){
		case 0:	for(uint16_t i; i<MAX_LECTURES; ++i){
					to_mean = cnya->read_status();
					delay(100);
				}
				break;
		case 1: for(uint16_t i; i<MAX_LECTURES; ++i){
					to_mean = cnyb->read_status();
					delay(100);
				}
				break;
	}

	if(to_mean/MAX_LECTURES > 600) {Serial.println("CARA BLANCA"); return 1;}
	else {Serial.println("CARA NEGRA"); return 0;}
}

short Driver::check_cube(uint16_t index){
	switch(index){
		case 0: if(ldra->read_status() != 0){Serial.println("HAY CUBO EN EL TAMBOR"); return 1;}
				else{return 0;}
				break;
		case 1:	if(ldrb->read_status() != 0){Serial.println("HAY CUBO EN ALMACEN 1"); return 1;}
				else{return 0;}
				break;
		case 2:	if(ldrc->read_status() != 0){Serial.println("HAY CUBO EN ALMACEN 2"); return 1;}
				else{return 0;}
				break;
		case 3: if(ldrd->read_status() != 0){Serial.println("HAY CUBO EN ALMACEN 3"); return 1;}
				else{return 0;}
				break;
	}
}

void Driver::servos_initial_state(){
	servoa->write(10);
	delay(100);
	servob->write(180);
	delay(100);
}
short Driver::watch_initial(){servoa->write(10);  delay(500); check_dice(0);}
short Driver::watch_base(){servoa->write(70);  delay(500); check_dice(0);}
short Driver::watch_final(){servoa->write(120);  delay(500); check_dice(0);}

short Driver::watch_initial_phase(){servob->write(180);  delay(500); check_dice(1);}
short Driver::watch_base_phase(){servob->write(85);  delay(500); check_dice(1);}
short Driver::watch_final_phase(){servob->write(5);  delay(500); check_dice(1);}

void Driver::free_steppers(){delete stepper;}
void Driver::free_leds(){delete led;}
void Driver::free_cnys(){delete cnya; delete cnyb;}
void Driver::free_servos(){delete servoa; delete servob;}
void Driver::free_ldrs(){delete ldra; delete ldrb; delete ldrc; delete ldrd;}

void Driver::re_init(){
	servos_initial_state();
	stepper->step(80);
}
//void Driver::suspend(){}
void Driver::check_initialized() const  {if (!stepper or !led or !ldra or !ldrb or !ldrc or !ldrd or !cnya or !cnyb or !servoa or !servob) Serial.println("Class Driver must be initialized");}
