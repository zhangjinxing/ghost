/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Ghost, a micro-kernel based operating system for the x86 architecture    *
 *  Copyright (C) 2015, Max Schlüssel <lokoxe@gmail.com>                     *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation, either version 3 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GHOSTLIBRARY_IO_KEYBOARD
#define GHOSTLIBRARY_IO_KEYBOARD

#include <stdint.h>
#include <string>
#include <sstream>

/**
 *
 */
class g_key_info {
public:
	g_key_info() :
			key("KEY_NONE"), pressed(false), ctrl(false), alt(false), shift(false), scancode(0) {
	}

	std::string key;
	bool pressed :1;
	bool ctrl :1;
	bool alt :1;
	bool shift :1;
	uint8_t scancode;

	/**
	 *
	 */
	bool operator<(const g_key_info& other) const {
		if (key > other.key)
			return false;
		if (key < other.key)
			return true;

		if (pressed > other.pressed)
			return false;
		if (pressed < other.pressed)
			return true;

		if (ctrl > other.ctrl)
			return false;
		if (ctrl < other.ctrl)
			return true;

		if (alt > other.alt)
			return false;
		if (alt < other.alt)
			return true;

		if (shift > other.shift)
			return false;
		if (shift < other.shift)
			return true;

		return false;
	}
};

/**
 *
 */
class g_keyboard {
private:
	static void registerKeyboard();

public:
	static g_key_info readKey(bool* break_condition = nullptr);

	static g_key_info keyForScancode(uint8_t scancode);
	static char charForKey(g_key_info info);

	static std::string getCurrentLayout();
	static bool loadLayout(std::string iso);
	static bool loadScancodeLayout(std::string iso);
	static bool loadConversionLayout(std::string iso);
};

#endif
