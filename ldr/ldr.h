#ifndef LDR_H
#define LDR_H

class LDR{
public:
	LDR(short ldrp, short stat = 0);
	LDR(const LDR& ldr);
	int read_status();

private:
	short pin_ldr;
	int status;	
};

#endif //LDR_H
