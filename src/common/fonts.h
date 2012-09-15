/**
 * NDS Toolkit - A suite of tools for hacking Nintendo video games.
 * Copyright (C) 2012 Vinny Diehl
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
**/

/**
 * @file fonts.h - Constants for fonts.
**/

#ifndef FONTS_H_INCLUDED
#define FONTS_H_INCLUDED

#include <wx/font.h>

// :TODO: 2012-09-14 gbchaosmaster - Use fixed-width font from system settings
// Right now it's just using a generic fixed-width font. Figure out how to
// find the user's selected fixed-width, and use that.
const wxFont FIXED_FONT(10, wxMODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

#endif // FONTS_H_INCLUDED
