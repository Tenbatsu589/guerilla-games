#pragma once

#include "config.h"
#include "board.h"
#include "coordinate.h"
#include "visitation_guard.h"

namespace Boggle
{
	class board_traverser
	{
	public:
		board_traverser(const board& b) : m_board(b) { }

		template<typename FUNC>
		void traverse(const coordinate& start, FUNC&& f) {
			Boggle::Config::string_type inprogress;
			traverse_int(start, inprogress, visitation_guard(), f);
		}
	private:

		template<typename FUNC>
		void traverse_int(coordinate current, Boggle::Config::string_type& inprogress, visitation_guard guard, FUNC&& f) {
			if (guard.has_visited(current))
				return;
			guard.visit(current);

			char c = m_board[current];

			inprogress.push_back(c);

			// In this version, a "q" will always represent "qu", since "u" nearly always follows "q" in English.
			if (c == 'q')
				inprogress.push_back('u');

			f(inprogress);

			coordinate::size_type min_x = std::max<coordinate::size_type>(current.X() - 1, 0);
			coordinate::size_type min_y = std::max<coordinate::size_type>(current.Y() - 1, 0);
			coordinate::size_type max_x = std::min<coordinate::size_type>(current.X() + 1, coordinate::s_dimension - 1);
			coordinate::size_type max_y = std::min<coordinate::size_type>(current.Y() + 1, coordinate::s_dimension - 1);

			for (coordinate::size_type y = min_y; y <= max_y; y++) {
				for (coordinate::size_type x = min_x; x <= max_x; x++) {
					coordinate neighbor(x, y);
					if (neighbor != current)
						traverse_int(neighbor, inprogress, guard, f);
				}
			}

			inprogress.pop_back();
			if (c == 'q')
				inprogress.pop_back();
		}

		const board& m_board;
	};
}

