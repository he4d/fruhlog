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

#include <errno.h>
#include "dirfunc.h"

/*
 * mkdirs() creates the folders/subfolders that are passed to it.
 * The mode is defined in the header file
 */
bool Dirfunc::mkdirs(const char *path, mode_t mode) {
	char* p = const_cast<char*>(path);
	while (*p != '\0') {
		p++;
		while (*p != '\0' && *p != '/')
			p++;
		char v = *p;
		*p = '\0';
		if (mkdir(path, mode) == -1 && errno != EEXIST) {
			*p = v;
			return false;
		}
		*p = v;
	}
	return true;
}

/*
 * direxists() simply checks if the passed folder structure exists or not.
 * If yes it returns true, if not false
 */
bool Dirfunc::direxist(const char *path) {
	struct stat st;
	if (!stat(path, &st))
		return true;
	else
		return false;
}
