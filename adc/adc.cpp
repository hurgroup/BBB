#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>
using namespace std;

int main(){
	cout << "ADC Start" << endl;

	FILE *ADCHandle = NULL;
	const char *ADC5Voltage = "/sys/bus/iio/devices/iio:device0/in_voltage5_raw";
	
	char ADCVoltageRead[5]={0};
	int Voltage;

	while(1){
		if((ADCHandle=fopen(ADC5Voltage,"r"))!=NULL){
			fread(ADCVoltageRead,sizeof(char),sizeof(ADCVoltageRead-1),ADCHandle);
			fclose(ADCHandle);
			stringstream ss(ADCVoltageRead);
			//ADCVoltageNum = ADCVoltageRead; 
			//cout << ADCVoltageRead << endl;
			
			ss >> Voltage;
			cout << Voltage << endl;
//			printf("%s",ADCVoltageRead);
			//sleep(1);
			usleep(50000);

		}

	}
	cout << "ADC End" << endl;
	return 0;
}
