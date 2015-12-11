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

#include <unistd.h>
#include <iostream>
#include "sensor.h"

int main(int argc, char **argv) {
	if (getuid()) {
		std::cerr << "You must be root to run the application" << std::endl;
		return 0;
	}
	if (argc < 2) {
		std::cout << "Usage: fruhlog [timevalue in seconds]\n"
				<< "Examples:\n"
				<< "  fruhlog 20"
				<< "\tfor 20 seconds update interval\n"
				<< "  fruhlog 300"
				<< "\tfor 5 minutes update interval\n";
		return 0;
	} else {
		std::vector<Sensor> allSensors;
		if(initSensors(allSensors)) {
			while (true) {
				for (auto it = begin(allSensors); it != end(allSensors); ++it) {
					it->readTempValues();
					it->writeLogfile();
				}
				sleep(atoi(argv[1]));
			}
		} else {
			return 0;
		}
	}
}
