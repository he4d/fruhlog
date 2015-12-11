/*
 * This file is part of fruhlog
 * fruhlog - a logfile creator for the raspberry-pi
 * Copyright (C) 2015 Tobias Tschinkowitz
 *
 * fruhlog is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fruhlog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fruhlog. If not, see <http://www.gnu.org/licenses/>.
 */
#include <dirent.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "sensor.h"

Sensor::Sensor(const std::string &sensorName)
:
m_gpioPath(gpioPath),
m_sensorName(sensorName),
m_tempCelsius(0),
m_tempFahrenheit(0),
m_logfile(sensorName)
{}

Sensor::~Sensor()
{}

/*
 * readTempValues() is opening the w1_slave file of the sensor and
 * reads out the necessary values. Then it converts the
 * values to degree celsius and fahrenheit and writes them
 * to the matching member variables of the sensor
 */
void Sensor::readTempValues() {
	std::string Data[22];
	std::string temperature;
	std::string status;
	double temp_raw;
	std::string device_file = m_gpioPath + m_sensorName + baseFile;
	std::ifstream inf;

	inf.open(device_file.c_str());
	if (inf.is_open()) {
		for (auto i = 0; i < 22; i++) {
			inf >> Data[i];
		}
		temperature = Data[21];
		status = Data[11];
		if (status == "YES") {
			temperature.erase(0, 2);
			temp_raw = atof(temperature.c_str());
			this->m_tempCelsius = nround(temp_raw / 1000.0, 1);
			this->m_tempFahrenheit =
					nround(this->m_tempCelsius * 9.0 / 5.0 + 32.0, 1);
		} else {
			std::cerr << "Status not okay" << std::endl;
		}
	} else {
		std::cerr << "No sensorfile found.." << std::endl;
	}
}

double Sensor::getTempCelsius() const {
	return m_tempCelsius;
}

double Sensor::getTempFahrenheit() const {
	return m_tempFahrenheit;
}

std::string Sensor::getSensorName() const {
	return m_sensorName;
}

void Sensor::writeLogfile() {
	m_logfile.createFolderTree();
	m_logfile.createCSVFile(m_tempCelsius, m_tempFahrenheit);
}

/*
 * initSensors() will search for all connected DS18B20 sensors to the
 * GPIO Port of the raspberry-pi. It will then create the objects for each
 * found sensor and pushes these into the vector which is passed as an pointer
 * to the function, with the specific sensor names found by the function
 */
bool initSensors(std::vector<Sensor> &allSensors) {
	if (loadModules()) {
		std::vector<std::string> sensorNames;
		struct dirent **namelist;
		std::string temp_files;

		int n = scandir(gpioPath, &namelist, NULL, alphasort);
		for (int i = 0; i < n; i++) {
			temp_files = namelist[i]->d_name;
			free(namelist[i]);
			if (temp_files.substr(0, 2) == "28") {
				sensorNames.push_back(temp_files);
			}
		}
		free(namelist);
		if (!sensorNames.size()) {
			std::cerr << "No Sensors found.." << std::endl;
			return false;
		} else {
			for (auto it = begin(sensorNames); it != end(sensorNames); ++it)
			{
				allSensors.push_back(Sensor(*it));
			}
			return true;
		}
	}
	return false;
}

/*
 * loadModules() will load the necessary kernel modules for the DS18B20 if they
 * are not already loaded. Therefore you have to run the program as root.
 * If it succeeds with loading it returns true, if not false and writes out an
 * error message.
 */
bool loadModules() {
	if (!system("modprobe " module1) && !system("modprobe " module2)) {
		return true;
	} else {
		std::cerr << "Modules could not be loaded.." << std::endl;
		return false;
	}
}

double nround(double value, int n_places) {
	double places = pow(10.0, n_places);
	return round(value * places) / places;
}
