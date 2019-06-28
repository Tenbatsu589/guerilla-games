#pragma once

#include "config.h"
#include "board.h"
#include "dictionary.h"

namespace Boggle {
	using string_type = Boggle::Config::string_type;
	using word_container = std::vector<string_type>;
	using coordinate_container = std::array<coordinate, 16>;
	using coordinate_iterator = coordinate_container::iterator;

	struct solver
	{
		solver(const board& _board, const dictionary& _dictionary) : _board(_board), _dictionary(_dictionary) { }
		void traverse_cell(const coordinate& cell, Boggle::word_container& words);
		Boggle::word_container operator()(Boggle::coordinate_iterator begin, Boggle::coordinate_iterator end);
		const board& _board;
		const dictionary& _dictionary;
	};

	word_container solve(const board& _board, const dictionary& _dictionary);
};

