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

#ifndef FRUHLOG_LOGFILE_H_
#define FRUHLOG_LOGFILE_H_

#define logpath "/var/log/fruhlog/"

#include <iostream>
#include <fstream>
#include <string>
#include "../include/logfile.h"
#include "../include/dirfunc.h"
#include "../include/datetime.h"

class Logfile {
public:
	explicit Logfile(const std::string &sensorName);
	~Logfile();
	void createFolderTree();
	void createCSVFile(const double &temp_c, const double &temp_f);
private:
	std::string m_directory;
	std::string m_filename;
	std::string m_sensorName;
};

bool isEmpty(std::fstream *pFile);

#endif  // FRUHLOG_LOGFILE_H_
