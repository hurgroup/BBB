#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;

#define PERIOD 1000000


int main(){
	cout << "PWM ADC Start" << endl;

	FILE *ADCHandle = NULL;

	const char *ADC5Voltage = "/sys/bus/iio/devices/iio:device0/in_voltage5_raw";
	char ADCVoltageRead[5]={0};
	int Voltage;


	FILE *PWM0Handle = NULL;
	const char *PWM0Period = "/sys/class/pwm/pwmchip0/pwm0/period";
	const char *PWM0Dutycycle = "/sys/class/pwm/pwmchip0/pwm0/duty_cycle";
	const char *PWM0Enable = "/sys/class/pwm/pwmchip0/pwm0/enable";
	char setValue[10];

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










	for(int i=0;i<1000;i++){
		

		//ADC
		if((ADCHandle=fopen(ADC5Voltage,"r"))!=NULL){
			fread(ADCVoltageRead,sizeof(char),sizeof(ADCVoltageRead-1),ADCHandle);
			fclose(ADCHandle);
			stringstream ss(ADCVoltageRead);
			//ADCVoltageNum = ADCVoltageRead; 
			//cout << ADCVoltageRead << endl;
			
			ss >> Voltage;
			cout << "on " << i << ","  << Voltage << endl;
//			printf("%s",ADCVoltageRead);
			//sleep(1);

		}
		sprintf(setValue,"%d",int(PERIOD*Voltage/4096));
		if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite(setValue,sizeof(char),sizeof(setValue),PWM0Handle);
			fclose(PWM0Handle);
		}

		usleep(50000);
	}










	if((PWM0Handle=fopen(PWM0Dutycycle,"r+"))!=NULL){
			fwrite("0",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}

	if((PWM0Handle=fopen(PWM0Enable,"r+"))!=NULL){
			fwrite("0",sizeof(char),1,PWM0Handle);
			fclose(PWM0Handle);
	}

	cout << "PWM ADC End" << endl;
	return 0;
}
