#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

#define PERIOD 1000000

int main(){
	cout << "PWM Start" << endl;

	FILE *PWM0Handle = NULL;
	const char *PWM0Period = "/sys/class/pwm/pwmchip0/pwm0/period";
	const char *PWM0Dutycycle = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
	const char *PWM0Enable = "/sys/class/pwm/pwmchip0/pwm0/enable";
	char setValue[10];



//	strcpy(setValue,GPIOString);
//	fwrite(&setValue,sizeof(char),2,LEDHandle);


	if((PWM0Handle=fopen(PWM0Period,"r+"))!=NULL){
			fwrite("1000000",sizeof(char),7,PWM0Handle);
			fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite("0",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Enable,"r+"))!=NULL){
			fwrite("1",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}

	for(int i=0;i<10;i++){
		cout << "on " <<i << endl;
		//strcpy(setValue,GPIOString);
		sprintf(setValue,"%d",int(PERIOD*i/10));
		if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite(setValue,sizeof(char),sizeof(setValue),PWM0Handle);
			fclose(PWM0Handle);
		}
		sleep(1);
	}

	if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite("0",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Enable,"r+"))!=NULL){
			fwrite("0",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}


	cout << "PWM End" << endl;
	return 0;
}
