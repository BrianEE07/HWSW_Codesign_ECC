#include<io51.h>

void init(void){
	P0=0;
	P1=0;
	P2=0;
	P3=0;
}

int main(void){
	unsigned char i;
	
	init();

	P0 = 1;
	P1 = 59;
	P1 = 0;
	P1 = 230;
	P1 = 202;
	P1 = 170;
	P1 = 27;
	
}