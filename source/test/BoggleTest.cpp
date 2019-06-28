// Game Rules:
//  Boggle is a word game.  The goal is to make as many words as possible
//  out of the given set of letters laid out in a 4x4 grid.  Words are 
//  formed by starting with any letter and moving to an adjacent letter
//  (up, down, left, right, or diagonal) and so-forth on.  Once a letter
//  is used in a word, it can not be used again.  All words must be a 
//  minimum of 3 characters in length.  Finally, in this version, a "q"
//  will always represent "qu", since "u" nearly always follows "q" in
//  English.  If a word may be formed multiple ways on the same board, it
//  only counts once.
//
// Example:
//
// Board:
//    P W Y R
//    E N T H
//    G S I Q
//    O L S A
//
// A few possible words:
//   pen
//   peg
//   quit
//   hit
//   slit
//   slits
//
// Command line arguments:
//  BoggleTest.exe <dictionary_filename> <board_filename> <output_filename>
//
// Dictionary:
//  The dictionary file is an ASCII text file that lists acceptable words.  Each word is
//  new line separated.  Words are in alphabetical order and all lowercase, utilizing
//  only letters 'a' to 'z'.
//
// Board:
//  The board file is an ASCII text file that is 4 lines of 4 characters.  These
//  represent the game board, a 4x4 matrix of characters.  These may be mixed case.
//  Whitespace is optional and should be ignored.  Only letters 'a' to 'z' or 'A'
//  to 'Z' are used.
//
// Output:
//  The output should be an ASCII text file (in alphabetical order) of all legal words
//  possible to spell on the current board that are in the given dictionary.  These
//  should be all lowercase and newline separated (same format as the dictionary).

#include "board.h"
#include "config.h"
#include "profile_span.h"
#include "dictionary.h"
#include "solver.h"

using namespace Boggle;

int main(const int argc, const char* const argv[])
{

	if (argc != 4)
	{
		std::cerr << "Usage: BoggleTest <dictionary_filename> <board_filename> <output_filename>" << std::endl;
		return -1;
	}
	console_profile_span m("main");
	dictionary dict;
	board board;
	{
		console_profile_span l("loading");
		if (!dict.load(argv[1])) {
			std::cerr << "Failed to load dictionary " << argv[1];
			return -1;
		}


		if (!board.load(argv[2])) {
			std::cerr << "Failed to load board " << argv[1];
			return -1;
		}
	}

	
	word_container words;
	words.reserve(0x80);
	words = Boggle::solve(board, dict);

	{
		console_profile_span s("write");
		std::ofstream ostream;
		ostream.open(argv[3]);
		if (!ostream.is_open()) {
			std::cout << "Failed to open " << argv[3];
			return -1;
		}
		for (const string_type& word : words)
			ostream << word << "\n";
		ostream.close();
	}

	return 0;
}

