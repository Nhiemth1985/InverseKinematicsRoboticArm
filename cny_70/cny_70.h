#ifndef CNY_70_H
#define CNY_70_H

class CNY{
public:
	CNY(short cnyp, short stat = 0);
	CNY(const CNY& cny);
	int read_status();

private:
	short pin_cny;
	int status;	
};

#endif //CNY_70_H