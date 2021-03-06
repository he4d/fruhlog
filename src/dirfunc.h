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

#ifndef FRUHLOG_DIRFUNC_H_
#define FRUHLOG_DIRFUNC_H_

#include <sys/stat.h>

#define DEFAULT_MODE      S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH

class Dirfunc {
public:
  static bool mkdirs(const char *path, mode_t mode = DEFAULT_MODE);
  static bool direxist(const char *path);
};


#endif  // FRUHLOG_DIRFUNC_H_
