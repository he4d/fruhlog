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

#include "../include/datetime.h"

/*
 * getDate() simply returns a string with the value, depending on the argument
 * which it got on calling.
 * Possible arguments:
 * y - Year
 * m - Month
 * d - Day
 * t - Time (14:23:10)
 * s - Seconds
 * Y - Full date (2014-05-12)
 */
std::string getDate(const char &what) {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	switch (what) {
	case 'y':
		strftime(buffer, 80, "%Y", timeinfo);
		break;
	case 'm':
		strftime(buffer, 80, "%m", timeinfo);
		break;
	case 'd':
		strftime(buffer, 80, "%d", timeinfo);
		break;
	case 't':
		strftime(buffer, 80, "%H:%M:%S", timeinfo);
		break;
	case 's':
		strftime(buffer, 80, "%S", timeinfo);
		break;
	case 'Y':
		strftime(buffer, 80, "%F", timeinfo);
		break;
	default:
		std::cerr << "Unknown parameter to getDate function.." << std::endl;
		return 0;
	}
	return buffer;
}
