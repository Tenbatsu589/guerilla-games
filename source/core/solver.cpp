#include "pch.h"
#include "profile_span.h"
#include "solver.h"
#include "board_traverser.h"

using namespace Boggle;

void solver::traverse_cell(const coordinate& cell, word_container& words)
{
	board_traverser traveler(_board);
	traveler.traverse(cell, [&](string_type word) {
		if (word.size() < 3)
			return;
		if (!_dictionary.contains(word))
			return;
		words.emplace_back(word);
	});
}

word_container solver::operator()(coordinate_iterator begin, coordinate_iterator end)
{
	word_container words;
	while (begin != end) {
		traverse_cell(*begin, words);
		begin++;
	}
	return words;
}

using task_t = std::packaged_task< word_container(coordinate_iterator, coordinate_iterator)>;

namespace Boggle {
	word_container solve(const board& _board, const dictionary& _dictionary)
	{
		console_profile_span _t("traverse");
		const coordinate::size_type min_x = 0;
		const coordinate::size_type min_y = 0;
		const coordinate::size_type max_x = coordinate::s_dimension - 1;
		const coordinate::size_type max_y = coordinate::s_dimension - 1;

		coordinate_container coords;
		for (coordinate::size_type y = min_y; y <= max_y; y++) {
			for (coordinate::size_type x = min_x; x <= max_x; x++) {
				coordinate cell(x, y);
				coords[cell.index()] = cell;
			}
		}

		size_t concurrency = std::thread::hardware_concurrency();
		size_t cells_per_thread = coords.size() / concurrency;
		size_t remainder_index = coords.size() % concurrency;

		auto begin = coords.begin();
		auto end = coords.end();
		size_t thread_index = 0;

		std::vector<std::thread> threads;
		std::vector<std::future<word_container>> futures;
		while (begin != end) {
			auto thread_begin = begin;
			auto thread_end = thread_begin;
			thread_end += cells_per_thread;
			if (thread_index < remainder_index)
				thread_end += 1;
			task_t task(solver(_board, _dictionary));
			futures.emplace_back(task.get_future());
			threads.emplace_back(std::move(task), thread_begin, thread_end);

			begin = thread_end;
		}
		assert(begin == coords.end());

		word_container words;
		for (std::future<word_container>& future : futures) {
			const word_container& found = future.get();
			words.insert(words.end(), found.begin(), found.end());
		}

		{
			console_profile_span s("sort");
			std::sort(words.begin(), words.end());
			//If a word may be formed multiple ways on the same board, it only counts once.
			auto duplicate = std::adjacent_find(words.begin(), words.end());
			while (duplicate != words.end()) {
				words.erase(duplicate);
				duplicate = std::adjacent_find(words.begin(), words.end());
			}
		}

		return words;
	}
}