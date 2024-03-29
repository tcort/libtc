 /*
    check.h - unit testing framework
    Copyright (C) 2022, 2023, 2024  Thomas Cort

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.

    SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef TC_CHECK_H
#define TC_CHECK_H

#define TC_CHECK_PASS (0)
#define TC_CHECK_FAIL (1)
#define TC_CHECK_SKIP (77)

struct check {
	int (*fn)(void);
	char *message;
};

int tc_check(struct check *checks);

#endif
