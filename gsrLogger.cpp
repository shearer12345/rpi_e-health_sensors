/*
 *  eHealth sensor platform for Arduino and Raspberry from Cooking-hacks.
 *
 *  Description: "The e-Health Sensor Shield allows Arduino and Raspberry Pi 
 *  users to perform biometric and medical applications by using 9 different 
 *  sensors: Pulse and Oxygen in Blood Sensor (SPO2), Airflow Sensor (Breathing),
 *  Body Temperature, Electrocardiogram Sensor (ECG), Glucometer, Galvanic Skin
 *  Response Sensor (GSR - Sweating), Blood Pressure (Sphygmomanometer) and 
 *  Patient Position (Accelerometer)."
 *
 *  In this example we read the values in volts of EMG sensor and show
 *  these values in the serial monitor. 
 *
 *  Copyright (C) 2012 Libelium Comunicaciones Distribuidas S.L.
 *  http://www.libelium.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Version 2.0
 *  Author: Luis Martin & Ahmad Saad & Anartz Nuin
 */

//Include eHealth library
#include "eHealth.h"
#include <iostream>
#include <fstream>
#include <ctime>

std::ofstream myfile;

void setup() {
	myfile.open ("gsrOutput.tsv");
	std::cout << "Conductance" << std::endl;    
	myfile << "date\tconductance" << std::endl;    
}
	
void loop() { 
	
	float conductance = 0.0f;

	const int samplesPerWindow = 10; 
	const int averageWindow = 20;
	for (int i = 0; i < samplesPerWindow; i++)
	{
		conductance += eHealth.getSkinConductance();
		//float resistance = eHealth.getSkinResistance();
		//float conductanceVol = eHealth.getSkinConductanceVoltage();
		delay(averageWindow/samplesPerWindow);
	}
	conductance /= samplesPerWindow;

	timeval curTime;
	gettimeofday(&curTime, NULL);
	int milli = curTime.tv_usec / 1000;

	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer,sizeof(buffer),"%Y-%m-%dT%H:%M:%S",timeinfo);

	char currentTime[89] = "";
	sprintf(currentTime, "%s.%d+0000", buffer, milli);

	std::string str(currentTime);

	myfile << str << "\t" << conductance << std::endl;    
	std::cout << str << "\t" << conductance << std::endl;    
}


int main (){
	setup();
	while(1){
		loop();
	}
	myfile.close();
	return (0);
}