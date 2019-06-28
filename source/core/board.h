#pragma once

#include "coordinate.h"

// Board:
//  The board file is an ASCII text file that is 4 lines of 4 characters.  These
//  represent the game board, a 4x4 matrix of characters.  These may be mixed case.
//  Whitespace is optional and should be ignored.  Only letters 'a' to 'z' or 'A'
//  to 'Z' are used.

namespace Boggle
{
	class board
	{
	public:
		bool load(std::string_view filename);
		char operator[](size_t index) const {
			assert(index < 16);
			return m_data[index];
		}

		char operator[](const coordinate& coord) const {
			size_t index = coord.index();
			assert(index < 16);
			return m_data[index];
		}
	private:
		char m_data[16];
	};
};