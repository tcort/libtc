/*
    adif.h -- Amateur Data Interchange Format (ADIF)
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

#include "tc/adif.h"
#include "tc/ctype.h"
#include "tc/stdlib.h"

int tc_adif_is_valid_data_type_specifier(char ch) {
	switch (tc_toupper(ch)) {
		case 'B': return 1; /* Boolean */
		case 'N': return 1; /* Number */
		case 'D': return 1; /* Date */
		case 'T': return 1; /* Time */
		case 'S': return 1; /* String */
		case 'M': return 1; /* Multiline String */
		case 'E': return 1; /* Enumeration */
		case 'L': return 1; /* Location */
		default : return 0;
	}

}

struct tc_adif *tc_adif_parse(char *adif) {
	return TC_NULL;
}
