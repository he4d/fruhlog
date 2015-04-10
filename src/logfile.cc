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

#include "../include/logfile.h"

Logfile::Logfile(const std::string &sensorName)
:
m_sensorName(sensorName)
{}

Logfile::~Logfile()
{}

/*
 * createFolderTree() creates the folders where the log files have to be saved.
 * The folders look like this:
 * /var/log/fruhlog/28-0000542fd/2014/05/
 * If the folders already exist it just leaves the function and does nothing
 */
void Logfile::createFolderTree() {
	m_directory = logpath + m_sensorName + "/" +
			getDate('y') + "/"+getDate('m') + "/";
	if (!direxist(m_directory.c_str()))
		if (!mkdirs(m_directory.c_str()))
			std::cerr << "Could not create directories.." << std::endl;
}

/*
 * createCSVFile() takes the temperatures in celsius and fahrenheit and writes
 * these into the csv file. It checks if the files is empty. If this is true
 * then it creates the titles for the rows, if not its just appending the
 * current values to a new line.
 * If it couldnt open the file in any case it writes out an error.
 */
void Logfile::createCSVFile(const double &temp_c, const double &temp_f) {
	std::string filename;
	filename.append(m_directory+getDate('d')+".csv");
	std::fstream file(filename,
			std::fstream::in | std::fstream::out | std::fstream::app);
	if (file) {
		if (isEmpty(&file)) {
			file << "date,time,temp_c,temp_f,sensor\n"
					<< getDate('Y') << ","
					<< getDate('t') << ","
					<< temp_c << ","
					<< temp_f << ","
					<< m_sensorName;
		} else {
			file << "\n" << getDate('Y') << ","
					<< getDate('t') << ","
					<< temp_c << ","
					<< temp_f << ",";
		}
	} else {
		std::cerr << "Could not open file..." << std::endl;
	}
	file.close();
}

/*
 * isEmpty() just checks if the passed file has no content in it.
 * If its empty it returns true if not false
 */
bool isEmpty(std::fstream *pFile) {
	pFile->seekg(0, pFile->end);
	bool empty = !pFile->tellg();
	pFile->seekg(0, pFile->beg);
	return empty;
}
