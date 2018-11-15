#ifndef DRIVING_H
#define DRIVING_H

#include "stepper_motor.h"
#include "led.h"
#include "ldr.h"
#include "cny_70.h"
#include "Servo_t3.h"

#define MAX_LECTURES 20

class Driver{
public:
	class driver_exception{
	public:
		driver_exception(const char* error) : str_error(error)
		{}

		const char* what() const { return str_error; }

	private:
		const char* str_error;
	};

	Driver();

	void init_stepper(int stepsPerRevolution = 200, int pina = 10, int pinb = 11, int pinc = 12, int pind = 13);
	void init_cnys(short cnypd = 14,short cnypt = 15);
	void init_servos(int sp = 1, int sd = 9);
	void init_leds(short pinled = 0);
	void init_ldrs(short ldr_tambor = 19,short ldrza = 16, short ldrzb = 17, short ldrzc = 18);

	void oneStepAtATime();
	void oneRevolution();
	void goneAndBack();
	void modulateSpeed(long);
	void goOn(int);
	void forceStop();

	void turnOn();
	void turnOff();
	void blink_leds(uint16_t);

	void servos_initial_state();
	short watch_initial();
	short watch_base();
	short watch_final();

	short watch_initial_phase();
	short watch_base_phase();
	short watch_final_phase();

	short check_dice(uint16_t index);
	short check_cube(uint16_t index);

	void free_steppers();
	void free_cnys();
	void free_servos();
	void free_leds();
	void free_ldrs();

	void re_init();
	//void suspend();
	void check_initialized() const;

private:
	Stepper* stepper;
	Led* led;
	CNY* cnya;
	CNY* cnyb;
	LDR* ldra;
	LDR* ldrb;
	LDR* ldrc;
	LDR* ldrd;
	Servo* servoa;
	Servo* servob;
};

#endif //DRIVING_H