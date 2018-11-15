#ifndef LED_H
#define LED_H

#define OFF 0x00
#define ON 0x01

class Led{
public:
	Led(short ledp, short stat = 0);
	short lightup();
	short turnoff();
	short check_status();
private:
	short pin_led;
	short status;
};

#endif //LED_H
