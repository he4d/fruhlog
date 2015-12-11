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

#ifndef FRUHLOG_SENSOR_H_
#define FRUHLOG_SENSOR_H_

#include <string>
#include <vector>
#include "logfile.h"

#define gpioPath "/sys/bus/w1/devices/"
#define baseFile "/w1_slave"
#define module1 "w1-gpio"
#define module2 "w1-therm"

class Sensor {
public:
	explicit Sensor(const std::string &sensorName);
	~Sensor();
	void readTempValues();
	double getTempCelsius() const;
	double getTempFahrenheit() const;
	std::string getSensorName() const;
	void writeLogfile();
private:
	std::string m_gpioPath;
	std::string m_sensorName;
	double m_tempCelsius;
	double m_tempFahrenheit;
	Logfile m_logfile;
};

bool initSensors(std::vector<Sensor> &allSensors);
bool loadModules();
double nround(double value, int n_places);
#endif  // FRUHLOG_SENSOR_H_
